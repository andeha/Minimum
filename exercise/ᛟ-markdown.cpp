/*  test-markdown.cpp | formatted text using a querty keyboard. */

import ClibTwinbeam;

UNITTEST(keyput₋example₋1)
{
   struct Unicodes text = UC("Introduction *H1* Welcome to a bold introduction. Ɵ There is an error, quickly consume error.--:");
   struct Unicodes rightalign=UC("--:"), initial=UC("Ɵ"), header1 = UC("*H1*");
   __uint128_t ralign₋code=FNV1b(rightalign.tetras*4,rightalign.unicodes);
   __uint128_t initial₋code=FNV1b(initial.tetras*4,initial.unicodes);
   __uint128_t header1₋code=FNV1b(header1.tetras*4,header1.unicodes);
   void * rules;
   rules = impression₋store(rules,ralign₋code,Heap₋alloc);
   rules = impression₋store(rules,initial₋code,Heap₋alloc);
   rules = impression₋store(rules,header1₋code,Heap₋alloc);
   if (keyput(rules,text)) { ENSURE(false, "error in keyput."); }
}

UNITTEST(keyput₋example₋2)
{
   struct Unicodes run = UC("a completed run");
   Attributes attrs = 
    ^(char32̄_t * text, __builtin_int_t offset, __builtin_int_t range, 
       __builtin_int_t attribute)
    {
      mfprint("⬚:⬚ (⬚) '⬚'\n", ﹟d(offset), ﹟d(range), ﹟d(attribute), ﹟S(range,text));
    };
   if (format₋system(run,attrs)) { ENSURE(false, "error in format-system"); }
}

struct Action { void (*action)(void); };

UNITTEST(keyput₋example₋3)
{
  INIT action₋init = ^(void * uninited) { };
  notepointer note = jot(header1₋code,&rules,sizeof(Action),action₋init);
}
