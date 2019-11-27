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

#include "bip66.hpp"

#include <array>
#include <cstdint>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// Global Constants
constexpr uint8_t MIN_SIG_LENGTH        = 8U;
constexpr uint8_t MAX_SIG_LENGTH        = 72U;

constexpr uint8_t SIG_COMPOUND          = 0x30;

constexpr uint8_t ELEMENT_LENGTH        = 32U;

constexpr uint8_t ELEMENT_PADDING       = 0x00;
constexpr uint8_t ELEMENT_INTEGER       = 0x02;
constexpr uint8_t ELEMENT_NEGATIVE      = 0x80;

constexpr uint8_t SIG_SEQ_OFFSET        = 0U;
constexpr uint8_t SIG_LEN_OFFSET        = 1U;
constexpr uint8_t R_SEQ_OFFSET          = 2U;
constexpr uint8_t R_LEN_OFFSET          = 3U;
constexpr uint8_t R_BEGIN_OFFSET        = 4U;
constexpr uint8_t S_LEN_OFFSET          = 5U;  // + lenR
constexpr uint8_t S_BEGIN_OFFSET        = 6U;  // + lenR

////////////////////////////////////////////////////////////////////////////////
namespace bip66 {

////////////////////////////////////////////////////////////////////////////////
bool isValidElement(const uint8_t *element, uint8_t length) {
    // Check that the Element isn't too small or too large.
    if (length == 0 || length > ELEMENT_LENGTH + 1U) {
        return false;
    }

    // Check that the Element would not be interpreted as a negative value.
    if ((element[0] & ELEMENT_NEGATIVE) != 0U) {
        return false;
    }

    // Check that the Element is not excessively padded.
    if (length > 1U &&
        element[0] == ELEMENT_PADDING &&
        (element[1] & ELEMENT_NEGATIVE) == 0U) {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Copy an Element adding or removing Padding if necessary.
//
// - Returns false if..
// .. the element is null.
// .. the destination is null.
// .. the element length is 0, or greater than 33.
//
// ---
// Copy Cases:
//
// Encoding and Element is Negative:
// - Prepend padding to the element and increment its length.
//
// Decoding and Element has Padding:
// - Skip the padding on copy.
//
// No Padding or Negative Elements detected:
// - We already checked the buffers and lengths, let's just go ahead and copy.
//
// ---
static bool copyElement(const uint8_t *element,
                        uint8_t *dst,
                        uint8_t &length,
                        bool encoding = true) {
    if (element == nullptr || dst == nullptr) {
        return false;
    }

    // Encoding and Element is Negative, add padding.
    if (encoding &&                                     // encoding
        length > 1 &&                                   // length > 1
        (element[0] & 0x80) != 0U) {                    // 1st byte is negative
        dst[0] = 0x00;
        std::memcpy(dst + 1, element, length);
        ++length;
    }
    // Decoding and has padding, skip the padding.
    else if (!encoding &&                               // decoding
             element[0] == 0 &&                         // has padding
             (element[1] & ELEMENT_NEGATIVE) != 0U) {   // 2nd byte is negative
        std::memcpy(dst, element + 1U, length - 1U);

        // Padding is technically considered invalid,
        // let's check the original element instead.
        return isValidElement(element, length);
    }
    // No Padding or Negative Elements detected.
    else {
        std::memcpy(dst, element, length);
    }

    return isValidElement(dst, length);
}

////////////////////////////////////////////////////////////////////////////////
// bip66::encode
// 
//  Expects r and s to be positive DER integers.
//
//  The DER format uses the most significant bit as a sign bit (& 0x80).
//  If the significant bit is set AND the integer is positive, a 0x00 is prepended.
//
//  Examples:
//
//       0 =>     0x00
//       1 =>     0x01
//      -1 =>     0xff
//     127 =>     0x7f
//    -127 =>     0x81
//     128 =>   0x0080
//    -128 =>     0x80
//     255 =>   0x00ff
//    -255 =>   0xff01
//   16300 =>   0x3fac
//  -16300 =>   0xc054
//   62300 => 0x00f35c
//  -62300 => 0xff0ca4
//
// ---
//
// Format: 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S] [sighash]
//
// - total-length: 1-byte length descriptor of everything that follows,
//   excluding the sighash byte.
//
// - R-length: 1-byte length descriptor of the R value that follows.
//
// - R: arbitrary-length big-endian encoded R value. It must use the shortest
//   possible encoding for a positive integers (which means no null bytes at
//   the start, except a single one when the next byte has its highest bit set).
//
// - S-length: 1-byte length descriptor of the S value that follows.
//
// - S: arbitrary-length big-endian encoded S value. The same rules apply.
//
// --
bool encode(const uint8_t *rElement,
            const uint8_t rElementLength,
            const uint8_t *sElement,
            const uint8_t sElementLength,
            uint8_t *outSignature) {
    if (outSignature == nullptr) {
        return false;
    }

    std::array<std::array<uint8_t, ELEMENT_LENGTH + 1> , 2U>  rs {};

    auto lenR = rElementLength;
    auto lenS = sElementLength;

    if (!copyElement(rElement, rs.at(0).begin(), lenR) ||
        !copyElement(sElement, rs.at(1).begin(), lenS)) {
        return false;
    }

    const auto outLen = S_BEGIN_OFFSET + lenR + lenS;
    if (outLen < MIN_SIG_LENGTH || outLen > MAX_SIG_LENGTH) {
        return false;
    }

    // 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S]
    outSignature[SIG_SEQ_OFFSET]    = SIG_COMPOUND;                 // 1 Byte
    outSignature[SIG_LEN_OFFSET]    = outLen - R_SEQ_OFFSET;        // 1 Byte

    // R Sequence
    outSignature[R_SEQ_OFFSET]      = ELEMENT_INTEGER;              // 1 Byte
    outSignature[R_LEN_OFFSET]      = lenR;                         // 1 Byte
    std::memcpy(&outSignature[R_BEGIN_OFFSET],              // 32 <=> 33 Bytes
                rs[0].begin(), lenR);

    // S Sequence
    outSignature[R_BEGIN_OFFSET + lenR] = ELEMENT_INTEGER;          // 1 Byte
    outSignature[S_LEN_OFFSET + lenR]   = lenS;                     // 1 Byte
    std::memcpy(&outSignature[S_BEGIN_OFFSET + lenR],       // 32 <=> 33 Bytes
            rs[1].begin(), lenS);

  return check(outSignature, outLen);                       // 70 <=> 72 Bytes
}

////////////////////////////////////////////////////////////////////////////////
// bip66::decode
//
// Decode the R and S elements from a Signature using Check validation.
bool decode(const uint8_t *signature,
            const uint8_t signatureLength,
            uint8_t *outR,
            uint8_t *outS)  {
    if (!check(signature, signatureLength)) {
        return false;
    }

    auto lenR = signature[R_LEN_OFFSET];
    auto lenS = signature[S_LEN_OFFSET + lenR];

    return copyElement(&signature[R_BEGIN_OFFSET], outR, lenR, false) &&
           copyElement(&signature[S_BEGIN_OFFSET + lenR], outS, lenS, false);
}

////////////////////////////////////////////////////////////////////////////////
// bip66::check
//
// - Check that the Signature has valid DER encoding.
// - Ensure that each Element is..
// .. of the correct length corresponding to the Signature.
// .. a valid Element.
bool check(const uint8_t *signature, uint8_t length) {
    // Check the Signature Length
    if (length < MIN_SIG_LENGTH || length > MAX_SIG_LENGTH) {
        return false;
    }

    // Check for valid encoding.
    if (signature[SIG_SEQ_OFFSET] != SIG_COMPOUND ||
        signature[SIG_LEN_OFFSET] != length - R_SEQ_OFFSET) {
        return false;
    }

    uint8_t lenR = signature[R_LEN_OFFSET];

    // Check that both elements are integers.
    if (signature[R_SEQ_OFFSET] != ELEMENT_INTEGER ||
        signature[R_BEGIN_OFFSET + lenR] != ELEMENT_INTEGER) {
        return false;
    }

    uint8_t lenS = signature[S_LEN_OFFSET + lenR];

    // Check that the R & S lengths aren't too big.
    if (S_LEN_OFFSET + lenR >= length ||
        S_BEGIN_OFFSET + lenR + lenS != length) {
        return false;
    }

    if (signature[R_BEGIN_OFFSET + lenR] != ELEMENT_INTEGER) {
        return false;
    }

    return isValidElement(&signature[R_BEGIN_OFFSET], lenR) &&
           isValidElement(&signature[lenR + S_BEGIN_OFFSET], lenS);
}

}  // namespace bip66
