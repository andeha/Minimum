/*  cipher-rhode.c | unicode steganography and the 7-bit ascii alphabet. */

import ClibTwinbeam;

inexorable int token₋separator(char32̄_t uc) { return uc == ' ' || 
 uc == '\t' || uc == '\xa' || uc == '\xd'; }

int read₋utf8₋exposition(int byte₋count, char8₋t * utf8₋bytes, 
 struct structa * pool, struct structa * words)
{ char8₋t * leadOr8Bit; char32̄_t uc;
   int32_t tetras=0; char32̄_t cs[1024]; __builtin_int_t i=0,j=0, bytes;
again:
   if (i >= byte₋count) { return -1; }
   leadOr8Bit = i + utf8₋bytes;
   bytes = 1 + Utf8Followers(*leadOr8Bit);
   uc = Utf8ToUnicode(leadOr8Bit,bytes);
   if (token₋separator(uc)) {
     if (cs[j-1] != '-') {
      for (short x=0; x<j; x+=1) {
       if (copy₋append₋onto₋regular(pool,tetras,cs,^(__builtin_int_t bytes) { return Heap₋alloc(bytes); } )) { return -2; }
      }
      Nonabsolute ref; if (regularpool₋datum₋text(pool,tetras,&ref)) { return -3; }
     }
     j = 0;
   }
   cs[j] = uc; j += 1; i += bytes;
   if (j >= 1024) { return -2; }
   goto again;
}

int steganography₋hide(Nonabsolute word, Nonabsolute * code)
{
   return 0;
}

int steganography₋reveal(Nonabsolute code, Nonabsolute * word)
{
   return 0;
}


