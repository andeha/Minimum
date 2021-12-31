/*  enforce-beskow.c | cryptic and postable material. */

import ClibTwinbeam; /* and because of .c not 'import After_9'. */
import CString;

/*
   
   clang -o x86_stegagraph -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"  \
     -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap   \
     -g -std=c2x -lc++ enforce-beskow.c ../Releases/libClibTwinbeam.a
   
   ./x86_stegagraph ./testimony.txt
   
 */

/*
 *  main entry.
 */

/* auto Alloc = ^(__builtin_int_t bytes) { return Heap₋alloc(bytes); };
auto Fall⒪⒲ = ^(void * p) { Heap₋unalloc(p); };
auto Realloc = ^(void * p, __builtin_int_t to₋bytes) { return Heap₋realloc(p,to₋bytes); }; */

Structa code₋key₋pool, text₋word₋pool; /* two regularpools. */
Structa message₋words; /* vector<Nonabsolute> */
Structa code₋key₋words; /* vector<Nonabsolute> */

int
main(
  int argc, 
  const char * argv[]
)
{ char8₋t * binary=(char8₋t *)argv[0]; int reverse=0; 
   if (argc != 3) { print("usage: ⬚ [encrypt|decrypt] 'text file' \n", ﹟s8(binary)); return 1; }
   if (strcmp(argv[1],"decrypt") == 0) { reverse=1; }
   char8₋t * canonicalUtf8RegularOrLinkpath = (char8₋t *)argv[1];
   __builtin_int_t utf8₋bytes; uint8_t * utf8₋textmaterial;
   if (Twinbeam₋mmap(canonicalUtf8RegularOrLinkpath,0,0,0,&utf8₋bytes,&utf8₋textmaterial)) { return 2; }
   if (utf8₋textmaterial == ΨΛΩ) { return 3; }
   if (init₋regularpool(&code₋key₋pool) && init₋regularpool(&text₋word₋pool)) { return 4; }
   if (structa₋init(sizeof(Nonabsolute),4096,&message₋words)) { return 5; }
   if (structa₋init(sizeof(Nonabsolute),4096,&code₋key₋words)) { return 6; }
   __builtin_int_t beskow₋bytes = Beskow₋bytes();
   if (read₋utf8₋exposition(beskow₋bytes,wording₋beskow,&code₋key₋pool,&code₋key₋words)) { return 7; }
   if (read₋utf8₋exposition(utf8₋bytes,utf8₋material,&text₋word₋pool,&message₋words) { return 8; }
   __builtin_int_t message₋word₋count = structa₋bytes(&message₋words)/sizeof(Nonabsolute);
again:
   if (i >= message₋word₋count) { goto unagain; }
   if (reverse) {
     if (steganography₋reveal(Nonabsolute code, Nonabsolute * word)) { return 11; }
   }
   else {
     if (steganography₋hide(Nonabsolute word, Nonabsolute * code)) { return 12; }
   }
   goto again;
unagain:
   if (optional₋uninit₋regularpool(&text₋word₋pool)) { return 9; }
   if (deinit₋structa(&message₋words)) { return 10; }
   if (optional₋uninit₋regularpool(&code₋key₋pool)) { return 11; }
   if (deinit₋structa(&code₋key₋words)) { return 12; }
   return 0;
}


