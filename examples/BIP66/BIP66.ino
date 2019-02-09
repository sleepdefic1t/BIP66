/**
 * This file is part of Ark Cpp Client.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#include <Arduino.h>
#include <bip66.h>
#include "hex.h"


const char* decodedSignatureHex = "21704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d61140edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93";
const char* encodedSignatureHex = "3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93";

const char* decodedSignatureHex2 = "38044de976712d32fbf37451c266e1867e6e31b4e69ada8792a94db32078ab584c146804cc62f2231d39d9e3afc704b51e491cee0c7cfa6ac3548f3db4c511da";
const char* encodedSignatureHex2 = "3044022038044de976712d32fbf37451c266e1867e6e31b4e69ada8792a94db32078ab5802204c146804cc62f2231d39d9e3afc704b51e491cee0c7cfa6ac3548f3db4c511da";

const char* decodedSignatureHex3 = "3e422b8d4e4b5232ae6e612e5f43db12185b706cdbbb4c142fad9101b730bff12e4c4b36741cf39ac8c53c45af7799bcd001475845a50d84e1e4cde524276fe9";
const char* encodedSignatureHex3 = "304402203e422b8d4e4b5232ae6e612e5f43db12185b706cdbbb4c142fad9101b730bff102202e4c4b36741cf39ac8c53c45af7799bcd001475845a50d84e1e4cde524276fe9";

const char* decodedSignatureHex4 = "35ff1bf278ada14e964443e84778fddd52f6bc8f57cd86bd22eab891a59e5db13a6cdd02469d3b33b3550dea5be5b8aa68f3d20395e185e41ca374fa3b26d795";
const char* encodedSignatureHex4 = "3044022035ff1bf278ada14e964443e84778fddd52f6bc8f57cd86bd22eab891a59e5db102203a6cdd02469d3b33b3550dea5be5b8aa68f3d20395e185e41ca374fa3b26d795";

const char* decodedSignatureHex5 = "0094e93db8f0c4117fb32d2c534b2770cf3d6ccdc64c7cda342081afa6947d3f5422176faae12303389ff351e70641177a1b4386fae7613f2f4a3537dd601a50";
const char* encodedSignatureHex5 = "304402200094e93db8f0c4117fb32d2c534b2770cf3d6ccdc64c7cda342081afa6947d3f02205422176faae12303389ff351e70641177a1b4386fae7613f2f4a3537dd601a50";


std::vector<const char*> decodedSignaturesHex = {
  decodedSignatureHex,
  decodedSignatureHex2,
  decodedSignatureHex3,
  decodedSignatureHex4,
  decodedSignatureHex5
};

std::vector<const char*> encodedSignaturesHex = {
  encodedSignatureHex,
  encodedSignatureHex2,
  encodedSignatureHex3,
  encodedSignatureHex4,
  encodedSignatureHex5
};


void testChecking() {
  Serial.print("\n\n========== testChecking ==========\n");

  auto count = 5;
  auto matches = 0;
  for (auto i = 0; i < count; ++i) {
    std::vector<uint8_t> encodedBytes = HexToBytes(encodedSignaturesHex[i]);

    const auto checked = BIP66::check(encodedBytes);
      Serial.print("\nsuccessful: ");
      Serial.println(checked ? "true" : "false");
      Serial.println(BytesToHex(encodedBytes).c_str());

    checked ? ++matches : 0;
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d checks successful!\n", matches, count);
    Serial.print(buf);

  Serial.print("\n========== /testChecking ==========\n\n");
}


void testDecoding() {
  Serial.print("\n\n========== testDecoding ==========\n");

  auto count = 5;
  auto matches = 0;
  for (auto i = 0; i < count; ++i) {
    std::vector<uint8_t> encodedBytes = HexToBytes(encodedSignaturesHex[i]);
    std::vector<uint8_t> rawSignatureBuffer;

    std::vector<uint8_t> r(32);
    std::vector<uint8_t> s(32);

    const auto decoded = BIP66::decode(encodedBytes, r, s);
      Serial.print("\nsuccessful: ");
      Serial.println(decoded ? "true" : "false");

    rawSignatureBuffer.insert(rawSignatureBuffer.begin(), r.begin(), r.end());
    rawSignatureBuffer.insert(rawSignatureBuffer.begin() + 32, s.begin(), s.end());
      Serial.println(BytesToHex(encodedBytes).c_str());
      Serial.println(BytesToHex(rawSignatureBuffer.begin(), rawSignatureBuffer.end()).c_str());
 
    if (rawSignatureBuffer == HexToBytes(decodedSignaturesHex[i])) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d decodings successful!\n", matches, count);
    Serial.print(buf);
    
  Serial.print("\n========== /testDecoding ==========\n\n");
}


void testEncodingPair() {
  Serial.print("\n\n========== testEncodingPair ==========\n");

  auto count = 5;
  auto matches = 0;
  for (auto i = 0; i < count; ++i) {
    std::vector<uint8_t> decodedBytes = HexToBytes(decodedSignaturesHex[i]);
    std::vector<uint8_t> r(32);
    std::vector<uint8_t> s(32);
    memcpy(&r[0], &decodedBytes[0], 32);
    memcpy(&s[0], &decodedBytes[32], 32);

    std::vector<uint8_t> rawSignatureBuffer(64);
    const auto encoded = BIP66::encode(r, s, rawSignatureBuffer);
      Serial.print("\nsuccessful: ");
      Serial.println(encoded ? "true" : "false");
      Serial.println(BytesToHex(r.begin(), r.end()).c_str());
      Serial.println(BytesToHex(s.begin(), s.end()).c_str());
      Serial.println(BytesToHex(rawSignatureBuffer.begin(), rawSignatureBuffer.end()).c_str());
    
    if (rawSignatureBuffer == HexToBytes(encodedSignaturesHex[i]) && (BIP66::check(rawSignatureBuffer))) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d encodings successful!\n", matches, count);
    Serial.print(buf);
    
  Serial.print("\n========== /testEncodingPair ==========\n\n");
}

void testEncodingRaw() {
  Serial.print("\n\n========== testEncodingRaw ==========\n");

  auto count = 5;
  auto matches = 0;
  for (auto i = 0; i < count; ++i) {
    std::vector<uint8_t> decodedBytes = HexToBytes(decodedSignaturesHex[i]);
    std::vector<uint8_t> signatureBuffer(72);

    const auto encoded = BIP66::encode(&decodedBytes[0], signatureBuffer);
      Serial.print("\nsuccessful: ");
      Serial.println(encoded ? "true" : "false");
      Serial.println(BytesToHex(decodedBytes.begin(), decodedBytes.end()).c_str());
      Serial.println(BytesToHex(signatureBuffer.begin(), signatureBuffer.end()).c_str());
    
    if (signatureBuffer == HexToBytes(encodedSignaturesHex[i]) && (BIP66::check(signatureBuffer))) {
      ++matches;
    };
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d encodings successful!\n", matches, count);
    Serial.print(buf);
    
  Serial.print("\n========== /testEncodingRaw ==========\n\n");
}


void testEncodeDecode() {
  Serial.print("\n\n========== testEncodeDecode ==========\n");

  auto count = 5;
  auto matches = 0;
  for (auto i = 0; i < count; ++i) {
    std::vector<uint8_t> encodedBytes = HexToBytes(encodedSignaturesHex[i]);

    const auto checked = BIP66::check(encodedBytes);
  
    std::vector<uint8_t> r(32);
    std::vector<uint8_t> s(32);
  
    const auto decoded = BIP66::decode(encodedBytes, r, s);
  
    std::vector<uint8_t> temp(72);
    const auto encoded = BIP66::encode(r, s, temp);

    (checked && decoded && encoded) ? ++matches : 0;
  };
  char buf[56];
    sprintf(buf, "\n%d out of %d successful!\n", matches, count);
    Serial.print(buf);

  Serial.print("\n========== testEncodeDecode ==========\n\n");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  testChecking();
  
  testEncodingPair();

  testEncodingRaw();

  testDecoding();

  testEncodeDecode();
}

void loop() { }
