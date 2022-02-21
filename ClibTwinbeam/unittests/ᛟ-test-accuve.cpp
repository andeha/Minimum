/*  test-accuve.c | equal-size tiles and to 100% tile-wrappable. */

import ClibTwinbeam;

UNITTEST(structa₋append)
{
   Structa tape₋count;
   unsigned bytes₋per₋item=2, bytes₋per₋tile=2000*sizeof(unsigned);
   if (structa₋init(bytes₋per₋item,bytes₋per₋tile,&tape₋count,Alloc)) 
   { ENSURE(false,"error in init₋structa."); }
   uint16_t material[] = { 1, 2, 3, 4, 5, 6, 7 };
   if (copy₋append₋items(7,material,&tape₋count,Alloc)) { ENSURE(false,"error in copy₋append."); }
   for (int i=0; i<7; i+=1) {
     unsigned elem = *(unsigned *)structa₋at(i,&tape₋count);
     print("⬚\n", ﹟d((__builtin_int_t)elem));
   }
   deinit₋structa(&tape₋count,Fallow);
}

UNITTEST(regular₋append)
{
   Structa tape₋color; int uninit₋error=0;
   if (init₋regularpool(&tape₋color,Alloc)) { ENSURE(false,"error in init₋symbolpool."); }
   Unicodes capture = UC("beekeeper"); Nonabsolute reference;
   if (copy₋append₋onto₋regular(&tape₋color,capture.tetras,capture.unicodes,Alloc))
   { ENSURE(false,"error append₋to₋regular."); }
   int32_t tetra₋count=capture.tetras;
   if (regularpool₋datum₋text(&tape₋color,tetra₋count,&reference)) 
   { ENSURE(false,"error in datum₋text."); }
   if (optional₋uninit₋regularpool(&tape₋color,Fallow)) { Pult💡(uninit₋error); }
}

struct µ₋note { int occurrencies; };

UNITTEST(jot₋token)
{ void * tree=ΨΛΩ; struct Unicodes token = UC("Twix");
   INIT init₋with₋note = ^(void * uninited) { return 1; };
   struct µ₋note * onenote = (µ₋note *)jot(token,&tree,sizeof(µ₋note),Alloc,init₋with₋note);
   onenote->occurrencies = 0;
}

UNITTEST(impression₋token)
{
   void * identities=ΨΛΩ;
   struct Unicodes token = UC("batman");
   __uint128_t fineprint = FNV1b(token.tetras*4,token.unicodes);
   void * handle₁ = impression₋store(&identities,fineprint,Alloc);
   void * handle₂ = impression₋seek(identities,fineprint);
   ENSURE(handle₁ == handle₂,"unable to find fineprint.");
}

