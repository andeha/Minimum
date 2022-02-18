/*  test-keying.cpp | texts and editor. */

import ClibTwinbeam;

UNITTEST(Rope₋keyput₋1)
{
   void *opaque1=ΨΛΩ, *opaque2=ΨΛΩ;
   struct two₋memory dynmem = { Heap₋unalloc, Heap₋unalloc, Heap₋alloc, Heap₋alloc,
    Heap₋object₋size };
   struct Unicodes text1 = UC("hello world"), text2 = { 8, UNICODES(" thesis ") };
   unicode₋shatter shat1=persist₋as₋shatter(text1), shat2=persist₋as₋shatter(text2);
   if (rope₋append₋text(&opaque1,shat1,dynmem)) { ENSURE(false, "append-1 failed"); }
   if (rope₋append₋text(&opaque2,shat2,dynmem)) { ENSURE(false, "append-2 failed"); }
   if (rope₋insert(&opaque1,5,&opaque2,dynmem)) { ENSURE(false, "insert failed"); }
   __builtin_int_t count = rope₋symbols(opaque1);
   char32̄_t uc = rope₋index(opaque1,7);
   if (rope₋delete(&opaque1,11,2,dynmem)) { ENSURE(false, "delete failed"); }
   unalloc₋rope(opaque1,dynmem);
   unalloc₋rope(opaque2,dynmem);
}


