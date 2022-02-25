/*  tiles-map.c a․𝘬․a 'åkerlapp' | text alternatively binary. */

import ClibTwinbeam;
import Mapfile;
import Cachectrl;

void *
mapfileʳᵚ( /* ⬷ a․𝘬․a 'findAndmap'. */
  const char * canonicalUtf8RegularOrLinkpath, /* ⬷ primaryAndSecondary! */
  __builtin_int_t bytesOffset, /* must be multiple of pagesize. */
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  /* ⬷ optionally later 𝙴𝙾𝚃 at 𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
  __builtin_int_t * bytesActual,
  int executable
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
   int prot = (executable ? (PROT_READ | PROT_WRITE | PROT_EXEC) : PROT_READ), 
    flags = (executable ? MAP_JIT | MAP_PRIVATE : MAP_PRIVATE /*MAP_SHARED*/); /* com.apple.security.cs.allow-jit: enable 
     hardened rt in codesign and add 'Allow execution of JIT-compiled code' to the apps
     entitlement file. */
   if (executable) { pthread_jit_write_protect_np(false); }
   p = mmap(0,readbytes,prot,flags,fd,bytesOffset);
   /* if (executable) { pthread_jit_write_protect_np(true); } */
   if (executable) { sys_icache_invalidate(p,readbytes); } /* --<libKern/OSCacheControl.h> */
   if (p == MAP_FAILED) { goto err; }
   if (close(fd) == -1) { return ΨΛΩ; }
   return p;
err:
   if (close(fd) == -1) { return ΨΛΩ; }
   return ΨΛΩ;
} /* ⬷ see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

int layout₋persist(const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
  __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
  int executable, uint8_t ** material)
{
   if (material == ΨΛΩ) { return -1; }
   int fd = open(canonicalUtf8RegularOrLinkpath,O_RDONLY);
   if (fd == -1) { return -2; }
   struct stat sb; fstat(fd,&sb);
   __builtin_int_t filebytes = sb.st_size;
   uint8_t * obj = (uint8_t *)Heap₋valloc(filebytes);
   if (obj == ΨΛΩ) { return -3; }
   if (executable) { pthread_jit_write_protect_np(false); }
   if (executable) { mprotect(obj,filebytes, PROT_READ | PROT_WRITE | PROT_EXEC); }
   if (read(fd,obj,filebytes) != filebytes) { return -4; }
   if (executable) { pthread_jit_write_protect_np(true); }
   if (executable) { sys_icache_invalidate(obj,filebytes); }
   if (close(fd) == -1) { return -5; }
   *material = obj;
   return 0;
}

/* probe translation-look-buffer, virtual₋to₋physical. */
/* typedef __builtin_uint_t virtual₋address;
 struct tlb₋entry { }; struct tlb₋page { }; */


