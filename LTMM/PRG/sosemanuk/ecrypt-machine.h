/* ecrypt-machine.h */

/* ------------------------------------------------------------------------- */

#if (defined(ECRYPT_DEFAULT_ROT) && !defined(ECRYPT_MACHINE_ROT))

#define ECRYPT_MACHINE_ROT

#if (defined(WIN32) && defined(_MSC_VER))

#undef ROTL32
#undef ROTR32
#undef ROTL64
#undef ROTR64

#include <stdlib.h>

#pragma intrinsic(_lrotl)     /* compile rotations "inline" */
#pragma intrinsic(_lrotr)

#define ROTL32(v, n) _lrotl(v, n)
#define ROTR32(v, n) _lrotr(v, n)
#define ROTL64(v, n) _rotl64(v, n)
#define ROTR64(v, n) _rotr64(v, n)

#endif

#endif

/* ------------------------------------------------------------------------- */

#if (defined(ECRYPT_DEFAULT_SWAP) && !defined(ECRYPT_MACHINE_SWAP))

#define ECRYPT_MACHINE_SWAP

#endif

/* ------------------------------------------------------------------------- */
