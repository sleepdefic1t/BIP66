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

#ifndef BIP66_H
#define BIP66_H

#include <vector>

namespace BIP66 {

bool check (const std::vector<uint8_t>& signature);
bool decode(const std::vector<uint8_t>& signature, std::vector<uint8_t>& r, std::vector<uint8_t>& s);
bool encode(const std::vector<uint8_t>& r, const std::vector<uint8_t>& s, std::vector<uint8_t>& signatureBuffer);
bool encode(const uint8_t rawSignature[32 * 2], std::vector<uint8_t>& signatureBuffer);

};

#endif
