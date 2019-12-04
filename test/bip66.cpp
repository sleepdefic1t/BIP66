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

#include "gtest/gtest.h"

#include <bip66.hpp>

#include <array>
#include <cstdint>

#include "test_cases.hpp"

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, encode) {
    const uint8_t count     = ENC_DEC_COUNT;
    uint8_t matches         = 0U;

    std::array<uint8_t, ENCODED_LENGTH> signature {};

    while (++matches < count &&
           bip66::encode(test_cases::decoded[matches],
                         ELEMENT_LENGTH,
                         &test_cases::decoded[matches][ELEMENT_LENGTH],
                         ELEMENT_LENGTH,
                         signature.data())) {};

  ASSERT_EQ(matches, count);
}

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, encode_valid) {
    const uint8_t count     = VALID_ENCODED_COUNT;
    uint8_t matches         = 0U;

    std::array<uint8_t, ENCODED_MAX_LENGTH> signature {};

    while (++matches < count &&
           bip66::encode(&test_cases::valid::r[matches][1],
                         test_cases::valid::r[matches][0],
                         &test_cases::valid::s[matches][1],
                         test_cases::valid::s[matches][0],
                         signature.data())) {};

    ASSERT_EQ(matches, count);
}

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, encode_invalid) {
    const uint8_t count     = INVALID_RS_COUNT;
    uint8_t misses          = 0U;

    std::array<uint8_t, ENCODED_MAX_LENGTH> signature {};

    while (++misses < count &&
           !bip66::encode(&test_cases::invalid::r[misses][1],
                          test_cases::invalid::r[misses][0],
                          &test_cases::invalid::s[misses][1],
                          test_cases::invalid::s[misses][0],
                          signature.data())) {};

    ASSERT_EQ(misses, count);
}

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, decode) {
    uint8_t matches = 0U;

    std::array<uint8_t, DECODED_LENGTH> rsBuffer {};

    while (bip66::decode(test_cases::encoded[++matches],
                         ENCODED_LENGTH,
                         rsBuffer.data(),
                         &rsBuffer[ELEMENT_LENGTH])) {};

    ASSERT_EQ(matches, ENC_DEC_COUNT);
}
////////////////////////////////////////////////////////////////////////////////

TEST(BIP66, decode_valid) {
    const uint8_t count     = VALID_ENCODED_COUNT;
    uint8_t matches         = 0U;

    std::array<uint8_t, DECODED_LENGTH + 1U> rsBuffer {};

    while (++matches < count &&
           bip66::decode(&test_cases::valid::encoded[matches][1],
                         test_cases::valid::encoded[matches][0],
                         rsBuffer.data(),
                         &rsBuffer[ELEMENT_LENGTH])) {};

    ASSERT_EQ(matches, count);
}
////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, decode_invalid) {
    const uint8_t count     = VALID_ENCODED_COUNT;
    uint8_t misses          = 0U;

    std::array<uint8_t, DECODED_LENGTH> rsBuffer {};

    while (++misses < count &&
           !bip66::decode(&test_cases::invalid::encoded[misses][1],
                          test_cases::invalid::encoded[misses][0],
                          rsBuffer.data(),
                          &rsBuffer[ELEMENT_LENGTH])) {};

    ASSERT_EQ(misses, count);
}

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, check) {
    uint8_t matches = 0U;

    while (bip66::check(test_cases::encoded[++matches], ENCODED_LENGTH)) {};

    ASSERT_EQ(matches, ENC_DEC_COUNT);
}

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, check_valid) {
    const uint8_t count     = VALID_ENCODED_COUNT;
    uint8_t matches         = 0U;

    while (++matches < count &&
           bip66::check(&test_cases::valid::encoded[matches][1],
                        test_cases::valid::encoded[matches][0])) {};

    ASSERT_EQ(matches, VALID_ENCODED_COUNT);
}

////////////////////////////////////////////////////////////////////////////////
TEST(BIP66, check_invalid) {
    const uint8_t count     = INVALID_ENCODED_COUNT;
    uint8_t misses          = 0U;

    while (++misses < count &&
           !bip66::check(test_cases::invalid::encoded[misses],
                         test_cases::invalid::encoded[misses][0])) {};

    ASSERT_EQ(misses, count);
}
