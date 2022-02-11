/*  enforce-beskow.c | cryptic and postable alternatively non-storable material 
 with artistic padding. (LATER-POSSIBLY-MAYBE.) */

import ClibTwinbeam;
import CString;

/*
   
   Hamming and /soundex/ substitution and least commonly used when a word is not in 
   
   [Twinbeam]--<Apps>--<macOS>--<material>--<svenska-ord.txt>
   
   files sorted-different.
   
   compile with:
   
   clang -o x86_stegagraph -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"  \
     -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap   \
     -g -std=c2x -lc++ enforce-beskow.c built-altern.c cipher-rhode.c       \
     present-print.c amend-tape.c eight-utf.c semantic-block.c tiles-map.c  \
     regular-pool.c endian-base.c symbol-texts.c
   
   ./x86_stegagraph encrypt ./express/testimony.txt
   
 */

/*
 *  main entry.
 */

char8₋t wording₋beskow[] = { /* #embed "../../Apps/macOS/material/Beskow.txt" */ };
__builtin_int_t Beskow₋bytes() { return 2 + sizeof(wording₋beskow)/sizeof(*wording₋beskow); }

Structa code₋key₋pool, text₋word₋pool, message₋words, code₋key₋words;
/* ⬷ two regularpools and three vector<Nonabsolute>. */

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
   ALLOC alloc = ^(__builtin_int_t bytes) { return Heap₋alloc(bytes); };
   FALLOW fallow = ^(void * p) { Heap₋unalloc(p); };
   if (init₋regularpool(&code₋key₋pool,alloc) && init₋regularpool(&text₋word₋pool,alloc)) { return 5; }
   if (structa₋init(sizeof(Nonabsolute),4096,&code₋key₋words,alloc)) { return 7; }
   if (structa₋init(sizeof(Nonabsolute),4096,&message₋words,alloc)) { return 8; }
   __builtin_int_t beskow₋bytes = Beskow₋bytes();
   if (read₋utf8₋exposition(beskow₋bytes,wording₋beskow,&code₋key₋pool,&code₋key₋words)) { return 10; }
   if (read₋utf8₋exposition(utf8₋bytes,utf8₋textmaterial,&text₋word₋pool,&message₋words)) { return 11; }
   __builtin_int_t message₋word₋count = structa₋count(&message₋words), i=0;
   Nonabsolute mess, bijection; struct Unicodes text;
again:
   if (i >= message₋word₋count) { goto unagain; }
   if (reverse) {
     if (steganography₋reveal(mess,&bijection)) { return 16; }
     text = regularpool₋at(&message₋words,bijection);
   }
   else {
     if (steganography₋hide(mess,&bijection)) { return 17; }
     text = regularpool₋at(&code₋key₋words,bijection);
   }
   print("⬚ ", ﹟S(text.tetras,text.unicodes));
   goto again;
unagain:
   if (optional₋uninit₋regularpool(&text₋word₋pool,fallow)) { return 12; }
   if (deinit₋structa(&message₋words,fallow)) { return 13; }
   if (optional₋uninit₋regularpool(&code₋key₋pool,fallow)) { return 14; }
   if (deinit₋structa(&code₋key₋words,fallow)) { return 15; }
   return 0;
}


