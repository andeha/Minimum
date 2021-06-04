/*  ClibTwinbeam.h | bridging Swift and Twinbeam. */

typedef unsigned long long  uint64_t;
typedef int                 int32_t; /* ≢'long'. */
/* #define 𝟷𝟸𝟾₋bit₋integers /‌* ⬷ flag -fforce-enable-int128 when Mips. */

#if defined 𝟷𝟸𝟾₋bit₋integers
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all);
#else
int Details_in_C(uint64_t pid, int32_t cross);
#endif


