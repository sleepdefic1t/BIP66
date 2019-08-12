/**
 * bip66.h
 * 
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * author: Simon Downey <simon@ark.io>
 *  
 * BIP66: https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki
 * adapted from: https://github.com/bitcoinjs/bip66/blob/master/index.js
 **/

#ifndef BIP66_H
#define BIP66_H

#include <cstddef>
#include <cstdint>
#include <vector>

struct BIP66 {
  static constexpr size_t ELEMENT_LEN = 32U;
  static constexpr size_t SIG_MIN_LEN = 8U;
  static constexpr size_t SIG_MAX_LEN = 72U;

  static bool encode(const std::vector<uint8_t>& r,
                     const std::vector<uint8_t>& s,
                     std::vector<uint8_t>& outSignature);

  static bool encode(const uint8_t* rawSignature,
                     std::vector<uint8_t>& outSignature);

  static bool decode(const std::vector<uint8_t>& signature,
                     std::vector<uint8_t>& outR,
                     std::vector<uint8_t>& outS);

  static bool check (const std::vector<uint8_t>& signature);
  static bool check(const uint8_t* signature, size_t len);
};

#endif
