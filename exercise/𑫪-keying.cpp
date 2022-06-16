/*  test-keying.cpp | texts and editor. */

import ClibTwinbeam;

inexorable void print₋rope(void ᶿ﹡ opaque)
{
   Rope₋text out = ^(unicode₋shatter text, __builtin_int_t count) {
    Argᴾ param = ﹟S(count,(const char32̄_t *)text);
    print("text segment is '⬚'\n",param); };
   __builtin_int_t count = depth₋first₋with₋interval(opaque,0,5,out,true);
   print("printed ⬚ characters\n", ﹟d(count));
}

UNITTEST(Rope₋keyput₋1)
{
   void *opaque1=ΨΛΩ, *opaque2=ΨΛΩ;
   struct two₋memory dynmem = { Heap₋unalloc, Heap₋unalloc, Heap₋alloc, Heap₋alloc, 
    Heap₋object₋size };
   struct Unicodes text1 = UC("hello "), text2 = { 8, UNICODES(" thesis ") };
   unicode₋shatter shat1=persist₋as₋shatter(text1), shat2=persist₋as₋shatter(text2);
   print("location1: "); print₋rope(opaque1);
   if (rope₋append₋text(&opaque1,shat1,dynmem)) { ENSURE(false, "append-1 failed"); }
   print("location2: "); print₋rope(opaque1);
   if (rope₋append₋text(&opaque2,shat2,dynmem)) { ENSURE(false, "append-2 failed"); }
   print("location3: "); print₋rope(opaque2);
   if (rope₋insert(&opaque1,5,&opaque2,dynmem)) { ENSURE(false, "insert failed"); }
   print("location4: "); print₋rope(opaque1);
   __builtin_int_t count = rope₋symbols(opaque1);
   ENSURE(count == 14, "rope-symbols incorrect");
  /* char32̄_t uc = rope₋index(opaque1,7);
   if (rope₋delete(&opaque1,11,2,dynmem)) { ENSURE(false, "delete failed"); }
   unalloc₋rope(opaque1,dynmem);
   unalloc₋rope(opaque2,dynmem); */
}


