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
#include <cstring>

////////////////////////////////////////////////////////////////////////////////

#define MIN_SIG_LENGTH          8U
#define MAX_SIG_LENGTH          72U

#define SIG_COMPOUND            0x30

#define ELEMENT_LENGTH          32U

#define ELEMENT_PADDING         0x00
#define ELEMENT_INTEGER         0x02
#define ELEMENT_NEGATIVE        0x80

#define SIG_SEQ_OFFSET          0U
#define SIG_LEN_OFFSET          1U
#define R_SEQ_OFFSET            2U
#define R_LEN_OFFSET            3U
#define R_BEGIN_OFFSET          4U
#define S_LEN_OFFSET            5U  // + lenR
#define S_BEGIN_OFFSET          6U  // + lenR

////////////////////////////////////////////////////////////////////////////////

namespace bip66 {

////////////////////////////////////////////////////////////////////////////////

static bool isValidElement(const uint8_t *element, const uint8_t length) {
    if (length == 0U || length > ELEMENT_LENGTH + 1U) {
        return false;
    }

    if ((element[0] & ELEMENT_NEGATIVE) != 0U) {
        return false;
    }

    // return false if the element is excessively padded.
    return !(length > 1U &&
            element[0] == ELEMENT_PADDING &&
            ((element[1] & ELEMENT_NEGATIVE) == 0U));
}

////////////////////////////////////////////////////////////////////////////////

// Copy the element to a buffer.
// Element is padded and length is incremented if needed.
static void copyElement(const uint8_t *src, uint8_t *dst, uint8_t& len) {
    if (len > 1U && (src[0] & ELEMENT_NEGATIVE) != 0U) {
        dst[0] = ELEMENT_PADDING;
        memmove(&dst[1], src, len);
        len++;
    }
    else {
        memmove(dst, src, len);
    }
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
            uint8_t *outSignature,
            const uint8_t maxOutLength) {
    if (maxOutLength < MIN_SIG_LENGTH || maxOutLength > MAX_SIG_LENGTH) {
        return false;
    }

    std::array<std::array<uint8_t, ELEMENT_LENGTH + 1U> , 2U>  rsBuffer;

    auto lenR = rElementLength;
    auto lenS = sElementLength;

    // Copy the Elements, padding if necessary.
    copyElement(rElement, rsBuffer[0].data(), lenR);
    copyElement(sElement, rsBuffer[1].data(), lenS);

    if (!isValidElement(rsBuffer[0].data(), lenR) ||
        !isValidElement(rsBuffer[1].data(), lenS)) {
        return false;
    }

    auto it = rsBuffer[0].data();
    while (*++it == 0U && *(it + 1U) < ELEMENT_NEGATIVE && --lenR > 1U) {};

    it = rsBuffer[1].data();
    while (*++it == 0U && *(it + 1U) < ELEMENT_NEGATIVE && --lenS > 1U) {};

    const auto outLen = S_BEGIN_OFFSET + lenR + lenS;

    // 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S]
    outSignature[SIG_SEQ_OFFSET]    = SIG_COMPOUND;             // 1 Byte
    outSignature[SIG_LEN_OFFSET]    = outLen - R_SEQ_OFFSET;    // 1 Byte

    outSignature[R_SEQ_OFFSET]      = ELEMENT_INTEGER;          // 1 Byte
    outSignature[R_LEN_OFFSET]      = lenR;                     // 1 Byte
    memmove(&outSignature[R_BEGIN_OFFSET],                      // 32<=>33 Bytes
            rsBuffer[0].data(), lenR);  

    outSignature[R_BEGIN_OFFSET + lenR] = ELEMENT_INTEGER;      // 1 Byte
    outSignature[S_LEN_OFFSET + lenR] = lenS;                   // 1 Byte
    memmove(&outSignature[S_BEGIN_OFFSET + lenR],               // 32<=>33 Bytes
            rsBuffer[1].data(), lenS);

  return check(outSignature, outLen);                           // 70<=>72 Bytes
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

    if (outR == nullptr || outS == nullptr) {
        return false;
    }

    memmove(outR, &signature[R_BEGIN_OFFSET], signature[R_LEN_OFFSET]);

    memmove(outS,
            &signature[S_BEGIN_OFFSET + signature[R_LEN_OFFSET]],
            signature[S_LEN_OFFSET + signature[R_LEN_OFFSET]]);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

// bip66::check
//
// - Check that the Signature has valid DER encoding.
// - Ensure that each Element is..
// .. of the correct length corresponding to the Signature.
// .. a valid Element.
bool check(const uint8_t *signature, uint8_t signatureLength) {
    if (signatureLength < MIN_SIG_LENGTH || signatureLength > MAX_SIG_LENGTH) {
        return false;
    }

    // Check for valid encoding.
    if (signature[SIG_SEQ_OFFSET] != SIG_COMPOUND ||
        signature[SIG_LEN_OFFSET] != signatureLength - R_SEQ_OFFSET) {
        return false;
    }

    uint8_t lenR = signature[R_LEN_OFFSET];
    uint8_t lenS = signature[S_LEN_OFFSET + lenR];

    if (!isValidElement(&signature[SIG_SEQ_OFFSET], lenR) ||
        !isValidElement(&signature[R_BEGIN_OFFSET + lenR], lenS)) {
        return false;
    }

    // Check that the R & S lengths aren't too big.
    if ((S_LEN_OFFSET + lenR >= signatureLength) ||
        (S_BEGIN_OFFSET + lenR + lenS) != signatureLength) {
        return false;
    }

    // Check that both elements are integers.
    if (signature[R_SEQ_OFFSET] != ELEMENT_INTEGER ||
        signature[R_BEGIN_OFFSET + lenR] != ELEMENT_INTEGER) {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace bip66
