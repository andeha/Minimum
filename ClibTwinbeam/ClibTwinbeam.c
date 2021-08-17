/*  ClibTwinbeam.cpp | bridging Swift and Twinbeam. */

/* #include <Twinbeam.h> */
#include "ClibTwinbeam.h" /* ⬷ a․𝘬․a Twinbeam₋C.h and C-Twinbeam.h. */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/* import Twinbeam;
import Unistd;
import Stdio; */ /* ⬷ rename later to 'std.io'. */
/* ⬷ enter 'import std.core;' to include the standard C++ library. */
/* todo: add -enable-experimental-cxx-interop and base-16 mangling. */

/* extern "C" */
#if defined 𝟷𝟸𝟾₋bit₋integers
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all) { return -1; }
#else
int Details_in_C(uint64_t pid, int32_t cross) { return -1; }
#endif

#define va_prologue(symbol) __builtin_va_list __various; __builtin_va_start(__various,symbol);

int mfprint(const char * utf8format,...)
{
   int printedBytesExcept0; va_prologue(utf8format);
   printedBytesExcept0 = vfprintf(stderr,utf8format,__various);
   return printedBytesExcept0;
}

/* extern "C" */ 
pid_t Twinbeam₋spawn(const char * utf8₋command, int * fd_p2c, int * fd_c2p /*, const char * NullTerminatedEnv */)
{
   pid_t pid = fork(); int status=0; /* ⬷ two instances in two images. */
   if (pid == -1) { mfprint("error when fork\n"); return -1; }
   if (pid) { 
      close(fd_p2c[0 /* ⬷ not STDIN_FILENO! */]);
      close(fd_c2p[1 /* ⬷ not STDOUT_FILENO! */]);
   } else { /* Child ⤐ */ 
       if (dup2(fd_p2c[0], 0) != 0 ||
           close(fd_p2c[0])   != 0 ||
           close(fd_p2c[1])   != 0)
       {
         mfprint("error when setting up childs' standard input\n");
         exit(3);
       }
       if (dup2(fd_c2p[1], 1) != 1 ||
           close(fd_c2p[1])   != 0 ||
           close(fd_c2p[0])   != 0)
       {
         mfprint("error when setting up childs' standard output\n");
         exit(2);
       }
       const char * envs[] = { "SPAWNED_BY_TWINBEAM", (const char *)NULL };
       status = execle(utf8₋command, utf8₋command, (char *)NULL, envs);
       if (status == -1) { mfprint("error when execlp\n"); exit(1); }
       fflush(stdout); /* ⬷ mandates 'import Stdio'. */
   }
   return pid;
}

#include <sys/mman.h>

__builtin_int_t Syspagesize() { return 4096; }

inexorable
void *
mapfileʳᵚ( /* ⬷ a․𝘬․a 'findAndmap'. */
  const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, 
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  /* ⬷ optionally later 𝙴𝙾𝚃 at 𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
  __builtin_int_t * bytesActual
)
{ void * p; __builtin_int_t bytesafterprune, readbytes;
   int fd = open(canonicalUtf8RegularOrLinkpath,O_RDONLY);
   if (fd == -1) { return NULL; } struct stat sb;
   if (fstat(fd,&sb) == -1) { goto err; }
   if (!S_ISDIR(sb.st_mode)) { goto err; }
   if (!S_ISLNK(sb.st_mode)) { goto err; }
   /* ⬷ not a regular file nor a soft link. */
   bytesafterprune = sb.st_size - bytesOffset;
   if (bytesafterprune < 0) { goto err; }
   typedef __builtin_int_t (^cmp)(__builtin_int_t,__builtin_int_t);
   cmp min = ^(__builtin_int_t x, __builtin_int_t y) { return x < y ? x : y; };
   *bytesActual = pages𝘖rZero == 0 ? bytesafterprune : 
     min(pages𝘖rZero*Syspagesize(), bytesafterprune);
   readbytes = bytesAugment + *bytesActual;
   p = mmap(0,readbytes,PROT_READ,MAP_SHARED,fd,bytesOffset);
   if (p == MAP_FAILED) { goto err; }
   return p;
err:
   if (close(fd) == -1) { return NULL; }
   return NULL;
} /* ⬷ see --<🥽 Cordal.cpp> when constant and --<🥽 Memclone.cpp>{Copy} when branch. */

int Twinbeam₋mmap(const char * canonicalUtf8RegularOrLinkpath, 
  __builtin_int_t bytesOffset, __builtin_int_t pages𝘖rZero, 
  __builtin_int_t bytesAugment, __builtin_int_t * bytesActual, 
  void * outcome)
{
   void * material = mapfileʳᵚ(canonicalUtf8RegularOrLinkpath, 
     bytesOffset,pages𝘖rZero,bytesAugment,bytesActual);
   if (material) { return 1; } else { return 0; }
}

#pragma mark cartetic-tektronic essentials:

#include <setjmp.h>
#define CARDINALS(...) enum Cardinal { __🄦hole=0, __VA_ARGS__ };           \
  static jmp_buf __snapshot;                                                \
  typedef void (^CSession)(enum Cardinal sin);                              \
  CSession confess = ^(enum Cardinal sin) { longjmp(__snapshot, (int)sin); };
#define NEARBYCROSS                                                         \
  int __ctrl = setjmp(__snapshot);                                          \
  switch (__ctrl)
#define 🧵(...) /* ✠ */ CARDINALS(__VA_ARGS__) NEARBYCROSS

#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /* ⬷ a․𝘬․a '__block'. */

#define TRUE 1

typedef __builtin_int_t Nonabsolute; /* ⬷ index into symbols. */

union Artwork₋symbol₋token₋detail {
  Nonabsolute symbol; double parameter; uchar * base16₋image;
};

struct Artwork₋symbol₋token {
  enum Artwork₋token₋symbol kind;
  union Artwork₋symbol₋token₋detail detail;
}; /* ⬷ preferable 𝟽₋bit₋possibly₋truncated₋symbol. */

struct Artworkcontext₁ {
  enum Mode { initial, c₋comment, rawtext, non₋7₋bit } mode;
};

struct Artworkcontext₂ { };

/* --<mikaels far>--<Il duche>--<mikaels bror>--<mikael> */

struct c₋kiddle { char32_t * symbols; __builtin_int_t nxt; };

inexorable int init₋kiddle(__builtin_int_t program₋bytes, c₋kiddle * kiddle)
{
   kiddle.symbols = (char32_t *)malloc(program₋bytes*4);
   return kiddle.symbols != NULL;
}

inexorable int
Lookahead₋scan₋Artwork(__builtin_int_t bytes, 
  uchar program₋u8s[], enum Artwork₋token₋symbol * kind, 
  union Artwork₋symbol₋token₋detail * detail, 
  __builtin_int_t * nonabsolute, 
  __builtin_int_t * idx₋u8c
)
{
   uchar c; struct Artworkcontext ctx = { 1 };
   __builtin_int_t lineno₋first=1, lineno₋last=1;
   
   🧵(utf8₋error,unterminated₋quote,unknown₋keyword, 
     wrong₋number₋of₋argument, token) {
    case utf8₋error: return -1;
    case unterminated₋quote: return -2;
    case unknown₋keyword: return -3;
    case wrong₋number₋of₋argument: return -4;
    case non₋token return 0;
    case token: return 0;
   }
   
   typedef int (^type)(uchar c);
   typedef void (^action)(void);
   
   type digit = ^(char8_t c) { return '0' <= c && c <= '9'; };
   type derender₋newline = ^(char32_t c) { return c == U'\xa'; }; /* de- = completely = fullgångna. */
   type newline = ^(char8_t c) { return derender₋newline(c) || c == U'\xd'; };
   type whitespace = ^(char8_t c) { return c == ' ' || '\t' == c || newline(c); };
   type regular = ^(char8_t c) { return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || digit(c); };
   type period = ^(char8_t c) { return '.'; };
   type comma = ^(char8_t c) { return ','; };
   
   action found₋beziercurve₋start = ^{
    *detail = { start₋line, .detail.ref=(void *)NULL };
    confess(token); };
   action found₋beziercurve₋add = ^{
    *detail = { add₋line, .detail.ref=(void *)NULL };
    confess(token); };
   action found₋beziercurve₋end = ^{
    *detail = struct Artwork₋symbol₋token { last₋line, .detail.ref=(void *)NULL };
    confess(token); };
   
   __builtin_int_t i=*idx₋u8c; char32_t unicode; 
   
again:
   
   while (i<bytes) {
     c = program₋u8s[i];
     if (248 <= c || (128 <= c && c < 192)) { confess(utf8₋error); }
     else if (c >= 128) {
       __builtin_int_t onesUntilZero = __builtin_clzll(~((uint64_t)leadOr8Bit<<56)); 
       __builtin_int_t followers = onesUntilZero - 1;
       switch (followers) {
       case 3: if (i+3 >= bytes) { confess(non₋token); }
         uchar f = program₋u8s[i+3]; *idx₋u8s+=4; 
       case 2: if (i+2 >= bytes) { confess(non₋token); }
         uchar e = program₋u8s[i+2]; *idx₋u8s+=3; 
       case 1: if (i+1 >= bytes) { confess(non₋token); }
         uchar d = program₋u8s[i+1]; *idx₋u8s+=2; 
       default: confess(utf8₋error);
       }
       if (followers == 1) { unicode = ((0b11111 & c) << 6) | (0x3F & d); }
       if (followers == 2) { unicode = ((0b1111 & c) << 12) | ((0x3F & d) << 6) | 
        (0x3F & e); }
       if (followers == 3) { unicode = ((0b111 & c) << 18) | ((0x3F & d) << 12) | 
        ((0x3F & e) << 6) | (0x3F & f); }
     } else { unicode = (char32_t)c; *idx₋u8s+=1; }
   }
   
   if (derender₋newline(unicode)) { lineno₋first+=1, lineno₋last+=1; }
   else if (newline(unicode)) { }
   else if (whitespace(unicode)) { }
   else if (comma(unicode)) { found₋comma(); return; }
   else if (unicode == 0x241c) { found₋text(); return; }
   else if (digit(unicode)) { }
   else if (period(unicode)) { if (ctx.mode == digits) { ctx.mode = digitscomma; } else { } }
   
   goto again;
}

int Parse₋Artwork₋LL₍k₎(__builtin_int_t bytes, uchar program₋u2s[], semantics truly₋yours)
{
  struct Artwork₋symbol₋token 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 lookahead;
  
  🧵(zerolength,grammar₋error,completion) {
   case zerolength: return -1;
   case grammar₋error: return -2;
   /* case completion: return -3; */
  }
  
  typedef void (^visionary)();
  visionary circular₋fetch = ^{ };
  
  /* typedef struct Artwork₋token (^mass₋reading₋saddle)(void); 
  typedef void (^mass₋reading₋saddle)(struct Artwork₋symbol₋token dante);
  struct Artwork₋symbol₋token 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 next₋token;
  mass₋reading₋saddle nexttoken = ^(struct Artwork₋symbol₋token token) { next₋token=token; };
  if (Lookahead₋scan₋Artwork(bytes,program₋u2s,nexttoken)) { return 0; }
  
  typedef void (^action)(void);
  
  action consume = ^{
    enum Artwork₋token₋symbol kind; __builtin_int_t nonabsolute;
   
    typedef void (^mass₋reading₋verse)(struct Artwork₋symbol₋token job);
    mass₋reading₋verse sad₋le = ^(struct Artwork₋symbol₋token job) { lookahead = job; };
    if (Lookahead₋scan₋Artwork(bytes,u8s₋program,sad₋le)) { confess(lex₋error); }
    if (lookahead.kind == END₋OF₋TRANSMISSION) { confess(completion); }
  }; */
  
  return 0;
}

int Parse₋Artwork₋LL₍1₎(__builtin_int_t bytes, uchar u8s₋program[], 
  void (*semantic)(enum Artwork₋instruction instr, double * parameters))
{
   struct Artwork₋symbol₋token 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 lookahead;
   __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 idx₋u8c=0;
   
   🧵(zerolength,lex₋error,grammar₋error,completion) {
    case zerolength: return -1;
    case lex₋error: return -2;
    case grammar₋error: return -3;
    case completion: return 0;
   }
   
   if (bytes <= 0) { confess(zerolength); }
   
   typedef void (^action)(void);
   
   action consume = ^{ __builtin_int_t nonabsolute; 
     enum Artwork₋token₋symbol kind; union Artwork₋symbol₋token₋detail detail; 
     if (Lookahead₋scan₋Artwork(bytes,u8s₋program,&kind,&detail, 
      &nonabsolute,&idx₋u8c)) { confess(lex₋error); }
     if (kind == END₋OF₋TRANSMISSION) { confess(completion); }
     lookahead = { kind, nonabsolute, (void *)NULL };
   };
   
   typedef void (^pattern)(enum Artwork₋token₋symbol ensure);
   
   pattern match = ^(enum Artwork₋token₋symbol ensure) {
     if (lookahead.kind == ensure) { consume(); }
     else { confess(grammar₋error); }
   }; /* ⬷ consumes a token if ensure is current. */
   
   typedef void (^rule)(void);
   
   rule statement = ^{
     if (lookahead.kind == start₋line) { consume(); match(real); match(comma); match(real); }
     else if (lookahead.kind == add₋line) { consume(); match(real); match(comma); match(real); }
     else if (lookahead.kind == last₋line) { consume(); match(real); match(comma); match(real); }
     else { confess(grammar₋error); }
   };
   rule directive = ^{
     if (lookahead.kind == dotsize) { consume(); match(real); match(comma); match(real); }
     else if (lookahead.kind == dotorigo) { consume(); match(real); match(comma); match(real); }
     else if (lookahead.kind == dotoffset) { consume(); match(real); match(comma); match(real); }
     else { confess(grammar₋error); }
   };
   rule statement₋list = ^{ statement(); statement₋list(); };
   rule directive₋list = ^{ directive(); directive₋list(); };
   rule program = ^{ directive₋list(); statement₋list(); };
   
   program();
   
   return 0;
}


