/*  regular-pool.c | may possibly may-not open with a number. */

import ClibTwinbeam;

int init₋regularpool(struct structa * 🅿, ALLOC alloc)
{ unsigned bytes₋per₋tile=4096;
   if (structa₋init(4,bytes₋per₋tile,🅿,alloc)) { return -1; }
   return 0;
}

int optional₋uninit₋regularpool(struct structa * 🅿, FALLOW fallow)
{
   if (deinit₋structa(🅿,fallow)) { return -1; }
   return 0;
}

int copy₋append₋onto₋regular(struct structa * 🅟, int32_t tetras, char32̄_t cs[], ALLOC alloc)
{ int32_t bytes=4*tetras;
   if (copy₋append₋items(bytes,cs,🅟,alloc)) { return -1; }
   return 0;
}

int regularpool₋datum₋text(struct structa * 🅟, int32_t tetras, Nonabsolute * reference)
{
   if (reference == ΨΛΩ) { return -1; }
   __builtin_int_t total₋bytes = 4*structa₋count(🅟), 
    byte₋idx=total₋bytes - 4*tetras;
   union Tetra𝘖rUnicode * datum = (union Tetra𝘖rUnicode *)structa₋at(byte₋idx,🅟);
   *reference = byte₋idx/4;
   return 0;
}

struct Unicodes regularpool₋at(struct structa * 🅟, Nonabsolute relative)
{
   __builtin_int_t byte₋idx = relative*4;
   union Tetra𝘖rUnicode * datum = (union Tetra𝘖rUnicode *)structa₋at(byte₋idx,🅟);
   union Tetra𝘖rUnicode * start = 1 + datum;
   struct Unicodes text = { datum->count, &(start->uc) };
   return text;
}

