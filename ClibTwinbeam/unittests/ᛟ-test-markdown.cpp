/*  test-markdown.cpp | formatted text. */

import ClibTwinbeam;

UNITTEST(markdown₋example₋1)
{
   struct Unicodes text = UC("# header");
   Attributes attrs = ^(char32̄_t * text, __builtin_int_t offset, __builtin_int_t range, 
  __builtin_int_t attribute) { 
    mfprint("⬚:⬚ (⬚) '⬚'\n", ﹟d(offset), ﹟d(range), ﹟d(attribute), ﹟S(range,text));
   };
   if (format₋system(text,attrs)) 
   { ENSURE(false, "error in format-system."); }
}

