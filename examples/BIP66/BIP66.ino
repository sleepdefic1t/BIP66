/********************************************************************************
*
*  The MIT License (MIT)
*
*  Copyright (c) Simon Downey <simon@ark.io> <https://github.com/sleepdefic1t>
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy of
*  this software and associated documentation files (the "Software"), to deal in
*  the Software without restriction, including without limitation the rights to
*  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
*  the Software, and to permit persons to whom the Software is furnished to do so,
*  subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
*  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
*  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
*  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
*  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*  BIP66: https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki
*  adapted from: https://github.com/bitcoinjs/bip66/blob/master/index.js
*
*********************************************************************************/

#include <Arduino.h>

#include <array>
#include <cstdint>

#include <bip66.hpp>

////////////////////////////////////////////////////////////////////////////////

void testEncode() {
    uint8_t r[32] = { 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 2 };
    uint8_t s[32] = { 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 };
    uint8_t signature[72];  // max signature length
    const bool success = bip66::encode(r, 32, s, 32, signature, 72U);

    printf("\nEncode: %s\n", (success ? "Successful" : "Failed"));
}

////////////////////////////////////////////////////////////////////////////////

void testDecode() {
    uint8_t derEncodedSignature[70] = { 48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 };

    uint8_t r[32];
    uint8_t s[32];

    const bool success = bip66::decode(derEncodedSignature, 70U, r, s);

    printf("\nDecode: %s\n", (success ? "Successful" : "Failed"));
}

////////////////////////////////////////////////////////////////////////////////

void testCheck() {
    const uint8_t derEncodedSignature[70] = { 48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 };

    const bool success = bip66::check(derEncodedSignature, 70U);

    printf("\nCheck: %s\n", (success ? "Successful" : "Failed"));
}

////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);

  testEncode();
  testDecode();
  testEncode();
}

////////////////////////////////////////////////////////////////////////////////

void loop() { }

////////////////////////////////////////////////////////////////////////////////
