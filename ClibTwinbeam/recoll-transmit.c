/*  􀫖 transmit-recoll.c | note-taking on field. */

import ClibTwinbeam;

inexorable void radio₋editor₋tile₋init(struct radio₋editor₋tile * 🆃)
{
   🆃->next=ΨΛΩ; 🆃->tetras=0; 🆃->prev=ΨΛΩ;
   for (int i=0; i<1019; ++i) { 🆃->chars[i]=INVISIBLE₋CHARACTER; }
}

inexorable int split₋tile(__builtin_int_t unicodes₋offset) { }

int radio₋editor₋init(Editor * 🅁, void * (^alloc)(int bytes))
{ 🅁->cursor₋unicodes₋offset=0; 🅁->cursor₋unicodes₋length=0;
   🅁->start=(struct radio₋editor₋tile *)alloc(sizeof(struct radio₋editor₋tile));
   if (🅁->start == ΨΛΩ) { return -1; }
   radio₋editor₋tile₋init(🅁->start);
   🅁->alloc=alloc;
   return 0;
}

int radio₋editor₋select(Editor * 🅁, __builtin_int_t unicodes₋offset₋start, 
 __builtin_int_t unicodes₋count)
{
   🅁->cursor₋unicodes₋offset=unicodes₋offset₋start;
   🅁->cursor₋unicodes₋length=unicodes₋count;
   return 0;
}

int radio₋editor₋wedge(Editor * 🅁, struct Unicodes symbols)
{
   if (symbols.tetras > 🅁->cursor₋unicodes₋length) { }
   🅁->cursor₋unicodes₋offset=unicodes₋offset₋start;
   🅁->cursor₋unicodes₋length=0;
   return 0;
}

int radio₋editor₋delete(Editor * 🅁, __builtin_int_t symbol₋count)
{
   🅁->cursor₋unicodes₋offset=unicodes₋offset₋start;
   🅁->cursor₋unicodes₋length=0;
   return 0;
}

int radio₋editor₋replace(Editor * 🅁, struct Unicodes symbols)
{
   if (symbols.tetras > 🅁->cursor₋unicodes₋length) {
     
   }
   🅁->cursor₋unicodes₋offset=unicodes₋offset₋start;
   🅁->cursor₋unicodes₋length=0;
   return 0;
}



