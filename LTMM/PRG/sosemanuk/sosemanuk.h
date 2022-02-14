#ifndef SOSEMANUK_H__
#define SOSEMANUK_H__

#define SOSEMANUK_ECRYPT

#ifdef SOSEMANUK_ECRYPT

#include "ecrypt-sync.h"

#else

#include <limits.h>


#if CHAR_BIT != 8
#error We need 8-bit bytes
#endif


#if !defined BROKEN_C99 && defined __STDC__ && __STDC_VERSION__ >= 199901L


#include <stdint.h>
typedef uint_least32_t unum32;

#else


#if UINT_MAX >= 0xFFFFFFFF
typedef unsigned int unum32;
#else
typedef unsigned long unum32;
#endif

#endif


#define ONE32    ((unum32)0xFFFFFFFF)
#define T32(x)   ((x) & ONE32)


#if (!defined BROKEN_C99 && defined __STDC__ && __STDC_VERSION__ >= 199901L) \
	|| defined __GNUC__
#define INLINE inline
#else
#define INLINE
#endif


typedef struct {
	unum32 sk[100];
} sosemanuk_key_context;

typedef struct {
	unum32 s00, s01, s02, s03, s04, s05, s06, s07, s08, s09;
	unum32 r1, r2;
	unsigned char buf[80];
	unsigned ptr;
} sosemanuk_run_context;

void sosemanuk_schedule(sosemanuk_key_context *kc,
	unsigned char *key, size_t key_len);


void sosemanuk_init(sosemanuk_run_context *rc,
	sosemanuk_key_context *kc, unsigned char *iv, size_t iv_len);


void sosemanuk_prng(sosemanuk_run_context *rc,
	unsigned char *out, size_t out_len);


void sosemanuk_encrypt(sosemanuk_run_context *rc,
	unsigned char *in, unsigned char *out, size_t data_len);

#endif

#endif
