/*  test-utf8.cpp | unicodes/alphabete — roman, arabic and non-cyrillic. */

import ClibTwinbeam;

UNITTEST(utf8ToUnicode₋1)
{
  char8₋t ξ[] = { 0xe2, 0x99, 0xab }; __builtin_int_t bytes=3;
  char32̄_t beamed₋eigth₋uc = Utf8ToUnicode(ξ,bytes);
  ENSURE(beamed₋eigth₋uc == 0x266b, "utf8 to unicode failed")
}

UNITTEST(unicodeToUtf8)
{ char32̄_t Ξ = U'😐';
  typedef void (^Encoding)(char8₋t * u8s, short bytes);
  Encoding sometime₋valid = ^(char8₋t * u8s, short bytes) {
    ENSURE(u8s[0] == 0xf0, "first byte error");
    ENSURE(u8s[1] == 0x9f, "second byte error");
    ENSURE(u8s[2] == 0x98, "third byte error");
    ENSURE(u8s[3] == 0x90, "fourth byte error");
    ENSURE(bytes == 4, "incorrect byte count");
  };
  if (UnicodeToUtf8(Ξ,sometime₋valid)) { ENSURE(false, "Error in UnicodeToUtf8"); }
}

static void print₋unicodes(int symbol₋count, char32̄_t * text₋heap)
{ uint32_t uc; int i=0;
   char32̄_t * text = text₋heap;
again:
   if (i >= symbol₋count) { return; }
   uc = *(i + text); i += 1;
   print("⬚ ", ﹟x((__builtin_uint_t)uc));
   goto again;
}

UNITTEST(decoded₋print)
{
#if defined __cplusplus
   const char32̄_t * text = (char32̄_t *)U"lorem ipsum";
   /* const char32̄_t * text = U"lorem ipsum"_unicodes; */
#else
   const char32̄_t * text = U"lorem ipsum";
#endif
   print₋unicodes(11,(char32̄_t *)text);
}

