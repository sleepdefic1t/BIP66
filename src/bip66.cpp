/**
 * bip66.cpp
 * 
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * author: Simon Downey <simon@ark.io>
 *  
 * BIP66: https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki
 * adapted from: https://github.com/bitcoinjs/bip66/blob/master/index.js
 **/

#include "bip66.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace {
constexpr size_t ELEMENT_LEN = 32U;
constexpr size_t SIG_MIN_LEN = 8U;
constexpr size_t SIG_MAX_LEN = 72U;

constexpr uint8_t SIG_COMPOUND_BYTE = 0x30;
constexpr uint8_t SIG_INTEGER_BYTE  = 0x02;
constexpr uint8_t SIG_NEGATIVE_BYTE = 0x80;  // (x & 0x80)
constexpr uint8_t SIG_ZERO_BYTE     = 0x00;

constexpr size_t SIG_SEQ_OFFSET   = 0;
constexpr size_t SIG_LEN_OFFSET   = 1;
constexpr size_t R_SEQ_OFFSET     = 2;
constexpr size_t R_LEN_OFFSET     = 3;
constexpr size_t R_BEGIN_OFFSET   = 4;
constexpr size_t S_LEN_OFFSET     = 5;  // + lenR
constexpr size_t S_BEGIN_OFFSET   = 6;  // + lenR

////////// BIP66::helpers //////////

// Negative numbers are not allowed for R or S.
inline bool isNegativeByte(const uint8_t& byte) {
  return (byte & SIG_NEGATIVE_BYTE) != 0;
}

// Null bytes at the start of an Element is not allowed,
// unless the Element would otherwise be interpreted as a negative number.
inline bool isNegativeElement(const uint8_t* element, size_t len) {
  return (len > 1) &&
         (element[0] == SIG_ZERO_BYTE) &&
         (element[1] & SIG_NEGATIVE_BYTE) == 0;
}

// Check whether the element is..
// .. not Zero-length.
// .. not too big.
// .. not Null.
// .. not Negative at the starting bytes.
inline bool isValidElement(const uint8_t* element, size_t len) {
  if (len == 0) { return false; };
  if (len > BIP66::ELEMENT_LEN + 1) { return false; };
  if (isNegativeByte(element[0])) { return false; };
  if (isNegativeElement(element, len)) { return false; };
  return true;
}

// Check whether the R element is..
// .. a valid Element
// .. an Integer
inline bool isValidR(const uint8_t* signature, const size_t& lenR) {
return isValidElement(&signature[R_BEGIN_OFFSET], lenR) &&
       signature[R_SEQ_OFFSET] == SIG_INTEGER_BYTE;
}

// Check whether the S element is..
// .. a valid Element
// .. an Integer
inline bool isValidS(const uint8_t* signature,
                     const size_t& lenR,
                     const size_t& lenS) {
  return isValidElement(
      &signature[lenR + S_BEGIN_OFFSET], lenS) &&
      signature[lenR + R_BEGIN_OFFSET] == SIG_INTEGER_BYTE;
}

// Make sure the length of the S element is still inside the signature.
inline bool isValidLenS(const uint8_t* signature, const size_t& lenR) {
  return signature + S_LEN_OFFSET + lenR != nullptr;
}

// Extract the lengths of the R or S elements.
enum RSType { R = 0, S };
inline size_t extractLen(const uint8_t* signature, RSType type) {
  return type == R
      ? signature[R_LEN_OFFSET]
      : signature[S_LEN_OFFSET + signature[R_LEN_OFFSET]];
}

// Extract R and S elements from a Signature
inline bool extractElements(const std::vector<uint8_t>& signature,
                            std::vector<uint8_t>& outR,
                            std::vector<uint8_t>& outS) {
  const auto& lenR = extractLen(signature.data(), R);
  const auto& lenS = extractLen(signature.data(), S);

  // Copy a reference to the R element.
  const auto& rBegin = &signature.at(R_BEGIN_OFFSET);
  outR = { rBegin, rBegin + lenR };

  // Copy a reference to the S element.
  const auto& sBegin = &signature.at(S_BEGIN_OFFSET + lenR);
  outS = { sBegin, sBegin + lenS };

  return (outR.size() == lenR) && outS.size() == lenS;
}

// Check that the Signature..
// .. is validly constrained.
// .. is of the correct type.
// .. has a length that covers the entire Signature.
inline bool isValidEncoding(const uint8_t* signature, size_t len) {
  return (signature != nullptr) &&
          BIP66::SIG_MIN_LEN <= len && len <= BIP66::SIG_MAX_LEN &&
          signature[SIG_SEQ_OFFSET] == SIG_COMPOUND_BYTE &&
          signature[SIG_LEN_OFFSET] == len - R_SEQ_OFFSET;
}

// Verify that the length of the signature matches the sum of the length
// of the elements.
inline bool isValidEncodedLen(const uint8_t* signature,
                              const size_t& lenR,
                              const size_t& lenS) {
  return signature + lenR + lenS + S_BEGIN_OFFSET != nullptr;
}

}  // namespace

////////// /BIP66::helpers //////////

// BIP66 Encoding.
//
// Expects r and s to be positive DER integers.
//
// The DER format uses the most significant bit as a sign bit (& 0x80).
// If the significant bit is set AND the integer is positive, a 0x00 is prepended.
//
// Examples:
//
//      0 =>     0x00
//      1 =>     0x01
//     -1 =>     0xff
//    127 =>     0x7f
//   -127 =>     0x81
//    128 =>   0x0080
//   -128 =>     0x80
//    255 =>   0x00ff
//   -255 =>   0xff01
//  16300 =>   0x3fac
// -16300 =>   0xc054
//  62300 => 0x00f35c
// -62300 => 0xff0ca4
struct BIP66;

////////// BIP66::encode //////////

// BIP66::encode
// 
// Format: 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S] [sighash]
// - total-length: 1-byte length descriptor of everything that follows,
//   excluding the sighash byte.
// - R-length: 1-byte length descriptor of the R value that follows.
// - R: arbitrary-length big-endian encoded R value. It must use the shortest
//   possible encoding for a positive integers (which means no null bytes at
//   the start, except a single one when the next byte has its highest bit set).
// - S-length: 1-byte length descriptor of the S value that follows.
// - S: arbitrary-length big-endian encoded S value. The same rules apply.
bool BIP66::encode(const std::vector<uint8_t>& r,
                   const std::vector<uint8_t>& s,
                   std::vector<uint8_t>& outSignature) {
  // Ensure that each element is valid.
  if (!isValidElement(r.data(), r.size()) || !isValidElement(s.data(), s.size())) {
    return false;
  };

  uint8_t lenR = r.size();
  uint8_t lenS = s.size();
  auto it = s.begin();
  while (lenR > 1 && *it == 0 && *(it + 1) < SIG_NEGATIVE_BYTE) {
    --lenR;
    ++it;
  };
  it = s.begin();
  while (lenS > 1 && *it == 0 && *(it + 1) < SIG_NEGATIVE_BYTE) {
    --lenS;
    ++it;
  };

  outSignature.clear();
  outSignature.reserve(S_BEGIN_OFFSET + lenR + lenS);

  /* 0x30 [total-length] 0x02 [R-length] [R] 0x02 [S-length] [S] */
  outSignature.push_back(SIG_COMPOUND_BYTE);                            // [0]
  outSignature.push_back(S_BEGIN_OFFSET + lenR + lenS - R_SEQ_OFFSET);  // [1]
  outSignature.push_back(SIG_INTEGER_BYTE);                             // [2]
  outSignature.push_back(lenR);                                         // [3]
  outSignature.insert(outSignature.end(), r.begin(), r.end());          // [4]
  outSignature.push_back(SIG_INTEGER_BYTE);                             // [4 + lenR]
  outSignature.push_back(lenS);                                         // [5 + lenR]
  outSignature.insert(outSignature.end(), s.begin(), s.end());          // [6 + lenR]

  return check(outSignature);
}

// BIP66::encode
//
// Expects (R, S) elements of the raw signature to be positive DER integers.
bool BIP66::encode(const uint8_t* rawSignature,
                   std::vector<uint8_t>& outSignature) {
  return BIP66::encode(
      { &rawSignature[0], &rawSignature[BIP66::ELEMENT_LEN] },
      { &rawSignature[BIP66::ELEMENT_LEN], &rawSignature[BIP66::ELEMENT_LEN * 2] },
      outSignature);
}

////////// /BIP66::encode //////////

////////// BIP66::decode //////////

// BIP66::decode
//
// Decode the R and S elements from a Signature using validation.
bool BIP66::decode(const std::vector<uint8_t>& signature,
                   std::vector<uint8_t>& outR,
                   std::vector<uint8_t>& outS) {
  // True if signature is DER encoded and valid Elements were extracted.
  return check(signature) && extractElements(signature, outR, outS);
}

////////// /BIP66::decode //////////

////////// BIP66::check //////////

// BIP66::Check
//
// - Check that the Signature has valid encoding.
// - Ensure that each Element is..
// .. of the correct length corresponding to the Signature.
// .. a valid Element.
bool BIP66::check(const std::vector<uint8_t>& signature) {
  return BIP66::check(signature.data(), signature.size());
}

// BIP66::check
//
// - Check that the Signature has valid DER encoding.
// - Ensure that each Element is..
// .. of the correct length corresponding to the Signature.
// .. a valid Element.
bool BIP66::check(const uint8_t* signature, size_t len) {
  if (!isValidEncoding(signature, len)) {
    return false;
  };

  const auto& lenR = extractLen(signature, R);
  if (!isValidLenS(signature, lenR)) {
    return false;
  };

  const auto& lenS = extractLen(signature, S);
  if (!isValidEncodedLen(signature, lenR, lenS)) {
    return false;
  };

  return (isValidR(signature, lenR) && isValidS(signature, lenR, lenS));
}

////////// /BIP66::check //////////
