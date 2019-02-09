/**
 * This file is part of Ark Cpp Client.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 * 
 * BIP66: https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki
 * adapted from: https://github.com/bitcoinjs/bip66/blob/master/index.js
 **/

#include "bip66.h"
#include <vector>
#include <cstring>


bool BIP66::check(const std::vector<uint8_t>& signature) {
  if ((signature.size() < 8)
    || (signature.size() > 72)
    || (signature[0] != 0x30)
    || (signature[1] != signature.size() - 2)
    || (signature[2] != 0x02)) {
    return false;
  };

  uint8_t lenR = signature[3];
  if ((lenR == 0)
    || (5 + lenR >= signature.size())
    || (signature[4 + lenR] != 0x02)) {
    return false;
  };

  uint8_t lenS = signature[5 + lenR];
  if ((lenS == 0)
    || ((6 + lenR + lenS) != signature.size())) {
    return false;
  };

  if ((signature[4] & 0x80)
    || (lenR > 1 && (signature[4] == 0x00) && !(signature[5] & 0x80))) {
    return false;
  };

  if ((signature[lenR + 6] & 0x80)
    || (lenS > 1 && (signature[lenR + 6] == 0x00) && !(signature[lenR + 7] & 0x80))) {
    return false;
  };

  return true;
}


bool BIP66::decode(
    const std::vector<uint8_t>& signature,
    std::vector<uint8_t>& r,
    std::vector<uint8_t>& s) {

  // If signature is DER encoded
  if (check(signature)) { 
    uint8_t lenR = signature[3];
    uint8_t lenS = signature[5 + lenR];
    
    // non-BIP66 - extract R, S values
    r = std::vector<uint8_t>(&signature[4], &signature[4] + lenR);
    s = std::vector<uint8_t>(&signature[6 + lenR], &signature[6 + lenR] + lenS);

    return true;
  };
  return false;
}


/*
 * Expects r and s to be positive DER integers.
 *
 * The DER format uses the most significant bit as a sign bit (& 0x80).
 * If the significant bit is set AND the integer is positive, a 0x00 is prepended.
 *
 * Examples:
 *
 *      0 =>     0x00
 *      1 =>     0x01
 *     -1 =>     0xff
 *    127 =>     0x7f
 *   -127 =>     0x81
 *    128 =>   0x0080
 *   -128 =>     0x80
 *    255 =>   0x00ff
 *   -255 =>   0xff01
 *  16300 =>   0x3fac
 * -16300 =>   0xc054
 *  62300 => 0x00f35c
 * -62300 => 0xff0ca4
*/
bool BIP66::encode(
    const std::vector<uint8_t>& r,
    const std::vector<uint8_t>& s,
    std::vector<uint8_t>& signatureBuffer) {
  auto lenR = r.size();
  auto lenS = s.size();
  if ((lenR == 0)
    || (lenS == 0)
    || (lenR > 33)
    || (lenS > 33)
    || (r[0] & 0x80)
    || (s[0] & 0x80)
    || (lenR > 1 && (r[0] == 0x00) && !(r[1] & 0x80))
    || (lenS > 1 && (s[0] == 0x00) && !(s[1] & 0x80))) {
    return false;
  };

  auto it = r.begin();
  while (lenR > 1 && *it == 0 && *(it + 1) < 0x80) {
    --lenR;
    ++it;
  };
  it = s.begin();
  while (lenS > 1 && *it == 0 && *(it + 1) < 0x80) {
    --lenS;
    ++it;
  };

  signatureBuffer.clear();
  signatureBuffer.reserve(6 + lenR + lenS);

  /* 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S] */
  signatureBuffer.push_back(0x30);                                      // [0]
  signatureBuffer.push_back(static_cast<uint8_t>(6 + lenR + lenS - 2)); // [1]
  signatureBuffer.push_back(0x02);                                      // [2]
  signatureBuffer.push_back(static_cast<uint8_t>(lenR));                // [3]
  signatureBuffer.insert(signatureBuffer.end(), r.begin(), r.end());    // [4]
  signatureBuffer.push_back(0x02);                                      // [4 + lenR]
  signatureBuffer.push_back(static_cast<uint8_t>(lenS));                // [5 + lenR]
  signatureBuffer.insert(signatureBuffer.end(), s.begin(), s.end());    // [6 + lenR]

  return check(signatureBuffer);
}


bool BIP66::encode(const uint8_t rawSignature[32 * 2], std::vector<uint8_t>& signatureBuffer) {
  std::vector<uint8_t> r(32);
  std::vector<uint8_t> s(32);
  memcpy(&r[0], &rawSignature[0], 32);
  memcpy(&s[0], &rawSignature[32], 32);

  return BIP66::encode(r, s, signatureBuffer);
}
