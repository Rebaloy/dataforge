/*=============================================================================
    Copyright (c) 2022 Alexander Pototskiy

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include "../utility/data_ops.hpp"

namespace dataforge::blowfish_detail {

inline const int rounds = 16;
using word_type = uint_least32_t;

inline const word_type P_iv[rounds + 2] =
{
  UINT32_C(0x243f6a88), UINT32_C(0x85a308d3), UINT32_C(0x13198a2e),
  UINT32_C(0x03707344), UINT32_C(0xa4093822), UINT32_C(0x299f31d0),
  UINT32_C(0x082efa98), UINT32_C(0xec4e6c89), UINT32_C(0x452821e6),
  UINT32_C(0x38d01377), UINT32_C(0xbe5466cf), UINT32_C(0x34e90c6c),
  UINT32_C(0xc0ac29b7), UINT32_C(0xc97c50dd), UINT32_C(0x3f84d5b5),
  UINT32_C(0xb5470917), UINT32_C(0x9216d5d9), UINT32_C(0x8979fb1b)
};

inline const word_type S_iv[4][256] =
{
  {
    UINT32_C(0xd1310ba6), UINT32_C(0x98dfb5ac), UINT32_C(0x2ffd72db),
    UINT32_C(0xd01adfb7), UINT32_C(0xb8e1afed), UINT32_C(0x6a267e96),
    UINT32_C(0xba7c9045), UINT32_C(0xf12c7f99), UINT32_C(0x24a19947),
    UINT32_C(0xb3916cf7), UINT32_C(0x0801f2e2), UINT32_C(0x858efc16),
    UINT32_C(0x636920d8), UINT32_C(0x71574e69), UINT32_C(0xa458fea3),
    UINT32_C(0xf4933d7e), UINT32_C(0x0d95748f), UINT32_C(0x728eb658),
    UINT32_C(0x718bcd58), UINT32_C(0x82154aee), UINT32_C(0x7b54a41d),
    UINT32_C(0xc25a59b5), UINT32_C(0x9c30d539), UINT32_C(0x2af26013),
    UINT32_C(0xc5d1b023), UINT32_C(0x286085f0), UINT32_C(0xca417918),
    UINT32_C(0xb8db38ef), UINT32_C(0x8e79dcb0), UINT32_C(0x603a180e),
    UINT32_C(0x6c9e0e8b), UINT32_C(0xb01e8a3e), UINT32_C(0xd71577c1),
    UINT32_C(0xbd314b27), UINT32_C(0x78af2fda), UINT32_C(0x55605c60),
    UINT32_C(0xe65525f3), UINT32_C(0xaa55ab94), UINT32_C(0x57489862),
    UINT32_C(0x63e81440), UINT32_C(0x55ca396a), UINT32_C(0x2aab10b6),
    UINT32_C(0xb4cc5c34), UINT32_C(0x1141e8ce), UINT32_C(0xa15486af),
    UINT32_C(0x7c72e993), UINT32_C(0xb3ee1411), UINT32_C(0x636fbc2a),
    UINT32_C(0x2ba9c55d), UINT32_C(0x741831f6), UINT32_C(0xce5c3e16),
    UINT32_C(0x9b87931e), UINT32_C(0xafd6ba33), UINT32_C(0x6c24cf5c),
    UINT32_C(0x7a325381), UINT32_C(0x28958677), UINT32_C(0x3b8f4898),
    UINT32_C(0x6b4bb9af), UINT32_C(0xc4bfe81b), UINT32_C(0x66282193),
    UINT32_C(0x61d809cc), UINT32_C(0xfb21a991), UINT32_C(0x487cac60),
    UINT32_C(0x5dec8032), UINT32_C(0xef845d5d), UINT32_C(0xe98575b1),
    UINT32_C(0xdc262302), UINT32_C(0xeb651b88), UINT32_C(0x23893e81),
    UINT32_C(0xd396acc5), UINT32_C(0x0f6d6ff3), UINT32_C(0x83f44239),
    UINT32_C(0x2e0b4482), UINT32_C(0xa4842004), UINT32_C(0x69c8f04a),
    UINT32_C(0x9e1f9b5e), UINT32_C(0x21c66842), UINT32_C(0xf6e96c9a),
    UINT32_C(0x670c9c61), UINT32_C(0xabd388f0), UINT32_C(0x6a51a0d2),
    UINT32_C(0xd8542f68), UINT32_C(0x960fa728), UINT32_C(0xab5133a3),
    UINT32_C(0x6eef0b6c), UINT32_C(0x137a3be4), UINT32_C(0xba3bf050),
    UINT32_C(0x7efb2a98), UINT32_C(0xa1f1651d), UINT32_C(0x39af0176),
    UINT32_C(0x66ca593e), UINT32_C(0x82430e88), UINT32_C(0x8cee8619),
    UINT32_C(0x456f9fb4), UINT32_C(0x7d84a5c3), UINT32_C(0x3b8b5ebe),
    UINT32_C(0xe06f75d8), UINT32_C(0x85c12073), UINT32_C(0x401a449f),
    UINT32_C(0x56c16aa6), UINT32_C(0x4ed3aa62), UINT32_C(0x363f7706),
    UINT32_C(0x1bfedf72), UINT32_C(0x429b023d), UINT32_C(0x37d0d724),
    UINT32_C(0xd00a1248), UINT32_C(0xdb0fead3), UINT32_C(0x49f1c09b),
    UINT32_C(0x075372c9), UINT32_C(0x80991b7b), UINT32_C(0x25d479d8),
    UINT32_C(0xf6e8def7), UINT32_C(0xe3fe501a), UINT32_C(0xb6794c3b),
    UINT32_C(0x976ce0bd), UINT32_C(0x04c006ba), UINT32_C(0xc1a94fb6),
    UINT32_C(0x409f60c4), UINT32_C(0x5e5c9ec2), UINT32_C(0x196a2463),
    UINT32_C(0x68fb6faf), UINT32_C(0x3e6c53b5), UINT32_C(0x1339b2eb),
    UINT32_C(0x3b52ec6f), UINT32_C(0x6dfc511f), UINT32_C(0x9b30952c),
    UINT32_C(0xcc814544), UINT32_C(0xaf5ebd09), UINT32_C(0xbee3d004),
    UINT32_C(0xde334afd), UINT32_C(0x660f2807), UINT32_C(0x192e4bb3),
    UINT32_C(0xc0cba857), UINT32_C(0x45c8740f), UINT32_C(0xd20b5f39),
    UINT32_C(0xb9d3fbdb), UINT32_C(0x5579c0bd), UINT32_C(0x1a60320a),
    UINT32_C(0xd6a100c6), UINT32_C(0x402c7279), UINT32_C(0x679f25fe),
    UINT32_C(0xfb1fa3cc), UINT32_C(0x8ea5e9f8), UINT32_C(0xdb3222f8),
    UINT32_C(0x3c7516df), UINT32_C(0xfd616b15), UINT32_C(0x2f501ec8),
    UINT32_C(0xad0552ab), UINT32_C(0x323db5fa), UINT32_C(0xfd238760),
    UINT32_C(0x53317b48), UINT32_C(0x3e00df82), UINT32_C(0x9e5c57bb),
    UINT32_C(0xca6f8ca0), UINT32_C(0x1a87562e), UINT32_C(0xdf1769db),
    UINT32_C(0xd542a8f6), UINT32_C(0x287effc3), UINT32_C(0xac6732c6),
    UINT32_C(0x8c4f5573), UINT32_C(0x695b27b0), UINT32_C(0xbbca58c8),
    UINT32_C(0xe1ffa35d), UINT32_C(0xb8f011a0), UINT32_C(0x10fa3d98),
    UINT32_C(0xfd2183b8), UINT32_C(0x4afcb56c), UINT32_C(0x2dd1d35b),
    UINT32_C(0x9a53e479), UINT32_C(0xb6f84565), UINT32_C(0xd28e49bc),
    UINT32_C(0x4bfb9790), UINT32_C(0xe1ddf2da), UINT32_C(0xa4cb7e33),
    UINT32_C(0x62fb1341), UINT32_C(0xcee4c6e8), UINT32_C(0xef20cada),
    UINT32_C(0x36774c01), UINT32_C(0xd07e9efe), UINT32_C(0x2bf11fb4),
    UINT32_C(0x95dbda4d), UINT32_C(0xae909198), UINT32_C(0xeaad8e71),
    UINT32_C(0x6b93d5a0), UINT32_C(0xd08ed1d0), UINT32_C(0xafc725e0),
    UINT32_C(0x8e3c5b2f), UINT32_C(0x8e7594b7), UINT32_C(0x8ff6e2fb),
    UINT32_C(0xf2122b64), UINT32_C(0x8888b812), UINT32_C(0x900df01c),
    UINT32_C(0x4fad5ea0), UINT32_C(0x688fc31c), UINT32_C(0xd1cff191),
    UINT32_C(0xb3a8c1ad), UINT32_C(0x2f2f2218), UINT32_C(0xbe0e1777),
    UINT32_C(0xea752dfe), UINT32_C(0x8b021fa1), UINT32_C(0xe5a0cc0f),
    UINT32_C(0xb56f74e8), UINT32_C(0x18acf3d6), UINT32_C(0xce89e299),
    UINT32_C(0xb4a84fe0), UINT32_C(0xfd13e0b7), UINT32_C(0x7cc43b81),
    UINT32_C(0xd2ada8d9), UINT32_C(0x165fa266), UINT32_C(0x80957705),
    UINT32_C(0x93cc7314), UINT32_C(0x211a1477), UINT32_C(0xe6ad2065),
    UINT32_C(0x77b5fa86), UINT32_C(0xc75442f5), UINT32_C(0xfb9d35cf),
    UINT32_C(0xebcdaf0c), UINT32_C(0x7b3e89a0), UINT32_C(0xd6411bd3),
    UINT32_C(0xae1e7e49), UINT32_C(0x00250e2d), UINT32_C(0x2071b35e),
    UINT32_C(0x226800bb), UINT32_C(0x57b8e0af), UINT32_C(0x2464369b),
    UINT32_C(0xf009b91e), UINT32_C(0x5563911d), UINT32_C(0x59dfa6aa),
    UINT32_C(0x78c14389), UINT32_C(0xd95a537f), UINT32_C(0x207d5ba2),
    UINT32_C(0x02e5b9c5), UINT32_C(0x83260376), UINT32_C(0x6295cfa9),
    UINT32_C(0x11c81968), UINT32_C(0x4e734a41), UINT32_C(0xb3472dca),
    UINT32_C(0x7b14a94a), UINT32_C(0x1b510052), UINT32_C(0x9a532915),
    UINT32_C(0xd60f573f), UINT32_C(0xbc9bc6e4), UINT32_C(0x2b60a476),
    UINT32_C(0x81e67400), UINT32_C(0x08ba6fb5), UINT32_C(0x571be91f),
    UINT32_C(0xf296ec6b), UINT32_C(0x2a0dd915), UINT32_C(0xb6636521),
    UINT32_C(0xe7b9f9b6), UINT32_C(0xff34052e), UINT32_C(0xc5855664),
    UINT32_C(0x53b02d5d), UINT32_C(0xa99f8fa1), UINT32_C(0x08ba4799),
    UINT32_C(0x6e85076a)
  },
  {
    UINT32_C(0x4b7a70e9), UINT32_C(0xb5b32944), UINT32_C(0xdb75092e),
    UINT32_C(0xc4192623), UINT32_C(0xad6ea6b0), UINT32_C(0x49a7df7d),
    UINT32_C(0x9cee60b8), UINT32_C(0x8fedb266), UINT32_C(0xecaa8c71),
    UINT32_C(0x699a17ff), UINT32_C(0x5664526c), UINT32_C(0xc2b19ee1),
    UINT32_C(0x193602a5), UINT32_C(0x75094c29), UINT32_C(0xa0591340),
    UINT32_C(0xe4183a3e), UINT32_C(0x3f54989a), UINT32_C(0x5b429d65),
    UINT32_C(0x6b8fe4d6), UINT32_C(0x99f73fd6), UINT32_C(0xa1d29c07),
    UINT32_C(0xefe830f5), UINT32_C(0x4d2d38e6), UINT32_C(0xf0255dc1),
    UINT32_C(0x4cdd2086), UINT32_C(0x8470eb26), UINT32_C(0x6382e9c6),
    UINT32_C(0x021ecc5e), UINT32_C(0x09686b3f), UINT32_C(0x3ebaefc9),
    UINT32_C(0x3c971814), UINT32_C(0x6b6a70a1), UINT32_C(0x687f3584),
    UINT32_C(0x52a0e286), UINT32_C(0xb79c5305), UINT32_C(0xaa500737),
    UINT32_C(0x3e07841c), UINT32_C(0x7fdeae5c), UINT32_C(0x8e7d44ec),
    UINT32_C(0x5716f2b8), UINT32_C(0xb03ada37), UINT32_C(0xf0500c0d),
    UINT32_C(0xf01c1f04), UINT32_C(0x0200b3ff), UINT32_C(0xae0cf51a),
    UINT32_C(0x3cb574b2), UINT32_C(0x25837a58), UINT32_C(0xdc0921bd),
    UINT32_C(0xd19113f9), UINT32_C(0x7ca92ff6), UINT32_C(0x94324773),
    UINT32_C(0x22f54701), UINT32_C(0x3ae5e581), UINT32_C(0x37c2dadc),
    UINT32_C(0xc8b57634), UINT32_C(0x9af3dda7), UINT32_C(0xa9446146),
    UINT32_C(0x0fd0030e), UINT32_C(0xecc8c73e), UINT32_C(0xa4751e41),
    UINT32_C(0xe238cd99), UINT32_C(0x3bea0e2f), UINT32_C(0x3280bba1),
    UINT32_C(0x183eb331), UINT32_C(0x4e548b38), UINT32_C(0x4f6db908),
    UINT32_C(0x6f420d03), UINT32_C(0xf60a04bf), UINT32_C(0x2cb81290),
    UINT32_C(0x24977c79), UINT32_C(0x5679b072), UINT32_C(0xbcaf89af),
    UINT32_C(0xde9a771f), UINT32_C(0xd9930810), UINT32_C(0xb38bae12),
    UINT32_C(0xdccf3f2e), UINT32_C(0x5512721f), UINT32_C(0x2e6b7124),
    UINT32_C(0x501adde6), UINT32_C(0x9f84cd87), UINT32_C(0x7a584718),
    UINT32_C(0x7408da17), UINT32_C(0xbc9f9abc), UINT32_C(0xe94b7d8c),
    UINT32_C(0xec7aec3a), UINT32_C(0xdb851dfa), UINT32_C(0x63094366),
    UINT32_C(0xc464c3d2), UINT32_C(0xef1c1847), UINT32_C(0x3215d908),
    UINT32_C(0xdd433b37), UINT32_C(0x24c2ba16), UINT32_C(0x12a14d43),
    UINT32_C(0x2a65c451), UINT32_C(0x50940002), UINT32_C(0x133ae4dd),
    UINT32_C(0x71dff89e), UINT32_C(0x10314e55), UINT32_C(0x81ac77d6),
    UINT32_C(0x5f11199b), UINT32_C(0x043556f1), UINT32_C(0xd7a3c76b),
    UINT32_C(0x3c11183b), UINT32_C(0x5924a509), UINT32_C(0xf28fe6ed),
    UINT32_C(0x97f1fbfa), UINT32_C(0x9ebabf2c), UINT32_C(0x1e153c6e),
    UINT32_C(0x86e34570), UINT32_C(0xeae96fb1), UINT32_C(0x860e5e0a),
    UINT32_C(0x5a3e2ab3), UINT32_C(0x771fe71c), UINT32_C(0x4e3d06fa),
    UINT32_C(0x2965dcb9), UINT32_C(0x99e71d0f), UINT32_C(0x803e89d6),
    UINT32_C(0x5266c825), UINT32_C(0x2e4cc978), UINT32_C(0x9c10b36a),
    UINT32_C(0xc6150eba), UINT32_C(0x94e2ea78), UINT32_C(0xa5fc3c53),
    UINT32_C(0x1e0a2df4), UINT32_C(0xf2f74ea7), UINT32_C(0x361d2b3d),
    UINT32_C(0x1939260f), UINT32_C(0x19c27960), UINT32_C(0x5223a708),
    UINT32_C(0xf71312b6), UINT32_C(0xebadfe6e), UINT32_C(0xeac31f66),
    UINT32_C(0xe3bc4595), UINT32_C(0xa67bc883), UINT32_C(0xb17f37d1),
    UINT32_C(0x018cff28), UINT32_C(0xc332ddef), UINT32_C(0xbe6c5aa5),
    UINT32_C(0x65582185), UINT32_C(0x68ab9802), UINT32_C(0xeecea50f),
    UINT32_C(0xdb2f953b), UINT32_C(0x2aef7dad), UINT32_C(0x5b6e2f84),
    UINT32_C(0x1521b628), UINT32_C(0x29076170), UINT32_C(0xecdd4775),
    UINT32_C(0x619f1510), UINT32_C(0x13cca830), UINT32_C(0xeb61bd96),
    UINT32_C(0x0334fe1e), UINT32_C(0xaa0363cf), UINT32_C(0xb5735c90),
    UINT32_C(0x4c70a239), UINT32_C(0xd59e9e0b), UINT32_C(0xcbaade14),
    UINT32_C(0xeecc86bc), UINT32_C(0x60622ca7), UINT32_C(0x9cab5cab),
    UINT32_C(0xb2f3846e), UINT32_C(0x648b1eaf), UINT32_C(0x19bdf0ca),
    UINT32_C(0xa02369b9), UINT32_C(0x655abb50), UINT32_C(0x40685a32),
    UINT32_C(0x3c2ab4b3), UINT32_C(0x319ee9d5), UINT32_C(0xc021b8f7),
    UINT32_C(0x9b540b19), UINT32_C(0x875fa099), UINT32_C(0x95f7997e),
    UINT32_C(0x623d7da8), UINT32_C(0xf837889a), UINT32_C(0x97e32d77),
    UINT32_C(0x11ed935f), UINT32_C(0x16681281), UINT32_C(0x0e358829),
    UINT32_C(0xc7e61fd6), UINT32_C(0x96dedfa1), UINT32_C(0x7858ba99),
    UINT32_C(0x57f584a5), UINT32_C(0x1b227263), UINT32_C(0x9b83c3ff),
    UINT32_C(0x1ac24696), UINT32_C(0xcdb30aeb), UINT32_C(0x532e3054),
    UINT32_C(0x8fd948e4), UINT32_C(0x6dbc3128), UINT32_C(0x58ebf2ef),
    UINT32_C(0x34c6ffea), UINT32_C(0xfe28ed61), UINT32_C(0xee7c3c73),
    UINT32_C(0x5d4a14d9), UINT32_C(0xe864b7e3), UINT32_C(0x42105d14),
    UINT32_C(0x203e13e0), UINT32_C(0x45eee2b6), UINT32_C(0xa3aaabea),
    UINT32_C(0xdb6c4f15), UINT32_C(0xfacb4fd0), UINT32_C(0xc742f442),
    UINT32_C(0xef6abbb5), UINT32_C(0x654f3b1d), UINT32_C(0x41cd2105),
    UINT32_C(0xd81e799e), UINT32_C(0x86854dc7), UINT32_C(0xe44b476a),
    UINT32_C(0x3d816250), UINT32_C(0xcf62a1f2), UINT32_C(0x5b8d2646),
    UINT32_C(0xfc8883a0), UINT32_C(0xc1c7b6a3), UINT32_C(0x7f1524c3),
    UINT32_C(0x69cb7492), UINT32_C(0x47848a0b), UINT32_C(0x5692b285),
    UINT32_C(0x095bbf00), UINT32_C(0xad19489d), UINT32_C(0x1462b174),
    UINT32_C(0x23820e00), UINT32_C(0x58428d2a), UINT32_C(0x0c55f5ea),
    UINT32_C(0x1dadf43e), UINT32_C(0x233f7061), UINT32_C(0x3372f092),
    UINT32_C(0x8d937e41), UINT32_C(0xd65fecf1), UINT32_C(0x6c223bdb),
    UINT32_C(0x7cde3759), UINT32_C(0xcbee7460), UINT32_C(0x4085f2a7),
    UINT32_C(0xce77326e), UINT32_C(0xa6078084), UINT32_C(0x19f8509e),
    UINT32_C(0xe8efd855), UINT32_C(0x61d99735), UINT32_C(0xa969a7aa),
    UINT32_C(0xc50c06c2), UINT32_C(0x5a04abfc), UINT32_C(0x800bcadc),
    UINT32_C(0x9e447a2e), UINT32_C(0xc3453484), UINT32_C(0xfdd56705),
    UINT32_C(0x0e1e9ec9), UINT32_C(0xdb73dbd3), UINT32_C(0x105588cd),
    UINT32_C(0x675fda79), UINT32_C(0xe3674340), UINT32_C(0xc5c43465),
    UINT32_C(0x713e38d8), UINT32_C(0x3d28f89e), UINT32_C(0xf16dff20),
    UINT32_C(0x153e21e7), UINT32_C(0x8fb03d4a), UINT32_C(0xe6e39f2b),
    UINT32_C(0xdb83adf7)
  },
  {
    UINT32_C(0xe93d5a68), UINT32_C(0x948140f7), UINT32_C(0xf64c261c),
    UINT32_C(0x94692934), UINT32_C(0x411520f7), UINT32_C(0x7602d4f7),
    UINT32_C(0xbcf46b2e), UINT32_C(0xd4a20068), UINT32_C(0xd4082471),
    UINT32_C(0x3320f46a), UINT32_C(0x43b7d4b7), UINT32_C(0x500061af),
    UINT32_C(0x1e39f62e), UINT32_C(0x97244546), UINT32_C(0x14214f74),
    UINT32_C(0xbf8b8840), UINT32_C(0x4d95fc1d), UINT32_C(0x96b591af),
    UINT32_C(0x70f4ddd3), UINT32_C(0x66a02f45), UINT32_C(0xbfbc09ec),
    UINT32_C(0x03bd9785), UINT32_C(0x7fac6dd0), UINT32_C(0x31cb8504),
    UINT32_C(0x96eb27b3), UINT32_C(0x55fd3941), UINT32_C(0xda2547e6),
    UINT32_C(0xabca0a9a), UINT32_C(0x28507825), UINT32_C(0x530429f4),
    UINT32_C(0x0a2c86da), UINT32_C(0xe9b66dfb), UINT32_C(0x68dc1462),
    UINT32_C(0xd7486900), UINT32_C(0x680ec0a4), UINT32_C(0x27a18dee),
    UINT32_C(0x4f3ffea2), UINT32_C(0xe887ad8c), UINT32_C(0xb58ce006),
    UINT32_C(0x7af4d6b6), UINT32_C(0xaace1e7c), UINT32_C(0xd3375fec),
    UINT32_C(0xce78a399), UINT32_C(0x406b2a42), UINT32_C(0x20fe9e35),
    UINT32_C(0xd9f385b9), UINT32_C(0xee39d7ab), UINT32_C(0x3b124e8b),
    UINT32_C(0x1dc9faf7), UINT32_C(0x4b6d1856), UINT32_C(0x26a36631),
    UINT32_C(0xeae397b2), UINT32_C(0x3a6efa74), UINT32_C(0xdd5b4332),
    UINT32_C(0x6841e7f7), UINT32_C(0xca7820fb), UINT32_C(0xfb0af54e),
    UINT32_C(0xd8feb397), UINT32_C(0x454056ac), UINT32_C(0xba489527),
    UINT32_C(0x55533a3a), UINT32_C(0x20838d87), UINT32_C(0xfe6ba9b7),
    UINT32_C(0xd096954b), UINT32_C(0x55a867bc), UINT32_C(0xa1159a58),
    UINT32_C(0xcca92963), UINT32_C(0x99e1db33), UINT32_C(0xa62a4a56),
    UINT32_C(0x3f3125f9), UINT32_C(0x5ef47e1c), UINT32_C(0x9029317c),
    UINT32_C(0xfdf8e802), UINT32_C(0x04272f70), UINT32_C(0x80bb155c),
    UINT32_C(0x05282ce3), UINT32_C(0x95c11548), UINT32_C(0xe4c66d22),
    UINT32_C(0x48c1133f), UINT32_C(0xc70f86dc), UINT32_C(0x07f9c9ee),
    UINT32_C(0x41041f0f), UINT32_C(0x404779a4), UINT32_C(0x5d886e17),
    UINT32_C(0x325f51eb), UINT32_C(0xd59bc0d1), UINT32_C(0xf2bcc18f),
    UINT32_C(0x41113564), UINT32_C(0x257b7834), UINT32_C(0x602a9c60),
    UINT32_C(0xdff8e8a3), UINT32_C(0x1f636c1b), UINT32_C(0x0e12b4c2),
    UINT32_C(0x02e1329e), UINT32_C(0xaf664fd1), UINT32_C(0xcad18115),
    UINT32_C(0x6b2395e0), UINT32_C(0x333e92e1), UINT32_C(0x3b240b62),
    UINT32_C(0xeebeb922), UINT32_C(0x85b2a20e), UINT32_C(0xe6ba0d99),
    UINT32_C(0xde720c8c), UINT32_C(0x2da2f728), UINT32_C(0xd0127845),
    UINT32_C(0x95b794fd), UINT32_C(0x647d0862), UINT32_C(0xe7ccf5f0),
    UINT32_C(0x5449a36f), UINT32_C(0x877d48fa), UINT32_C(0xc39dfd27),
    UINT32_C(0xf33e8d1e), UINT32_C(0x0a476341), UINT32_C(0x992eff74),
    UINT32_C(0x3a6f6eab), UINT32_C(0xf4f8fd37), UINT32_C(0xa812dc60),
    UINT32_C(0xa1ebddf8), UINT32_C(0x991be14c), UINT32_C(0xdb6e6b0d),
    UINT32_C(0xc67b5510), UINT32_C(0x6d672c37), UINT32_C(0x2765d43b),
    UINT32_C(0xdcd0e804), UINT32_C(0xf1290dc7), UINT32_C(0xcc00ffa3),
    UINT32_C(0xb5390f92), UINT32_C(0x690fed0b), UINT32_C(0x667b9ffb),
    UINT32_C(0xcedb7d9c), UINT32_C(0xa091cf0b), UINT32_C(0xd9155ea3),
    UINT32_C(0xbb132f88), UINT32_C(0x515bad24), UINT32_C(0x7b9479bf),
    UINT32_C(0x763bd6eb), UINT32_C(0x37392eb3), UINT32_C(0xcc115979),
    UINT32_C(0x8026e297), UINT32_C(0xf42e312d), UINT32_C(0x6842ada7),
    UINT32_C(0xc66a2b3b), UINT32_C(0x12754ccc), UINT32_C(0x782ef11c),
    UINT32_C(0x6a124237), UINT32_C(0xb79251e7), UINT32_C(0x06a1bbe6),
    UINT32_C(0x4bfb6350), UINT32_C(0x1a6b1018), UINT32_C(0x11caedfa),
    UINT32_C(0x3d25bdd8), UINT32_C(0xe2e1c3c9), UINT32_C(0x44421659),
    UINT32_C(0x0a121386), UINT32_C(0xd90cec6e), UINT32_C(0xd5abea2a),
    UINT32_C(0x64af674e), UINT32_C(0xda86a85f), UINT32_C(0xbebfe988),
    UINT32_C(0x64e4c3fe), UINT32_C(0x9dbc8057), UINT32_C(0xf0f7c086),
    UINT32_C(0x60787bf8), UINT32_C(0x6003604d), UINT32_C(0xd1fd8346),
    UINT32_C(0xf6381fb0), UINT32_C(0x7745ae04), UINT32_C(0xd736fccc),
    UINT32_C(0x83426b33), UINT32_C(0xf01eab71), UINT32_C(0xb0804187),
    UINT32_C(0x3c005e5f), UINT32_C(0x77a057be), UINT32_C(0xbde8ae24),
    UINT32_C(0x55464299), UINT32_C(0xbf582e61), UINT32_C(0x4e58f48f),
    UINT32_C(0xf2ddfda2), UINT32_C(0xf474ef38), UINT32_C(0x8789bdc2),
    UINT32_C(0x5366f9c3), UINT32_C(0xc8b38e74), UINT32_C(0xb475f255),
    UINT32_C(0x46fcd9b9), UINT32_C(0x7aeb2661), UINT32_C(0x8b1ddf84),
    UINT32_C(0x846a0e79), UINT32_C(0x915f95e2), UINT32_C(0x466e598e),
    UINT32_C(0x20b45770), UINT32_C(0x8cd55591), UINT32_C(0xc902de4c),
    UINT32_C(0xb90bace1), UINT32_C(0xbb8205d0), UINT32_C(0x11a86248),
    UINT32_C(0x7574a99e), UINT32_C(0xb77f19b6), UINT32_C(0xe0a9dc09),
    UINT32_C(0x662d09a1), UINT32_C(0xc4324633), UINT32_C(0xe85a1f02),
    UINT32_C(0x09f0be8c), UINT32_C(0x4a99a025), UINT32_C(0x1d6efe10),
    UINT32_C(0x1ab93d1d), UINT32_C(0x0ba5a4df), UINT32_C(0xa186f20f),
    UINT32_C(0x2868f169), UINT32_C(0xdcb7da83), UINT32_C(0x573906fe),
    UINT32_C(0xa1e2ce9b), UINT32_C(0x4fcd7f52), UINT32_C(0x50115e01),
    UINT32_C(0xa70683fa), UINT32_C(0xa002b5c4), UINT32_C(0x0de6d027),
    UINT32_C(0x9af88c27), UINT32_C(0x773f8641), UINT32_C(0xc3604c06),
    UINT32_C(0x61a806b5), UINT32_C(0xf0177a28), UINT32_C(0xc0f586e0),
    UINT32_C(0x006058aa), UINT32_C(0x30dc7d62), UINT32_C(0x11e69ed7),
    UINT32_C(0x2338ea63), UINT32_C(0x53c2dd94), UINT32_C(0xc2c21634),
    UINT32_C(0xbbcbee56), UINT32_C(0x90bcb6de), UINT32_C(0xebfc7da1),
    UINT32_C(0xce591d76), UINT32_C(0x6f05e409), UINT32_C(0x4b7c0188),
    UINT32_C(0x39720a3d), UINT32_C(0x7c927c24), UINT32_C(0x86e3725f),
    UINT32_C(0x724d9db9), UINT32_C(0x1ac15bb4), UINT32_C(0xd39eb8fc),
    UINT32_C(0xed545578), UINT32_C(0x08fca5b5), UINT32_C(0xd83d7cd3),
    UINT32_C(0x4dad0fc4), UINT32_C(0x1e50ef5e), UINT32_C(0xb161e6f8),
    UINT32_C(0xa28514d9), UINT32_C(0x6c51133c), UINT32_C(0x6fd5c7e7),
    UINT32_C(0x56e14ec4), UINT32_C(0x362abfce), UINT32_C(0xddc6c837),
    UINT32_C(0xd79a3234), UINT32_C(0x92638212), UINT32_C(0x670efa8e),
    UINT32_C(0x406000e0)
  },
  {
    UINT32_C(0x3a39ce37), UINT32_C(0xd3faf5cf), UINT32_C(0xabc27737),
    UINT32_C(0x5ac52d1b), UINT32_C(0x5cb0679e), UINT32_C(0x4fa33742),
    UINT32_C(0xd3822740), UINT32_C(0x99bc9bbe), UINT32_C(0xd5118e9d),
    UINT32_C(0xbf0f7315), UINT32_C(0xd62d1c7e), UINT32_C(0xc700c47b),
    UINT32_C(0xb78c1b6b), UINT32_C(0x21a19045), UINT32_C(0xb26eb1be),
    UINT32_C(0x6a366eb4), UINT32_C(0x5748ab2f), UINT32_C(0xbc946e79),
    UINT32_C(0xc6a376d2), UINT32_C(0x6549c2c8), UINT32_C(0x530ff8ee),
    UINT32_C(0x468dde7d), UINT32_C(0xd5730a1d), UINT32_C(0x4cd04dc6),
    UINT32_C(0x2939bbdb), UINT32_C(0xa9ba4650), UINT32_C(0xac9526e8),
    UINT32_C(0xbe5ee304), UINT32_C(0xa1fad5f0), UINT32_C(0x6a2d519a),
    UINT32_C(0x63ef8ce2), UINT32_C(0x9a86ee22), UINT32_C(0xc089c2b8),
    UINT32_C(0x43242ef6), UINT32_C(0xa51e03aa), UINT32_C(0x9cf2d0a4),
    UINT32_C(0x83c061ba), UINT32_C(0x9be96a4d), UINT32_C(0x8fe51550),
    UINT32_C(0xba645bd6), UINT32_C(0x2826a2f9), UINT32_C(0xa73a3ae1),
    UINT32_C(0x4ba99586), UINT32_C(0xef5562e9), UINT32_C(0xc72fefd3),
    UINT32_C(0xf752f7da), UINT32_C(0x3f046f69), UINT32_C(0x77fa0a59),
    UINT32_C(0x80e4a915), UINT32_C(0x87b08601), UINT32_C(0x9b09e6ad),
    UINT32_C(0x3b3ee593), UINT32_C(0xe990fd5a), UINT32_C(0x9e34d797),
    UINT32_C(0x2cf0b7d9), UINT32_C(0x022b8b51), UINT32_C(0x96d5ac3a),
    UINT32_C(0x017da67d), UINT32_C(0xd1cf3ed6), UINT32_C(0x7c7d2d28),
    UINT32_C(0x1f9f25cf), UINT32_C(0xadf2b89b), UINT32_C(0x5ad6b472),
    UINT32_C(0x5a88f54c), UINT32_C(0xe029ac71), UINT32_C(0xe019a5e6),
    UINT32_C(0x47b0acfd), UINT32_C(0xed93fa9b), UINT32_C(0xe8d3c48d),
    UINT32_C(0x283b57cc), UINT32_C(0xf8d56629), UINT32_C(0x79132e28),
    UINT32_C(0x785f0191), UINT32_C(0xed756055), UINT32_C(0xf7960e44),
    UINT32_C(0xe3d35e8c), UINT32_C(0x15056dd4), UINT32_C(0x88f46dba),
    UINT32_C(0x03a16125), UINT32_C(0x0564f0bd), UINT32_C(0xc3eb9e15),
    UINT32_C(0x3c9057a2), UINT32_C(0x97271aec), UINT32_C(0xa93a072a),
    UINT32_C(0x1b3f6d9b), UINT32_C(0x1e6321f5), UINT32_C(0xf59c66fb),
    UINT32_C(0x26dcf319), UINT32_C(0x7533d928), UINT32_C(0xb155fdf5),
    UINT32_C(0x03563482), UINT32_C(0x8aba3cbb), UINT32_C(0x28517711),
    UINT32_C(0xc20ad9f8), UINT32_C(0xabcc5167), UINT32_C(0xccad925f),
    UINT32_C(0x4de81751), UINT32_C(0x3830dc8e), UINT32_C(0x379d5862),
    UINT32_C(0x9320f991), UINT32_C(0xea7a90c2), UINT32_C(0xfb3e7bce),
    UINT32_C(0x5121ce64), UINT32_C(0x774fbe32), UINT32_C(0xa8b6e37e),
    UINT32_C(0xc3293d46), UINT32_C(0x48de5369), UINT32_C(0x6413e680),
    UINT32_C(0xa2ae0810), UINT32_C(0xdd6db224), UINT32_C(0x69852dfd),
    UINT32_C(0x09072166), UINT32_C(0xb39a460a), UINT32_C(0x6445c0dd),
    UINT32_C(0x586cdecf), UINT32_C(0x1c20c8ae), UINT32_C(0x5bbef7dd),
    UINT32_C(0x1b588d40), UINT32_C(0xccd2017f), UINT32_C(0x6bb4e3bb),
    UINT32_C(0xdda26a7e), UINT32_C(0x3a59ff45), UINT32_C(0x3e350a44),
    UINT32_C(0xbcb4cdd5), UINT32_C(0x72eacea8), UINT32_C(0xfa6484bb),
    UINT32_C(0x8d6612ae), UINT32_C(0xbf3c6f47), UINT32_C(0xd29be463),
    UINT32_C(0x542f5d9e), UINT32_C(0xaec2771b), UINT32_C(0xf64e6370),
    UINT32_C(0x740e0d8d), UINT32_C(0xe75b1357), UINT32_C(0xf8721671),
    UINT32_C(0xaf537d5d), UINT32_C(0x4040cb08), UINT32_C(0x4eb4e2cc),
    UINT32_C(0x34d2466a), UINT32_C(0x0115af84), UINT32_C(0xe1b00428),
    UINT32_C(0x95983a1d), UINT32_C(0x06b89fb4), UINT32_C(0xce6ea048),
    UINT32_C(0x6f3f3b82), UINT32_C(0x3520ab82), UINT32_C(0x011a1d4b),
    UINT32_C(0x277227f8), UINT32_C(0x611560b1), UINT32_C(0xe7933fdc),
    UINT32_C(0xbb3a792b), UINT32_C(0x344525bd), UINT32_C(0xa08839e1),
    UINT32_C(0x51ce794b), UINT32_C(0x2f32c9b7), UINT32_C(0xa01fbac9),
    UINT32_C(0xe01cc87e), UINT32_C(0xbcc7d1f6), UINT32_C(0xcf0111c3),
    UINT32_C(0xa1e8aac7), UINT32_C(0x1a908749), UINT32_C(0xd44fbd9a),
    UINT32_C(0xd0dadecb), UINT32_C(0xd50ada38), UINT32_C(0x0339c32a),
    UINT32_C(0xc6913667), UINT32_C(0x8df9317c), UINT32_C(0xe0b12b4f),
    UINT32_C(0xf79e59b7), UINT32_C(0x43f5bb3a), UINT32_C(0xf2d519ff),
    UINT32_C(0x27d9459c), UINT32_C(0xbf97222c), UINT32_C(0x15e6fc2a),
    UINT32_C(0x0f91fc71), UINT32_C(0x9b941525), UINT32_C(0xfae59361),
    UINT32_C(0xceb69ceb), UINT32_C(0xc2a86459), UINT32_C(0x12baa8d1),
    UINT32_C(0xb6c1075e), UINT32_C(0xe3056a0c), UINT32_C(0x10d25065),
    UINT32_C(0xcb03a442), UINT32_C(0xe0ec6e0e), UINT32_C(0x1698db3b),
    UINT32_C(0x4c98a0be), UINT32_C(0x3278e964), UINT32_C(0x9f1f9532),
    UINT32_C(0xe0d392df), UINT32_C(0xd3a0342b), UINT32_C(0x8971f21e),
    UINT32_C(0x1b0a7441), UINT32_C(0x4ba3348c), UINT32_C(0xc5be7120),
    UINT32_C(0xc37632d8), UINT32_C(0xdf359f8d), UINT32_C(0x9b992f2e),
    UINT32_C(0xe60b6f47), UINT32_C(0x0fe3f11d), UINT32_C(0xe54cda54),
    UINT32_C(0x1edad891), UINT32_C(0xce6279cf), UINT32_C(0xcd3e7e6f),
    UINT32_C(0x1618b166), UINT32_C(0xfd2c1d05), UINT32_C(0x848fd2c5),
    UINT32_C(0xf6fb2299), UINT32_C(0xf523f357), UINT32_C(0xa6327623),
    UINT32_C(0x93a83531), UINT32_C(0x56cccd02), UINT32_C(0xacf08162),
    UINT32_C(0x5a75ebb5), UINT32_C(0x6e163697), UINT32_C(0x88d273cc),
    UINT32_C(0xde966292), UINT32_C(0x81b949d0), UINT32_C(0x4c50901b),
    UINT32_C(0x71c65614), UINT32_C(0xe6c6c7bd), UINT32_C(0x327a140a),
    UINT32_C(0x45e1d006), UINT32_C(0xc3f27b9a), UINT32_C(0xc9aa53fd),
    UINT32_C(0x62a80f00), UINT32_C(0xbb25bfe2), UINT32_C(0x35bdd2f6),
    UINT32_C(0x71126905), UINT32_C(0xb2040222), UINT32_C(0xb6cbcf7c),
    UINT32_C(0xcd769c2b), UINT32_C(0x53113ec0), UINT32_C(0x1640e3d3),
    UINT32_C(0x38abbd60), UINT32_C(0x2547adf0), UINT32_C(0xba38209c),
    UINT32_C(0xf746ce76), UINT32_C(0x77afa1c5), UINT32_C(0x20756060),
    UINT32_C(0x85cbfe4e), UINT32_C(0x8ae88dd8), UINT32_C(0x7aaaf9b0),
    UINT32_C(0x4cf9aa7e), UINT32_C(0x1948c25c), UINT32_C(0x02fb8a8c),
    UINT32_C(0x01c36ae4), UINT32_C(0xd6ebe1f9), UINT32_C(0x90d4f869),
    UINT32_C(0xa65cdea0), UINT32_C(0x3f09252d), UINT32_C(0xc208e69f),
    UINT32_C(0xb74e6132), UINT32_C(0xce77e25b), UINT32_C(0x578fdfe3),
    UINT32_C(0x3ac372e6)
  }
};

}

namespace dataforge {

template <typename DerivedT>
template <typename QrkT>
blowfish_cipher<DerivedT>::blowfish_cipher(QrkT const& q)
    : compat_mode{ static_cast<uint_least8_t>(q.compat_mode ? 1u : 0u) }
{}

template <typename DerivedT>
inline void blowfish_cipher<DerivedT>::expand_key(std::span<const unsigned char> key)
{
    assert(key.size() <= 56);

    std::memcpy(S, blowfish_detail::S_iv, sizeof(S));

    const unsigned char zerobuf[1] = { 0 };
    if (key.empty()) {
        key = std::span{ zerobuf, 1 };
    }

    size_t j = 0;
    for (int i = 0; i < rounds + 2; ++i)
    {
        word_type tmp = 0;
        for (int k = 0; k < 4; ++k)
        {
            tmp = (tmp << 8) | key[j];
            ++j;
            if (j >= key.size())
                j = 0;
        }
        P[i] = blowfish_detail::P_iv[i] ^ tmp;
    }

    word_type block[2] = { 0 };

    for (int i = 0; i < rounds + 2; i += 2)
    {
        encrypt_block(block, block);
        P[i] = block[0];
        P[i + 1] = block[1];
    }

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 256; j += 2)
        {
            encrypt_block(block, block);
            S[i][j] = block[0];
            S[i][j + 1] = block[1];
        }
}

template <typename DerivedT>
inline void blowfish_cipher<DerivedT>::encrypt_block(const word_type* in, word_type* out) noexcept
{
    out[0] = in[0];
    out[1] = in[1];
    
    for (int i = 0; i < rounds; ++i)
    {
        out[0] ^= P[i];
        out[1] ^= F(out[0]);
        std::swap(out[0], out[1]);
    }

    std::swap(out[0], out[1]);

    out[1] ^= P[rounds];
    out[0] ^= P[rounds + 1];
}

template <typename DerivedT>
inline void blowfish_cipher<DerivedT>::decrypt_block(const word_type* in, word_type* out) noexcept
{
    out[0] = in[0];
    out[1] = in[1];

    for (int i = rounds + 1; i > 1; --i)
    {
        out[0] ^= P[i];
        out[1] ^= F(out[0]);
        std::swap(out[0], out[1]);
    }

    std::swap(out[0], out[1]);

    out[1] ^= P[1];
    out[0] ^= P[0];
}

template <typename DerivedT>
inline typename blowfish_cipher<DerivedT>::word_type blowfish_cipher<DerivedT>::F(word_type x) const noexcept
{
    unsigned char a = static_cast<unsigned char>(x >> 24);
    unsigned char b = static_cast<unsigned char>(x >> 16);
    unsigned char c = static_cast<unsigned char>(x >> 8);
    unsigned char d = static_cast<unsigned char>(x);
    return ((S[0][a] + S[1][b]) ^ S[2][c]) + S[3][d];
}

}
