/*  􀫖 transmit-recoll.c | field and note-taking. */

import ClibTwinbeam;

struct radio₋editor { void * start₋rope; 
  __builtin_int_t cursor₋unicodes₋offset, cursor₋unicodes₋length;
  void * (^alloc)(int bytes);
}; /* ⬷ a․𝘬․a remmingway. */
#define INVISIBLE₋CHARACTER 0xfffc /* object replacement character. */
typedef struct radio₋editor Editor;
EXT₋C int radio₋editor₋init(Editor * 🅁, void * (^alloc)(int bytes));
EXT₋C int radio₋editor₋select(Editor * 🅁, __builtin_int_t unicodes₋offset₋start, 
 __builtin_int_t unicodes₋count);
EXT₋C int radio₋editor₋keyput(Editor * 🅁, struct Unicodes symbols);
EXT₋C int radio₋editor₋delete(Editor * 🅁, __builtin_int_t symbol₋count);
EXT₋C int radio₋editor₋replace(Editor * 🅁, struct Unicodes symbols);

int radio₋editor₋init(Editor * 🅁, void * (^alloc)(int bytes))
{ 🅁->cursor₋unicodes₋offset=0; 🅁->cursor₋unicodes₋length=0;
   🅁->start₋rope = ΨΛΩ;
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

int radio₋editor₋keyput(Editor * 🅁, struct Unicodes symbols)
{
   if (symbols.tetras > 🅁->cursor₋unicodes₋length) { }
   🅁->cursor₋unicodes₋offset += 1;
   🅁->cursor₋unicodes₋length=0;
   return 0;
}

int radio₋editor₋delete(Editor * 🅁, __builtin_int_t symbol₋count)
{
   🅁->cursor₋unicodes₋offset += 1;
   🅁->cursor₋unicodes₋length=0;
   return 0;
}

int radio₋editor₋replace(Editor * 🅁, struct Unicodes symbols)
{
   if (symbols.tetras > 🅁->cursor₋unicodes₋length) {
     
   }
 //  🅁->cursor₋unicodes₋offset=unicodes₋offset₋start;
   🅁->cursor₋unicodes₋length=0;
   return 0;
}



