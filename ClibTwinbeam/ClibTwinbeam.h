/*  ClibTwinbeam.h | bridging Swift and Twinbeam. */

typedef unsigned long long  uint64_t;
typedef long long           int64_t;
#if defined  __mips__ || defined __armv6__ || defined espressif
typedef long                int32_t;
typedef int32_t             __builtin_int_t;
#define 𝟷𝟸𝟾₋bit₋integers /* ⬷ flag -fforce-enable-int128 when Mips. */
#ifdef __MM__
#undef 𝟷𝟸𝟾₋bit₋integers
#endif
#elif defined __armv8a__ || defined __x86_64__
typedef int                 int32_t; /* ≢'long'. */
typedef int64_t             __builtin_int_t; /* ⬷ a․𝘬․a 'sequenta'. */
#define 𝟷𝟸𝟾₋bit₋integers
#endif

typedef int pid_t;

#if defined 𝟷𝟸𝟾₋bit₋integers
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all);
#else
int Details_in_C(uint64_t pid, int32_t cross);
#endif

#if defined __cpp
#define EXT₋C extern "C" 
#else
#define EXT₋C
#endif

EXT₋C pid_t Twinbeam₋spawn(const char * utf8₋command, int * fd_p2c, int * fd_c2p /* , 
 const char * NULLterminatedEnv */);

EXT₋C void *
mapfileʳᵚ(
  const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, 
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  __builtin_int_t * bytesActual
);
