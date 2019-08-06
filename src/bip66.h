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

#include <cstdint>
#include <vector>

static const size_t ELEMENT_SIZE  = 32U;
typedef std::vector<uint8_t> ElementBytes;

static const size_t SIG_MIN_LEN        = 8U;
static const size_t SIG_MAX_LEN        = 72U;
typedef std::vector<uint8_t> SignatureBytes;

/**/

struct BIP66 {
  static bool encode(const ElementBytes& r,
                     const ElementBytes& s,
                     SignatureBytes& outSignature);

  static bool encode(const uint8_t rawSignature[ELEMENT_SIZE * 2],
                     SignatureBytes& outSignature);

  static bool decode(const SignatureBytes& signature,
                     ElementBytes& outR,
                     ElementBytes& outS);

  static bool check (const SignatureBytes& signature);
};

#endif
