/*  test-keying.cpp | texts and editor. */

import ClibTwinbeam;

UNITTEST(Rope₋keyput₋1)
{
   void *opaque1=ΨΛΩ, *opaque2=ΨΛΩ;
   struct two₋memory dynmem = { Heap₋unalloc, Heap₋unalloc, Heap₋alloc, Heap₋alloc,
    Heap₋object₋size };
   struct Unicodes text1 = { 11, UC("hello world") }, text2 = { 8, UC(" thesis ") };
   unicode₋shatter shat1=branch₋to₋shatter(text1), shat2=branch₋to₋shatter(text2);
   if (rope₋append₋text(&opaque1,shat1,dynmem)) { ENSURE(false, "append-1 failed"); }
   if (rope₋append₋text(&opaque2,shat2,dynmem)) { ENSURE(false, "append-2 failed"); }
   if (rope₋insert(&opaque1,5,&opaque2,dynmem)) { ENSURE(false, "insert failed"); }
   __builtin_int_t count = rope₋length(opaque1);
   char c = rope₋index(opaque1,7);
   if (rope₋delete(&opaque1,11,2,dynmem)) { ENSURE(false, "delete failed"); }
   unalloc₋rope(opaque1,dynmem);
   unalloc₋rope(opaque2,dynmem);
}


