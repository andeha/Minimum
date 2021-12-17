/* ᛟ-test-keying.cpp | texteditors and the terminal editing line. */

import ClibTwinbeam;

UNITTEST(Rope)
{
   void ﹡opaque₁=ΨΛΩ, ﹡opaque₂=ΨΛΩ;
   if (rope₋append₋text(opaque₁, U"hello world")) { ENSURE(false, "return 1"); }
   if (rope₋append₋text(opaque₂, U" this ")) { ENSURE(false, "return 2"); }
   if (rope₋insert(opaque₁,5,opaque₂)) { ENSURE(false, "return 3"); }
   if (rope₋delete(opaque₁,11,2)) { ENSURE(false, "return 4"); }
   __builtin_int_t count = rope₋length(opaque₁);
   char c = rope₋index(opaque₁,7);
   rope₋free(opaque₁);
   rope₋free(opaque₂);
}


