/*  test-accuve.c | equal-size tiles and after-9 wrappable. */

import ClibTwinbeam;

UNITTEST(structa₋append)
{
   struct structa /* tape₋ */ number;
   unsigned bytes₋per₋item=2, bytes₋per₋tile=4096;
   if (init₋structa(bytes₋per₋item,bytes₋per₋tile,&tape))
   { ENSURE(false,"error in init₋structa."); }
   uint16_t material[] = { 1, 2, 3, 4, 5, 6, 7 };
   if (tape.copy₋append₋items(7,material)) { ENSURE(false,"error in copy₋append."); }
   for (int i=0; i<7; ++i) {
     uint16_t elem = *(uint16_t *)structa₋at(i,&tape);
   }
   deinit₋structa(&tape);
}

UNITTEST(regular₋append)
{
   struct structa /* tape₋ */ regulars; int uninit₋error=0;
   if (init₋regularpool(&regulars)) { ENSURE(false,"error in init₋symbolpool."); }
   Unicodes capture = UNICODES("beekeeper"); Nonabsolute reference;
   if (copy₋append₋to₋regular(&regulars,capture.tetras,capture.unicodes))
   { ENSURE(false,"error append₋to₋regular."); }
   int32_t tetras=capture.tetras;
   if (regularpool₋datum₋text(&regulars,tetras,&reference)) 
   { ENSURE(false,"error in datum₋text."); }
   if (optional₋uninit₋regularpool(&symbols)) { Pult💡(uninit₋error); }
}


