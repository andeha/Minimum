/*  symbol-text.c | . */

import ClibTwinbeam;

EXT₋C __builtin_int_t TetrasUntilNull(char32̄_t * ucs, 
 __builtin_int_t maxtetras)
{ __builtin_int_t i=0;
again:
   if (i >= maxtetras) { return maxtetras; }
   char32̄_t * uc = ucs + i;
   if (*uc == 0x0000) { return i; }
   ++i; goto again;
}

EXT₋C
__builtin_int_t ExactUtf8bytes(char32̄_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t sum=0, i=0;
again:
   if (i >= maxtetras) { return sum; }
   char32̄_t uc = *(ucs + i);
   if (uc < 0x80L) { sum += 1; }
   else if (uc < 0x800L) { sum += 2; }
   else if (uc < 0x10000L) { sum += 3; }
   else if (uc <= 0x0010FFFFL) { sum += 4; }
   else { return -1; }
   ++i; goto again;
   return 0;
}

EXT₋C
__builtin_int_t
Utf8BytesUntilNull(
  char8₋t * u8s,
  __builtin_int_t maxbytes
)
{ __builtin_int_t i=0;
again:
   if (i >= maxbytes) { return maxbytes; }
   char8₋t leadOr8Bit = *(u8s + i);
   if (leadOr8Bit == 0x0) { return i; }
   __builtin_int_t followers = Utf8Followers(leadOr8Bit);
   if (followers < 0) { return -1; }
   i += followers + 1;
   goto again;
}

