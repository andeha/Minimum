/*  ᛟ-test-half.cpp | ieee754-2008 16-bit floating points. */

import ClibTwinbeam;
import Stdio;

extern "C" long write(int fd, const void * s, long unsigned nbyte);

UNITTEST(half₋Presentᵧ)
{
   pythagorean_double x { .binary16 = { 3, 2, 1 } };
   double y = To₋doubleprecision(x.bits);
   printf("double is %f\n\n", y); /* print("⬚", ﹟F(beamed₋eigth₋uc)); */
   /* auto sometime = ^(int count, char32_t * terminated₋ucs) {
     print("⬚", ﹟S₁(beamed₋eigth₋uc)); }; */
   const int stdout=1;
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(stdout, (const void *)u8s, bytes); };
   NumberformatCatalogue₋Presentᵧ(x.bits,out);
}


