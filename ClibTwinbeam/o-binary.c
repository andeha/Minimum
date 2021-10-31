/* 􀬓 o-binary.c | sections, segments and 'tape recorder'. */

import ClibTwinbeam;
import Mach_O_binary;

void
Symbols(
  const char * utf8exepath,
  void (^each₋symbol)(const char * sym, uint64_t addr, bool * stop))
{ __builtin_int_t bytesActual;
   extern void * mapfileʳᵚ(const char * canonicalUtf8RegularOrLinkpath,
   __builtin_int_t, __builtin_int_t , __builtin_int_t,__builtin_int_t *);
    uint8_t * obj = (uint8_t *)mapfileʳᵚ(utf8exepath, 0, 0, 0, &bytesActual);
    uint8_t * obj_p = obj;
   
    struct mach_header_64 * header = (struct mach_header_64 *)obj_p;
    obj_p += sizeof *header;
    struct section * sections = 0;
    uint32_t nsects;
   
    bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 outer₋stop = false;
   
    for (int i=0; i<header->ncmds; ++i) {
      struct load_command *lc = (struct load_command *)obj_p;
      if (lc->cmd == LC_SYMTAB) {
         struct symtab_command *symtab = (struct symtab_command *)obj_p;
         obj_p += sizeof *symtab;
         struct nlist_64 *ns = (struct nlist_64 *)(obj + symtab->symoff);
         char * strtable = (char *)(obj + symtab->stroff);
         for (int i=0; i<symtab->nsyms; ++i) {
            struct nlist_64 *entry = ns + i;
            uint32_t idx = entry->n_un.n_strx;
            if ((entry->n_type & N_TYPE) == N_SECT) { each₋symbol(strtable + idx, 
              entry->n_value, &outer₋stop); }
            if (outer₋stop) { return; }
         }
      } else if (lc->cmd == LC_SEGMENT) {
         struct segment_command * segment = (struct segment_command *)obj_p;
         obj_p += sizeof *segment;
         nsects = segment->nsects;
         sections = (struct section *)obj_p;
         obj_p += nsects * sizeof *sections;
      } else { obj_p += lc->cmdsize; }
    }
}


