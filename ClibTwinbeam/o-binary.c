/*  o-binary.c | sections, segments and 'tape recorder'. */

import ClibTwinbeam;
import Mach_O_binary;

int is_fat(uint32_t magic) { return magic == FAT_CIGAM; }

void
Symbols(
  const char * utf8exepath,
  void (^each₋symbol)(const char * sym, uint64_t addr, bool * stop))
{ __builtin_int_t bytesActual;
   extern void * mapfileʳᵚ(const char * canonicalUtf8RegularOrLinkpath,
   __builtin_int_t, __builtin_int_t , __builtin_int_t,__builtin_int_t *);
    uint8_t * obj = (uint8_t *)mapfileʳᵚ(utf8exepath,0,0,0,&bytesActual);
    uint8_t * obj_p = obj;
    uint32_t magic = *(uint32_t *)obj;
    if (is_fat(magic)) {
      struct fat_header * fheader = (struct fat_header *)obj_p;
      obj_p += sizeof(struct fat_header);
#define SWAP32(x) __builtin_bswap32(x)
      uint32_t acount = SWAP32(fheader->nfat_arch);
      print("is-fat containing ⬚ archs.\n", ﹟d((__builtin_int_t)acount));
      for (int i=0; i<acount; ++i) {
        struct fat_arch * arch = (struct fat_arch *)obj_p;
        obj_p += sizeof(struct fat_arch);
        uint32_t cputype = SWAP32(arch->cputype);
        if (cputype == CPU_TYPE_X86_64) { print("CPU_TYPE_X86_64\n"); 
         uint32_t offset = SWAP32(arch->offset); obj_p = offset + obj;
         print("offset is ⬚\n", ﹟x((__builtin_uint_t)offset));
         goto found; }
        if (arch->cputype == CPU_TYPE_ARM64) { print("CPU_TYPE_ARM64\n"); }
      }
found:
      ;
    }
    struct mach_header_64 * header = (struct mach_header_64 *)obj_p;
    obj_p += sizeof(struct mach_header_64);
    struct section * sections = 0;
    uint32_t nsects;
   
    bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 outer₋stop = false;
   
    for (int i=0; i<header->ncmds; ++i) {
      struct load_command *lc = (struct load_command *)obj_p;
      if (lc->cmd == LC_SYMTAB) {
        struct symtab_command *symtab = (struct symtab_command *)obj_p;
        obj_p += sizeof(struct symtab_command);
        struct nlist_64 * ns = (struct nlist_64 *)(obj + symtab->symoff);
        char * strtable = (char *)(obj + symtab->stroff);
        for (int i=0; i<symtab->nsyms; ++i) {
           struct nlist_64 * entry = ns + i;
           uint32_t idx = entry->n_un.n_strx;
           if ((entry->n_type & N_TYPE) == N_SECT) { each₋symbol(strtable + idx, 
             entry->n_value, &outer₋stop); }
           if (outer₋stop) { return; }
        }
      } else if (lc->cmd == LC_SEGMENT) {
        struct segment_command * segment = (struct segment_command *)obj_p;
        obj_p += sizeof(struct segment_command);
        nsects = segment->nsects;
        sections = (struct section *)obj_p;
        obj_p += nsects * sizeof(struct section);
      } else { obj_p += lc->cmdsize; }
    }
}


