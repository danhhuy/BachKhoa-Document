/* ecrypt-sync.h */

#ifndef ECRYPT_SYNC
#define ECRYPT_SYNC

#include "ecrypt-portable.h"
#include <stdlib.h>

#define ECRYPT_NAME "SOSEMANUK"    /* [edit] */ 



#define ECRYPT_MAXKEYSIZE 256                 /* [edit] */
#define ECRYPT_KEYSIZE(i) (8 + (i)*8)         /* [edit] */

#define ECRYPT_MAXIVSIZE 128                  /* [edit] */
#define ECRYPT_IVSIZE(i) (8 + (i)*8)          /* [edit] */


typedef struct
{

	u32 sk[100];

	size_t ivlen;

	u32 s00, s01, s02, s03, s04, s05, s06, s07, s08, s09;
	u32 r1, r2;

} ECRYPT_ctx;


void ECRYPT_init(void);


void ECRYPT_keysetup(
  ECRYPT_ctx* ctx, 
  const u8* key, 
  u32 keysize,                /* Key size in bits. */ 
  u32 ivsize);                /* IV size in bits. */ 

void ECRYPT_ivsetup(
  ECRYPT_ctx* ctx, 
  const u8* iv);

#define ECRYPT_HAS_SINGLE_BYTE_FUNCTION       /* [edit] */
#ifdef ECRYPT_HAS_SINGLE_BYTE_FUNCTION

#define ECRYPT_encrypt_bytes(ctx, plaintext, ciphertext, msglen)   \
  ECRYPT_process_bytes(0, ctx, plaintext, ciphertext, msglen)

#define ECRYPT_decrypt_bytes(ctx, ciphertext, plaintext, msglen)   \
  ECRYPT_process_bytes(1, ctx, ciphertext, plaintext, msglen)

void ECRYPT_process_bytes(
  int action,                 /* 0 = encrypt; 1 = decrypt; */
  ECRYPT_ctx* ctx, 
  const u8* input, 
  u8* output, 
  u32 msglen);                /* Message length in bytes. */ 

#else

void ECRYPT_encrypt_bytes(
  ECRYPT_ctx* ctx, 
  const u8* plaintext, 
  u8* ciphertext, 
  u32 msglen);                /* Message length in bytes. */ 

void ECRYPT_decrypt_bytes(
  ECRYPT_ctx* ctx, 
  const u8* ciphertext, 
  u8* plaintext, 
  u32 msglen);                /* Message length in bytes. */ 

#endif

/* ------------------------------------------------------------------------- */


#define ECRYPT_GENERATES_KEYSTREAM
#ifdef ECRYPT_GENERATES_KEYSTREAM

void ECRYPT_keystream_bytes(
  ECRYPT_ctx* ctx,
  u8* keystream,
  u32 length);                /* Length of keystream in bytes. */

#endif

/* ------------------------------------------------------------------------- */

#define ECRYPT_USES_DEFAULT_ALL_IN_ONE        /* [edit] */


#define ECRYPT_HAS_SINGLE_PACKET_FUNCTION     /* [edit] */
#ifdef ECRYPT_HAS_SINGLE_PACKET_FUNCTION

#define ECRYPT_encrypt_packet(                                        \
    ctx, iv, plaintext, ciphertext, mglen)                            \
  ECRYPT_process_packet(0,                                            \
    ctx, iv, plaintext, ciphertext, mglen)

#define ECRYPT_decrypt_packet(                                        \
    ctx, iv, ciphertext, plaintext, mglen)                            \
  ECRYPT_process_packet(1,                                            \
    ctx, iv, ciphertext, plaintext, mglen)

void ECRYPT_process_packet(
  int action,                 /* 0 = encrypt; 1 = decrypt; */
  ECRYPT_ctx* ctx, 
  const u8* iv,
  const u8* input, 
  u8* output, 
  u32 msglen);

#else

void ECRYPT_encrypt_packet(
  ECRYPT_ctx* ctx, 
  const u8* iv,
  const u8* plaintext, 
  u8* ciphertext, 
  u32 msglen);

void ECRYPT_decrypt_packet(
  ECRYPT_ctx* ctx, 
  const u8* iv,
  const u8* ciphertext, 
  u8* plaintext, 
  u32 msglen);

#endif



#define ECRYPT_BLOCKLENGTH 80                /* [edit] */

#undef ECRYPT_USES_DEFAULT_BLOCK_MACROS      /* [edit] */
#ifdef ECRYPT_USES_DEFAULT_BLOCK_MACROS

#define ECRYPT_encrypt_blocks(ctx, plaintext, ciphertext, blocks)  \
  ECRYPT_encrypt_bytes(ctx, plaintext, ciphertext,                 \
    (blocks) * ECRYPT_BLOCKLENGTH)

#define ECRYPT_decrypt_blocks(ctx, ciphertext, plaintext, blocks)  \
  ECRYPT_decrypt_bytes(ctx, ciphertext, plaintext,                 \
    (blocks) * ECRYPT_BLOCKLENGTH)

#ifdef ECRYPT_GENERATES_KEYSTREAM

#define ECRYPT_keystream_blocks(ctx, keystream, blocks)            \
  ECRYPT_keystream_bytes(ctx, keystream,                           \
    (blocks) * ECRYPT_BLOCKLENGTH)

#endif

#else

#define ECRYPT_HAS_SINGLE_BLOCK_FUNCTION      /* [edit] */
#ifdef ECRYPT_HAS_SINGLE_BLOCK_FUNCTION

#define ECRYPT_encrypt_blocks(ctx, plaintext, ciphertext, blocks)     \
  ECRYPT_process_blocks(0, ctx, plaintext, ciphertext, blocks)

#define ECRYPT_decrypt_blocks(ctx, ciphertext, plaintext, blocks)     \
  ECRYPT_process_blocks(1, ctx, ciphertext, plaintext, blocks)

void ECRYPT_process_blocks(
  int action,                 /* 0 = encrypt; 1 = decrypt; */
  ECRYPT_ctx* ctx, 
  const u8* input, 
  u8* output, 
  u32 blocks);                /* Message length in blocks. */

#else

void ECRYPT_encrypt_blocks(
  ECRYPT_ctx* ctx, 
  const u8* plaintext, 
  u8* ciphertext, 
  u32 blocks);                /* Message length in blocks. */ 

void ECRYPT_decrypt_blocks(
  ECRYPT_ctx* ctx, 
  const u8* ciphertext, 
  u8* plaintext, 
  u32 blocks);                /* Message length in blocks. */ 

#endif

#ifdef ECRYPT_GENERATES_KEYSTREAM

void ECRYPT_keystream_blocks(
  ECRYPT_ctx* ctx,
  u8* keystream,
  u32 blocks);                /* Keystream length in blocks. */ 

#endif

#endif

#define ECRYPT_MAXVARIANT 1                   /* [edit] */

#ifndef ECRYPT_VARIANT
#define ECRYPT_VARIANT 1
#endif

#if (ECRYPT_VARIANT > ECRYPT_MAXVARIANT)
#error this variant does not exist
#endif

/* ------------------------------------------------------------------------- */

#endif
