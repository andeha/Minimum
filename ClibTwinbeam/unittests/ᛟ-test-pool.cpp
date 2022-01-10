/*  test-pool.cpp | Unicode symbols table. */

import ClibTwinbeam;

UNITTEST(symbolpool₋add₋and₋retrieve)
{
   struct symbolpool snippets₋and₋keywords;
   if (init₋symbolpool(&snippets₋and₋keywords, __builtin_int_t 
    tetras₋per₋tile, __builtin_int_t count, void * kbXtiles[], Leaf₋alloc 
    leaf₋alloc)) { return; }
   
   if (copy₋append₋text(struct symbolpool * 🅟, int count, char32̄_t cs[], 
    Nonabsolute * ref, void (^inflate)(__builtin_int_t ﹟, void **kbXtiles, 
    int * cancel))) { return; }
   
   if (datum₋text(struct symbolpool * 🅟, int32_t tetras)) { return; }
   
   union Tetra𝘖rUnicode * symbol = at(&snippets₋and₋keywords, Nonabsolute relative);
   
   if (textual₋similar(&snippets₋and₋keywords, struct Unicodes uc₁, 
    Nonabsolute relative)) { return; }
   
   if (optional₋uninit₋smallpool(&snippets₋and₋keywords, Text₋dealloc 
    dealloc₂, Node₋dealloc dealloc₁)) { return; }
}

UNITTEST(symbolpool₋impressions)
{
   
}

