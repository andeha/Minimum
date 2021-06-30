/*  ClibTwinbeam.h | bridging Swift and Twinbeam. */

typedef unsigned long long  uint64_t;
typedef int                 int32_t; /* ≢'long'. */
/* #define 𝟷𝟸𝟾₋bit₋integers /‌* ⬷ flag -fforce-enable-int128 when Mips. */

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


