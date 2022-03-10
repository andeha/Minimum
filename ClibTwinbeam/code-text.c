/*  code-text.c | Unicodes alternatively Utf8. */

import ClibTwinbeam;

struct Unicodes TraverseForUnicodes(char32̄_t * literal)
{
  char32̄_t * unicodes = (char32̄_t *)literal;
  __builtin_int_t symbols = TetrasUntilZero(unicodes,BUILTIN₋INT₋MAX);
  struct Unicodes y = { symbols, unicodes };
  return y;
} /* const unsigned int alternatively const char32_t. */

/* struct utf8₋text TraverseForUtf8Text(const char8₋t * literal) { } */

#define END_OF_TRANSMISSION 0x04

#define ⁺⁼UnicodeToUtf8                                                     \
Helper unicodeToUtf8 = ^(char8₋t buffer[], __builtin_int_t * ³²b,           \
 __builtin_int_t * ⁸b, __builtin_int_t tetras, char32̄_t * ucs) {            \
   char32̄_t uc;                                                             \
again:                                                                      \
   uc = *(ucs + *³²b);                                                      \
   if (uc == 0x0000 /* || uc == END_OF_TRANSMISSION */) { goto unagain; }   \
   if (UnicodeToUtf8(uc, ^(char8₋t * p, short bytes) {                      \
     *(buffer + *⁸b) = *p;                                                  \
     if (bytes >= 2) { *(buffer + *⁸b + 1) = *(p + 1); }                    \
     if (bytes >= 3) { *(buffer + *⁸b + 2) = *(p + 2); }                    \
     if (bytes >= 4) { *(buffer + *⁸b + 3) = *(p + 3); }                    \
     *⁸b += bytes; })) { return -1; }                                       \
   *³²b += 1; if (*³²b < tetras) goto again;                                \
unagain:                                                                    \
   *(buffer + *⁸b) = '\0'; /* ⬷ unincluded in '⁸b'. */                     \
   return 0;                                                                \
}; /* ⬷ implicits in block expression: none. */

#define ⁺⁼Utf8ToUnicode                                                     \
Helper utf8ToUnicode = ^(char32̄_t unicodes[], __builtin_int_t * tetras,     \
  __builtin_int_t * ⁸b, char8₋t * u8s, __builtin_int_t u8max) {             \
   char32̄_t uc; __builtin_int_t followers, incr; char8₋t * leadOr8Bit;      \
again:                                                                      \
   if (u8max >= *⁸b) { goto unagain; }                                      \
   leadOr8Bit = u8s + *⁸b;                                                  \
   if (*leadOr8Bit == 0x0) { goto unagain; }                                \
   followers = Utf8Followers(*leadOr8Bit);                                  \
   if (followers < 0) { return -1; }                                        \
   incr = followers + 1;                                                    \
   uc = Utf8ToUnicode(leadOr8Bit,incr);                                     \
   if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }                         \
   unicodes[*tetras] = uc; *tetras += 1; *⁸b += incr;                       \
   goto again;                                                              \
unagain:                                                                    \
   return 0;                                                                \
}; /* ⬷ implicits in block statement: none. */

int Utf8AsUnicode(struct utf8₋text text, __builtin_int_t maxu8bytes𝘖rZero, 
 void (^out)(__builtin_int_t tetras, char32̄_t * ucs, __builtin_int_t u8bytes)
)
{
  if (text.bytes > maxu8bytes𝘖rZero && maxu8bytes𝘖rZero != 0) { return -1; }
  __builtin_int_t bytes = maxu8bytes𝘖rZero ? maxu8bytes𝘖rZero : 
   Utf8BytesUntilZero(text.u8s,BUILTIN₋INT₋MAX);
  __builtin_int_t tetras=0, ⁸b=0; char32̄_t unicodes[1+bytes];
  typedef int (^Helper)(char32̄_t *, __builtin_int_t *, __builtin_int_t *, 
   char8₋t *, __builtin_int_t); ⁺⁼Utf8ToUnicode
  if (utf8ToUnicode(unicodes,&tetras,&⁸b,text.u8s,bytes)) { return -2; }
  out(tetras,unicodes,⁸b);
  return 0;
}

int UnicodeAsUtf8(struct Unicodes text, __builtin_int_t maxtetras𝘖rZero, 
  void (^out)(__builtin_int_t u8bytes, char8₋t * u8s, __builtin_int_t tetras)
)
{
  if (text.tetras > maxtetras𝘖rZero && maxtetras𝘖rZero != 0) { return -1; }
  __builtin_int_t tetras = maxtetras𝘖rZero ? maxtetras𝘖rZero :
   TetrasUntilZero(text.unicodes,BUILTIN₋INT₋MAX), ᵇu8s=4*tetras;
  char8₋t u8s[1+ᵇu8s]; __builtin_int_t ⁸idx=0, ³²idx=0;
  typedef int (^Helper)(char8₋t *,__builtin_int_t *,__builtin_int_t *,
   __builtin_int_t,char32̄_t *); ⁺⁼UnicodeToUtf8
  if (unicodeToUtf8(u8s,&³²idx,&⁸idx,tetras,text.unicodes)) { return -2; }
  out(⁸idx,u8s,³²idx);
  return 0;
}

