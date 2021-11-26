/* 􀻬 åkerlapp.c | text alternatively binary. */

import ClibTwinbeam;
import Mapfile;

void *
mapfileʳᵚ( /* ⬷ a․𝘬․a 'findAndmap'. */
  const char * canonicalUtf8RegularOrLinkpath, /* ⬷ primaryAndSecondary! */
  __builtin_int_t bytesOffset, 
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  /* ⬷ optionally later 𝙴𝙾𝚃 at 𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
  __builtin_int_t * bytesActual
)
{ void * p; __builtin_int_t bytesafterprune, readbytes;
   typedef __builtin_int_t (^cmp)(__builtin_int_t,__builtin_int_t);
   cmp min = ^(__builtin_int_t x, __builtin_int_t y) { return x < y ? x : y; };
   int fd = open(canonicalUtf8RegularOrLinkpath,O_RDONLY);
   if (fd == -1) { return NULL; } struct stat sb;
   if (fstat(fd,&sb) == -1) { goto err; }
   if (S_ISDIR(sb.st_mode)) { goto err; }
   if (S_ISLNK(sb.st_mode)) { goto err; }
   /* ⬷ not a regular file nor a soft link. */
   bytesafterprune = sb.st_size - bytesOffset;
   if (bytesafterprune < 0) { goto err; }
   *bytesActual = pages𝘖rZero == 0 ? bytesafterprune : 
     min(pages𝘖rZero*Syspagesize(), bytesafterprune);
   readbytes = bytesAugment + *bytesActual;
   p = mmap(0,readbytes,PROT_READ,MAP_SHARED,fd,bytesOffset);
   if (p == MAP_FAILED) { goto err; }
   return p;
err:
   if (close(fd) == -1) { return ΨΛΩ; }
   return ΨΛΩ;
} /* ⬷ see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

int Twinbeam₋mmap(const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
  __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
  void * outcome)
{
   void * material = mapfileʳᵚ(canonicalUtf8RegularOrLinkpath, 
     bytesOffset,pages𝘖rZero,bytesAugment,bytesActual);
   if (material) { outcome=material; return 1; } else { return 0; }
}

EXT₋C void * Heap₋alloc(__builtin_int_t bytes) { return malloc(bytes); }

EXT₋C void Heap₋unalloc(void * p) { free(p); }

EXT₋C void * Heap₋realloc(void * p, __builtin_int_t to₋bytes) { return realloc(p,to₋bytes); }

/* EXT₋C void * Heap₋realloc₂(void * p, __builtin_int_t to₋bytes)
{
  size_t old_bytes = malloc_size(p);
  uint8_t * new_words = (uint8_t *)malloc(to₋bytes);
  Copy8Memory((ByteAlignedRef)new_words, (ByteAlignedRef)p, old_bytes);
  Heap₋unalloc(p);
  return new_words;
} */

EXT₋C void * Heap₋valloc(__builtin_int_t bytes) { return valloc(bytes); }


