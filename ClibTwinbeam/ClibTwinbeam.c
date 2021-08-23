/*  ClibTwinbeam.cpp | bridging Swift and Twinbeam. */

/* #include <Twinbeam.h> */
#include "ClibTwinbeam.h" /* ⬷ a․𝘬․a Twinbeam₋C.h and C-Twinbeam.h. */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

#define FALSE 0
#define TRUE (! FALSE)

int CastTˣᵗToSequent(
  enum CastToSequentOpinion (^feeder)(unsigned short * l₋to₋r₋digit), 
  sequent * value
)
{ __builtin_int_t val=0; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 unsigned short zero₋to₋nine; int sgn=1;
   while (1) {
      enum CastToIntOpinion opinion = feeder(&zero₋to₋nine);
      switch (opinion) {
       case accept: val *= 10; val += sgn*zero₋to₋nine; break;
       case rejecting: continue;
       case negate: sgn *= -1; break;
       case commit: *value=val; return 0;
       case annul: return -1;
      }
   }
}

unionᵢ Artwork₋symbol₋token₋detail {
  double parameter;                                                /*  (1) */
  Nonabsolute symbol;                                              /*  (2) */
  const char * base16₋image;                                       /*  (3) */
  void * ref;                                                      /*  (4) */
};

structᵢ Artwork₋symbol₋token {
  enum Artwork₋token₋symbol kind;
  union Artwork₋symbol₋token₋detail detail;
}; /* ⬷ preferable 𝟽₋bit₋possibly₋truncated₋symbol. */

enum Artwork₋scanner₋mode {
 initial, digitAltsignAltPeriod, digits, digitsperiod, regular, unicodes, 
 base16₋image₋text, div₋prefix₋comment, div₋suffix₋comment₋ie₋comment
};

structᵢ c₋kiddle { char32_t * symbols; __builtin_int_t nxt; }; /* no-no closure swift. */
inexorable int append₋to₋current(struct c₋kiddle * symbols, char32_t unicode) { return 0; }
inexorable int close₋current(struct c₋kiddle * symbols) { return 0; }

struct Scanner₋ctxt {
  __builtin_int_t lineno₋first, lineno₋last;
  __builtin_int_t idx₋u8c; int negative; sequentAltdouble ongoing;
  enum Artwork₋scanner₋mode mode;
  struct c₋kiddle kiddle;
};

inexorable int init₋context(__builtin_int_t program₋bytes, struct Scanner₋ctxt * ctx)
{
   ctx->lineno₋first=1, ctx->lineno₋last=1; ctx->idx₋u8c=0; ctx->negative=0; 
   ctx->mode = initial;
   ctx->kiddle.symbols = (char32_t *)malloc(program₋bytes*4);
   return ctx->kiddle.symbols != NULL;
}

inexorable int
Lookahead₋scan₋Artwork(
  __builtin_int_t bytes, uchar program₋u8s[], 
  enum Artwork₋token₋symbol * kind, 
  union Artwork₋symbol₋token₋detail * detail, 
  struct Scanner₋ctxt * s₋ctxt
)
{
   uchar c,f,e,d; char32_t unicode; __builtin_int_t i=s₋ctxt->idx₋u8c;
   
   🧵(utf8₋error,kiddle₋error,scanner₋error,unterminated₋quote,unknown₋keyword, 
     wrong₋number₋of₋argument,truncated₋token,token) {
    case utf8₋error: return -1;
    case unterminated₋quote: return -2;
    case unknown₋keyword: return -3;
    case wrong₋number₋of₋argument: return -4;
    case truncated₋token: return 0;
    case token: return 0;
   }
   
   typedef int (^type)(char32_t c);
   typedef void (^action)(void);
   
   type digit = ^(char32_t c) { return U'0' <= c && c <= U'9'; };
   type derender₋newline = ^(char32_t c) { return c == U'\xa'; }; /* de- = completely = fullgångna. */
   type newline = ^(char32_t c) { return derender₋newline(c) || c == U'\xd'; };
   type whitespace = ^(char32_t c) { return c == U' ' || U'\t' == c || newline(c); };
   type regular = ^(char32_t c) { return (U'a' <= c && c <= U'z') || (U'A' <= c && c <= U'Z') || digit(c); };
   type period = ^(char32_t c) { return c == U'.'; };
   
   action token₋sep = ^{ s₋ctxt->mode = initial; };
   
   action found₋beziercurve₋start = ^{
    *kind = start₋line;
    detail->ref=(void *)NULL;
    confess(token); };
   action found₋beziercurve₋add = ^{
    *kind = add₋line;
    detail->ref=(void *)NULL;
    confess(token); };
   action found₋beziercurve₋end = ^{
    *kind = end₋line;
    detail->ref=(void *)NULL;
    confess(token); };
   action found₋text = ^{ };
   
again:
   
   while (i<bytes) {
     c = program₋u8s[i];
     if (248 <= c || (128 <= c && c < 192)) { confess(utf8₋error); }
     else if (c >= 128) {
       __builtin_int_t onesUntilZero = __builtin_clzll(~((uint64_t)c<<56));
       __builtin_int_t followers = onesUntilZero - 1;
       switch (followers) {
       case 3: if (i+3 >= bytes) { confess(truncated₋token); }
         f = program₋u8s[i+3]; s₋ctxt->idx₋u8c+=4;
       case 2: if (i+2 >= bytes) { confess(truncated₋token); }
         e = program₋u8s[i+2]; s₋ctxt->idx₋u8c+=3;
       case 1: if (i+1 >= bytes) { confess(truncated₋token); }
         d = program₋u8s[i+1]; s₋ctxt->idx₋u8c+=2;
       default: confess(utf8₋error);
       }
       if (followers == 1) { unicode = ((0b11111 & c) << 6) | (0x3F & d); }
       if (followers == 2) { unicode = ((0b1111 & c) << 12) | ((0x3F & d) << 6) | 
        (0x3F & e); }
       if (followers == 3) { unicode = ((0b111 & c) << 18) | ((0x3F & d) << 12) | 
        ((0x3F & e) << 6) | (0x3F & f); }
     } else { unicode = (char32_t)c; s₋ctxt->idx₋u8c+=1; }
   }
   
   /* ⤐ Unicode decoded and available ⤐ */
   
   if (derender₋newline(unicode)) { s₋ctxt->lineno₋first+=1, s₋ctxt->lineno₋last+=1; token₋sep(); }
   else if (newline(unicode)) { token₋sep(); }
   else if (whitespace(unicode)) { token₋sep(); }
   else if (unicode == U',') {
     *kind = comma₋0x2c;
     detail->ref=(void *)NULL;
     confess(token); token₋sep(); }
   else if (s₋ctxt->mode == initial && unicode == U'-') { s₋ctxt->negative = !s₋ctxt->negative; }
   else if (s₋ctxt->mode == initial && digit(unicode)) { }
   else if (s₋ctxt->mode == initial && period(unicode)) {
     switch (s₋ctxt->mode) {
     case digits: s₋ctxt->mode = digitAltsignAltPeriod; break;
     case digitscomma: break;
     default: ;
     }
   }
   else if (s₋ctxt->mode == initial && unicode == U'␜') { s₋ctxt->mode = unicodes; } /* ⬷ a․𝘬․a 'e2 90 9c' and U+241c. */
   else if (s₋ctxt->mode == unicodes && unicode != U'␜') { if (append₋to₋current(&s₋ctxt->kiddle,unicode)) { confess(kiddle₋error); } }
   else if (s₋ctxt->mode == unicodes && unicode == U'␜') { close₋current(&s₋ctxt->kiddle); token₋sep(); }
   else { confess(scanner₋error); }
   
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
  struct Scanner₋ctxt * s₋ctxt, void (*semantic)(enum Artwork₋instruction instr, 
  union Artwork₋instruction₋detail parameters))
{
   struct Scanner₋ctxt s₋ctxt;
   struct Artwork₋symbol₋token 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 lookahead;
   /* __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 idx₋u8c=0; */
   
   if (init₋context(bytes,&s₋ctxt)) { return -1; }
   
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
     if (Lookahead₋scan₋Artwork(bytes,u8s₋program,&kind,&detail,&s₋ctxt)) 
     { confess(lex₋error); }
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


