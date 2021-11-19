/* 􀊫 search-symbol.c | 64 keyput prefix searching. */

import ClibTwinbeam;

EXT₋C
__builtin_int_t ExactUtf8bytes(char32_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t sum=0, i=0;
again:
   if (i >= maxtetras) { return sum; }
   char32_t uc = *(ucs + i);
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
   char8₋t * leadOr8Bit = u8s + i;
   if (*leadOr8Bit == 0x0) { return i; }
   __builtin_int_t followers = Utf8Followers(*leadOr8Bit);
   if (followers < 0) { return -1; }
   i += followers + 1;
   goto again;
}

EXT₋C
int
IsPrefixOrEqual(
  const char * 𝟽alt𝟾₋bitstring, /* ⬷ possibly 'normalizedUtf8' */
  const char * 𝟽alt𝟾₋bitprefix  /* ⬷ smiley appears when 'prompt> nm'! */
) /* ⬷ consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
{  const char *s=𝟽alt𝟾₋bitstring, *p=𝟽alt𝟾₋bitprefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters 'string' and 'prefix' are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in 'prefix' equal to 'string'. Return first character following 'eightbitPrefix'. */
    /* *p != 0 && *s != 0 */
    char diff = *s - *p;
    if (diff) { return 0; } /* Savannah and Samura. */
    s++, p++;
    goto again;
}


