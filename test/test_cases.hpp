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

#ifndef BIP66_TEST_CASES_H
#define BIP66_TEST_CASES_H

#include <cstdint>

////////////////////////////////////////////////////////////////////////////////

#define ELEMENT_LENGTH              32U

#define ENC_DEC_COUNT               5U
#define DECODED_LENGTH              64U
#define ENCODED_LENGTH              70U
#define ENCODED_MAX_LENGTH          72U

#define VALID_ENCODED_COUNT         9U
#define VALID_ENCODED_LENGTH        71U
#define VALID_R_LENGTH              33U
#define VALID_S_LENGTH              34U

#define INVALID_ENCODED_COUNT       15U
#define INVALID_ENCODED_LENGTH      74U
#define INVALID_RS_COUNT            8U
#define INVALID_RS_LENGTH           35U

////////////////////////////////////////////////////////////////////////////////

namespace test_cases {
constexpr const uint8_t encoded[ENC_DEC_COUNT][ENCODED_LENGTH] = {
        // 3044022021704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d611402200edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93
    { 48, 68, 2, 32, 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 2, 32, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 },
        // 3044022038044de976712d32fbf37451c266e1867e6e31b4e69ada8792a94db32078ab5802204c146804cc62f2231d39d9e3afc704b51e491cee0c7cfa6ac3548f3db4c511da
    { 48, 68, 2, 32, 56, 4, 77, 233, 118, 113, 45, 50, 251, 243, 116, 81, 194, 102, 225, 134, 126, 110, 49, 180, 230, 154, 218, 135, 146, 169, 77, 179, 32, 120, 171, 88, 2, 32, 76, 20, 104, 4, 204, 98, 242, 35, 29, 57, 217, 227, 175, 199, 4, 181, 30, 73, 28, 238, 12, 124, 250, 106, 195, 84, 143, 61, 180, 197, 17, 218 },
        // 304402203e422b8d4e4b5232ae6e612e5f43db12185b706cdbbb4c142fad9101b730bff102202e4c4b36741cf39ac8c53c45af7799bcd001475845a50d84e1e4cde524276fe9
    { 48, 68, 2, 32, 62, 66, 43, 141, 78, 75, 82, 50, 174, 110, 97, 46, 95, 67, 219, 18, 24, 91, 112, 108, 219, 187, 76, 20, 47, 173, 145, 1, 183, 48, 191, 241, 2, 32, 46, 76, 75, 54, 116, 28, 243, 154, 200, 197, 60, 69, 175, 119, 153, 188, 208, 1, 71, 88, 69, 165, 13, 132, 225, 228, 205, 229, 36, 39, 111, 233 },
        // 3044022035ff1bf278ada14e964443e84778fddd52f6bc8f57cd86bd22eab891a59e5db102203a6cdd02469d3b33b3550dea5be5b8aa68f3d20395e185e41ca374fa3b26d795
    { 48, 68, 2, 32, 53, 255, 27, 242, 120, 173, 161, 78, 150, 68, 67, 232, 71, 120, 253, 221, 82, 246, 188, 143, 87, 205, 134, 189, 34, 234, 184, 145, 165, 158, 93, 177, 2, 32, 58, 108, 221, 2, 70, 157, 59, 51, 179, 85, 13, 234, 91, 229, 184, 170, 104, 243, 210, 3, 149, 225, 133, 228, 28, 163, 116, 250, 59, 38, 215, 149 },
        // 304402200094e93db8f0c4117fb32d2c534b2770cf3d6ccdc64c7cda342081afa6947d3f02205422176faae12303389ff351e70641177a1b4386fae7613f2f4a3537dd601a50
    { 48, 68, 2, 32, 0, 148, 233, 61, 184, 240, 196, 17, 127, 179, 45, 44, 83, 75, 39, 112, 207, 61, 108, 205, 198, 76, 124, 218, 52, 32, 129, 175, 166, 148, 125, 63, 2, 32, 84, 34, 23, 111, 170, 225, 35, 3, 56, 159, 243, 81, 231, 6, 65, 23, 122, 27, 67, 134, 250, 231, 97, 63, 47, 74, 53, 55, 221, 96, 26, 80 }
};  // encoded

constexpr const uint8_t decoded[ENC_DEC_COUNT][DECODED_LENGTH] = {
        // 21704f2adb2e4a10a3ddc1d7d64552b8061c05f6d12a168c69091c75581d61140edf37689d2786fc690af9f0f6fa1f629c95695039f648a6d455484302402e93
    { 33, 112, 79, 42, 219, 46, 74, 16, 163, 221, 193, 215, 214, 69, 82, 184, 6, 28, 5, 246, 209, 42, 22, 140, 105, 9, 28, 117, 88, 29, 97, 20, 14, 223, 55, 104, 157, 39, 134, 252, 105, 10, 249, 240, 246, 250, 31, 98, 156, 149, 105, 80, 57, 246, 72, 166, 212, 85, 72, 67, 2, 64, 46, 147 },
        // 38044de976712d32fbf37451c266e1867e6e31b4e69ada8792a94db32078ab584c146804cc62f2231d39d9e3afc704b51e491cee0c7cfa6ac3548f3db4c511da
    { 56, 4, 77, 233, 118, 113, 45, 50, 251, 243, 116, 81, 194, 102, 225, 134, 126, 110, 49, 180, 230, 154, 218, 135, 146, 169, 77, 179, 32, 120, 171, 88, 76, 20, 104, 4, 204, 98, 242, 35, 29, 57, 217, 227, 175, 199, 4, 181, 30, 73, 28, 238, 12, 124, 250, 106, 195, 84, 143, 61, 180, 197, 17, 218 },
        // 3e422b8d4e4b5232ae6e612e5f43db12185b706cdbbb4c142fad9101b730bff12e4c4b36741cf39ac8c53c45af7799bcd001475845a50d84e1e4cde524276fe9
    { 62, 66, 43, 141, 78, 75, 82, 50, 174, 110, 97, 46, 95, 67, 219, 18, 24, 91, 112, 108, 219, 187, 76, 20, 47, 173, 145, 1, 183, 48, 191, 241, 46, 76, 75, 54, 116, 28, 243, 154, 200, 197, 60, 69, 175, 119, 153, 188, 208, 1, 71, 88, 69, 165, 13, 132, 225, 228, 205, 229, 36, 39, 111, 233 },
        // 35ff1bf278ada14e964443e84778fddd52f6bc8f57cd86bd22eab891a59e5db13a6cdd02469d3b33b3550dea5be5b8aa68f3d20395e185e41ca374fa3b26d795
    { 53, 255, 27, 242, 120, 173, 161, 78, 150, 68, 67, 232, 71, 120, 253, 221, 82, 246, 188, 143, 87, 205, 134, 189, 34, 234, 184, 145, 165, 158, 93, 177, 58, 108, 221, 2, 70, 157, 59, 51, 179, 85, 13, 234, 91, 229, 184, 170, 104, 243, 210, 3, 149, 225, 133, 228, 28, 163, 116, 250, 59, 38, 215, 149 },
        // 0094e93db8f0c4117fb32d2c534b2770cf3d6ccdc64c7cda342081afa6947d3f5422176faae12303389ff351e70641177a1b4386fae7613f2f4a3537dd601a50
    { 0, 148, 233, 61, 184, 240, 196, 17, 127, 179, 45, 44, 83, 75, 39, 112, 207, 61, 108, 205, 198, 76, 124, 218, 52, 32, 129, 175, 166, 148, 125, 63, 84, 34, 23, 111, 170, 225, 35, 3, 56, 159, 243, 81, 231, 6, 65, 23, 122, 27, 67, 134, 250, 231, 97, 63, 47, 74, 53, 55, 221, 96, 26, 80 }
};  // decoded

////////////////////////////////////////////////////////////////////////////////

// additional test cases adapted from: https://github.com/bitcoinjs/bip66/blob/master/test/fixtures.json
namespace valid {
constexpr const uint8_t encoded[VALID_ENCODED_COUNT][VALID_ENCODED_LENGTH] = {
        // len[0] + 3044022029db2d5f4e1dcc04e19266cce3cb135865784c62ab653b307f0e0bb744f5c2aa022000a97f5826912cac8b44d9f577a26f169a2f8db781f2ddb7de2bc886e93b6844
    { 70, 48, 68, 2, 32, 41, 219, 45, 95, 78, 29, 204, 4, 225, 146, 102, 204, 227, 203, 19, 88, 101, 120, 76, 98, 171, 101, 59, 48, 127, 14, 11, 183, 68, 245, 194, 170, 2, 32, 0, 169, 127, 88, 38, 145, 44, 172, 139, 68, 217, 245, 119, 162, 111, 22, 154, 47, 141, 183, 129, 242, 221, 183, 222, 43, 200, 134, 233, 59, 104, 68 },
        // len[0] + 304302201ea1fdff81b3a271659df4aad19bc4ef83def389131a36358fe64b245632e777021f29e164658be9ce810921bf81d6b86694785a79ea1e52dbfa5105148d1f0bc1
    { 69, 48, 67, 2, 32, 30, 161, 253, 255, 129, 179, 162, 113, 101, 157, 244, 170, 209, 155, 196, 239, 131, 222, 243, 137, 19, 26, 54, 53, 143, 230, 75, 36, 86, 50, 231, 119, 2, 31, 41, 225, 100, 101, 139, 233, 206, 129, 9, 33, 191, 129, 214, 184, 102, 148, 120, 90, 121, 234, 30, 82, 219, 250, 81, 5, 20, 141, 31, 11, 193 },
        // len[0] + 304402201b19519b38ca1e6813cd25649ad36be8bc6a6f2ad9758089c429acd9ce0b572f02203bf32193c8a3a3de1f847cd6e6eebf43c96df1ffa4d7fe920f8f71708920c65f
    { 70, 48, 68, 2, 32, 27, 25, 81, 155, 56, 202, 30, 104, 19, 205, 37, 100, 154, 211, 107, 232, 188, 106, 111, 42, 217, 117, 128, 137, 196, 41, 172, 217, 206, 11, 87, 47, 2, 32, 59, 243, 33, 147, 200, 163, 163, 222, 31, 132, 124, 214, 230, 238, 191, 67, 201, 109, 241, 255, 164, 215, 254, 146, 15, 143, 113, 112, 137, 32, 198, 95 },
        // len[0] + 3044022000c8da1836747d05a6a3d2c395825edce827147d15909e66939a5037d5916e6f022017823c2da62f539d7f8e1e186eaea7a401ab3c077dcfc44aeaf3e13fac99bdbc
    { 70, 48, 68, 2, 32, 0, 200, 218, 24, 54, 116, 125, 5, 166, 163, 210, 195, 149, 130, 94, 220, 232, 39, 20, 125, 21, 144, 158, 102, 147, 154, 80, 55, 213, 145, 110, 111, 2, 32, 23, 130, 60, 45, 166, 47, 83, 157, 127, 142, 30, 24, 110, 174, 167, 164, 1, 171, 60, 7, 125, 207, 196, 74, 234, 243, 225, 63, 172, 153, 189, 188 },
        // len[0] + 3042021e2ff2609c8dc0392d3731a2c6312841e09c76f10b83e2b52604dc84886dd502200090ac80e787c063618192bc04758e6666d0179c377fb2f3d6105d58000f33ac
    { 68, 48, 66, 2, 30, 47, 242, 96, 156, 141, 192, 57, 45, 55, 49, 162, 198, 49, 40, 65, 224, 156, 118, 241, 11, 131, 226, 181, 38, 4, 220, 132, 136, 109, 213, 2, 32, 0, 144, 172, 128, 231, 135, 192, 99, 97, 129, 146, 188, 4, 117, 142, 102, 102, 208, 23, 156, 55, 127, 178, 243, 214, 16, 93, 88, 0, 15, 51, 172 },
        // len[0] + 3041021d00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb02202e7aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e9
    { 67, 48, 65, 2, 29, 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187, 2, 32, 46, 122, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233 },
        // len[0] + 3042021d00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb0221008aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e925
    { 68, 48, 66, 2, 29, 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187, 2, 33, 0, 138, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233, 37 },
        // len[0] + 303e021d00c1d545da2e4edfbc65e9267d3c0a6fdda41793d0fd945f15acbcf0dd021d009acffda3ca5e7c349c35ba606f0a8f1ec7815b653b51695ca9ee69a6
    { 64, 48, 62, 2, 29, 0, 193, 213, 69, 218, 46, 78, 223, 188, 101, 233, 38, 125, 60, 10, 111, 221, 164, 23, 147, 208, 253, 148, 95, 21, 172, 188, 240, 221, 2, 29, 0, 154, 207, 253, 163, 202, 94, 124, 52, 156, 53, 186, 96, 111, 10, 143, 30, 199, 129, 91, 101, 59, 81, 105, 92, 169, 238, 105, 166 },
        // len[0] + 3006020100020100
    { 8, 48, 6, 2, 1, 0, 2, 1, 0 }
};  //  encoded

constexpr const uint8_t r[VALID_ENCODED_COUNT][VALID_R_LENGTH] = {
        // len[0] + 29db2d5f4e1dcc04e19266cce3cb135865784c62ab653b307f0e0bb744f5c2aa
    { 32, 41, 219, 45, 95, 78, 29, 204, 4, 225, 146, 102, 204, 227, 203, 19, 88, 101, 120, 76, 98, 171, 101, 59, 48, 127, 14, 11, 183, 68, 245, 194, 170 },
        // len[0] + 1ea1fdff81b3a271659df4aad19bc4ef83def389131a36358fe64b245632e777
    { 32, 30, 161, 253, 255, 129, 179, 162, 113, 101, 157, 244, 170, 209, 155, 196, 239, 131, 222, 243, 137, 19, 26, 54, 53, 143, 230, 75, 36, 86, 50, 231, 119 },
        // len[0] + 1b19519b38ca1e6813cd25649ad36be8bc6a6f2ad9758089c429acd9ce0b572f
    { 32, 27, 25, 81, 155, 56, 202, 30, 104, 19, 205, 37, 100, 154, 211, 107, 232, 188, 106, 111, 42, 217, 117, 128, 137, 196, 41, 172, 217, 206, 11, 87, 47 },
        // len[0] + 00c8da1836747d05a6a3d2c395825edce827147d15909e66939a5037d5916e6f
    { 32, 0, 200, 218, 24, 54, 116, 125, 5, 166, 163, 210, 195, 149, 130, 94, 220, 232, 39, 20, 125, 21, 144, 158, 102, 147, 154, 80, 55, 213, 145, 110, 111 },
        // len[0] + 2ff2609c8dc0392d3731a2c6312841e09c76f10b83e2b52604dc84886dd5
    { 30, 47, 242, 96, 156, 141, 192, 57, 45, 55, 49, 162, 198, 49, 40, 65, 224, 156, 118, 241, 11, 131, 226, 181, 38, 4, 220, 132, 136, 109, 213 },
        // len[0] + 00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb
    { 29, 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187 },
        // len[0] + 00feb1a12c27e5fe261acc64c0923add082573883e0800d8e4080fa9bb
    { 29, 0, 254, 177, 161, 44, 39, 229, 254, 38, 26, 204, 100, 192, 146, 58, 221, 8, 37, 115, 136, 62, 8, 0, 216, 228, 8, 15, 169, 187 },
        // len[0] + 00c1d545da2e4edfbc65e9267d3c0a6fdda41793d0fd945f15acbcf0dd
    { 29, 0, 193, 213, 69, 218, 46, 78, 223, 188, 101, 233, 38, 125, 60, 10, 111, 221, 164, 23, 147, 208, 253, 148, 95, 21, 172, 188, 240, 221 },
        // len[0] + 0
    { 1, 0 }
};  // r

constexpr const uint8_t s[VALID_ENCODED_COUNT][VALID_S_LENGTH] = {
        // len[0] + 00a97f5826912cac8b44d9f577a26f169a2f8db781f2ddb7de2bc886e93b6844
    { 32, 0, 169, 127, 88, 38, 145, 44, 172, 139, 68, 217, 245, 119, 162, 111, 22, 154, 47, 141, 183, 129, 242, 221, 183, 222, 43, 200, 134, 233, 59, 104, 68 },
        // len[0] + 29e164658be9ce810921bf81d6b86694785a79ea1e52dbfa5105148d1f0bc1
    { 31, 41, 225, 100, 101, 139, 233, 206, 129, 9, 33, 191, 129, 214, 184, 102, 148, 120, 90, 121, 234, 30, 82, 219, 250, 81, 5, 20, 141, 31, 11, 193 },
        // len[0] + 3bf32193c8a3a3de1f847cd6e6eebf43c96df1ffa4d7fe920f8f71708920c65f
    { 32, 59, 243, 33, 147, 200, 163, 163, 222, 31, 132, 124, 214, 230, 238, 191, 67, 201, 109, 241, 255, 164, 215, 254, 146, 15, 143, 113, 112, 137, 32, 198, 95 },
        // len[0] + 17823c2da62f539d7f8e1e186eaea7a401ab3c077dcfc44aeaf3e13fac99bdbc
    { 32, 23, 130, 60, 45, 166, 47, 83, 157, 127, 142, 30, 24, 110, 174, 167, 164, 1, 171, 60, 7, 125, 207, 196, 74, 234, 243, 225, 63, 172, 153, 189, 188 },
        // len[0] + 0090ac80e787c063618192bc04758e6666d0179c377fb2f3d6105d58000f33ac
    { 32, 0, 144, 172, 128, 231, 135, 192, 99, 97, 129, 146, 188, 4, 117, 142, 102, 102, 208, 23, 156, 55, 127, 178, 243, 214, 16, 93, 88, 0, 15, 51, 172 },
        // len[0] + 2e7aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e9
    { 32, 46, 122, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233 },
        // len[0] + 008aeb97f4046ea3be60d2896a19c8dc269ab5eb2de968912cd52a076a0a42e925
    { 33, 0, 138, 235, 151, 244, 4, 110, 163, 190, 96, 210, 137, 106, 25, 200, 220, 38, 154, 181, 235, 45, 233, 104, 145, 44, 213, 42, 7, 106, 10, 66, 233, 37 },
        // len[0] + 009acffda3ca5e7c349c35ba606f0a8f1ec7815b653b51695ca9ee69a6
    { 29, 0, 154, 207, 253, 163, 202, 94, 124, 52, 156, 53, 186, 96, 111, 10, 143, 30, 199, 129, 91, 101, 59, 81, 105, 92, 169, 238, 105, 166 },
        // len[0] + 0
    { 1, 0 }
};  // s
}  // namespace valid

////////////////////////////////////////////////////////////////////////////////

namespace invalid {
constexpr const uint8_t encoded[INVALID_ENCODED_COUNT][INVALID_ENCODED_LENGTH] = {
        // DER sequence length is too short
        // len[0] + ffffffffffffff
    { 7, 255, 255, 255, 255, 255, 255, 255 },
        // DER sequence length is too long
        // len[0] + ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
    { 73, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 },
        // Expected DER sequence
        // len[0] + 00ffff0400ffffff020400ffffff
    { 14, 0, 255, 255, 4, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
        // DER sequence length is invalid
        // len[0] + 30ff020400ffffff020400ffffff
    { 14, 48, 255, 2, 4, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
        // DER sequence length is invalid
        // len[0] + 300c030400ffffff030400ffffff0000
    { 16, 48, 12, 3, 4, 0, 255, 255, 255, 3, 4, 0, 255, 255, 255, 0, 0 },
        // Expected DER integer
        // len[0] + 300cff0400ffffff020400ffffff
    { 14, 48, 12, 255, 4, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
        // Expected DER integer
        // len[0] + 300c020200ffffff020400ffffff
    { 14, 48, 12, 2, 2, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
        // R length is zero
        // len[0] + 30080200020400ffffff
    { 10, 48, 8, 2, 0, 2, 4, 0, 255, 255, 255 },
        // S length is zero
        // len[0] + 3008020400ffffff0200
    { 10, 48, 8, 2, 4, 0, 255, 255, 255, 2, 0 },
        // R length is too long
        // len[0] + 300c02dd00ffffff020400ffffff
    { 14, 48, 12, 2, 221, 0, 255, 255, 255, 2, 4, 0, 255, 255, 255 },
        // S length is invalid
        // len[0] + 300c020400ffffff02dd00ffffff
    { 14, 48, 12, 2, 4, 0, 255, 255, 255, 2, 221, 0, 255, 255, 255 },
        // R value is negative
        // len[0] + 300c020480000000020400ffffff
    { 14, 48, 12, 2, 4, 128, 0, 0, 0, 2, 4, 0, 255, 255, 255 },
        // S value is negative
        // len[0] + 300c020400ffffff020480000000
    { 14, 48, 12, 2, 4, 0, 255, 255, 255, 2, 4, 128, 0, 0, 0 },
        // R value excessively padded
        // len[0] + 300c02040000ffff020400ffffff
    { 14, 48, 12, 2, 4, 0, 0, 255, 255, 2, 4, 0, 255, 255, 255 },
        // S value excessively padded
        // len[0] + 300c020400ffffff02040000ffff
    { 14, 48, 12, 2, 4, 0, 255, 255, 255, 2, 4, 0, 0, 255, 255 }
};  // der

constexpr const uint8_t r[INVALID_RS_COUNT][INVALID_RS_LENGTH] = {
        // R length is zero
        // len[0] + r: ""
    { 0 },
        // len[0] + r: 0080000000000000000000000000000000000000000000000000000000000000
    { 32, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // R value is negative
        // len[0] + r: 80
    { 1, 128 },
        // len[0] + r: 7f
    { 1, 127 },
        // R value excessively padded
        // len[0] + r: 0010000000000000000000000000000000000000000000000000000000000000
    { 32, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // len[0] + r: 0080000000000000000000000000000000000000000000000000000000000000
    { 32, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // R length is too long
        // len[0] + r: 00800000000000000000000000000000000000000000000000000000000000000000
    { 34, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // len[0] + r: 008000000000000000000000000000000000000000000000000000000000000000
    { 33, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};  // r

constexpr const uint8_t  s[INVALID_RS_COUNT][INVALID_RS_LENGTH] = {
        //  s: 0080000000000000000000000000000000000000000000000000000000000000
    { 32, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // s length is zero
        // len[0] + s: ""
    { 0 },
        // len[0] + s: 7f
    { 1, 127 },
        // S value is negative
        // len[0] + s: 80
    { 1, 128 },
        // len[0] + s: 0080000000000000000000000000000000000000000000000000000000000000
    { 32, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // S value excessively padded
        // len[0] + s: 0010000000000000000000000000000000000000000000000000000000000000
    { 32, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // len[0] + s: 008000000000000000000000000000000000000000000000000000000000000000
    { 33, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // S length is too long
        // len[0] + s: 00800000000000000000000000000000000000000000000000000000000000000000
    { 34, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
}; // s
}  // namespace invalid
}  // namespace test_cases

////////////////////////////////////////////////////////////////////////////////

#endif