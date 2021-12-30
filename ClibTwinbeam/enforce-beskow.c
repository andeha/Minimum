/*  enforce-beskow.c | cryptic and postable material. */

import ClibTwinbeam;
/* import After_9; */

/*
   
   clang -o x86_stegagraph -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"  \
     -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap   \
     -g -std=c2x -lc++ enforce-beskow.c ../Releases/libClibTwinbeam.a
   
   ./x86_stegagraph ./express/comment
   
 */

/*
 *  main entry.
 */

/* auto Alloc = ^(__builtin_int_t bytes) { return Heap₋alloc(bytes); };
auto Fall⒪⒲ = ^(void * p) { Heap₋unalloc(p); };
auto Realloc = ^(void * p, __builtin_int_t to₋bytes) { return Heap₋realloc(p,to₋bytes); }; */

Structa pool;
Structa words; /* vector<Nonabsolute> */

int
main(
  int argc, 
  const char * argv[]
)
{ char8₋t * binary=(char8₋t *)argv[0];
   if (argc != 2) { print("usage: ⬚ file \n", ﹟s8(binary)); return 1; }
   char8₋t * canonicalUtf8RegularOrLinkpath = (char8₋t *)argv[1];
   if (init₋regularpool(&pool)) { return 2; }
   __builtin_int_t bytesActual; uint8_t * material;
   if (Twinbeam₋mmap(canonicalUtf8RegularOrLinkpath,0,0,0,&bytesActual,&material)) { return 3; }
   int32_t tetras=0; char32̄_t cs[1024];
   if (copy₋append₋onto₋regular(&pool,tetras,cs)) { return 4; }
   Nonabsolute ref; if (regularpool₋datum₋text(&pool,tetras,&ref)) { return 5; }
   if (optional₋uninit₋regularpool(&pool)) { return 5; }
   return 0;
}


