/*  􀥳 lingustics-epi.c | an epitomic recursive descent parser. */

import ClibTwinbeam;
import Stdlib;
import Setjmp;

/*
  
  program -> assign
  program -> expr
  
  assign -> Ident = expr ';' alternatively '\n'
  
  expr -> term + term
  expr -> term - term
  expr -> term
  
  term -> factor * factor
  term -> factor / factor
  term -> factor
  
  factor -> affidare
  factor -> - affidare
  factor -> + affidare
  
  affidare -> circum ^ circum
  affidare -> circum
  
  circum -> real-literal
  circum -> integer-literal
  circum -> ( expr )
  circum -> funct ( expr ) alt. funct ( )
  circum -> identifier
  
 */

/* factor -> unary @ N(sigma,my), [max,min], [min,max], [mA] */
/* unary -> circum 'basväljare' circum  ⬷ hilbertväljare. */

/*
  
  clang -o x86_epitom-7 -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"       \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap      \
    -g -std=c18 -lc++ lingustics-epi.c ../Releases/libClibTwinbeam.a
  
  ./x86_epitom-7 ./express/comment.txt
  
 */

/*
 *  unicode scanner.
 */

enum lexer₋mode { mode₋initial, mode₋multiregular, mode₋fract /* a․𝘬․a 'relative' */, 
 mode₋integer, mode₋singleline₋comment, mode₋multiline₋comment };

typedef struct lexer {
  __builtin_int_t symbols; char32̄_t * text₋heap;
  __builtin_int_t tip₋unicode;
  __builtin_int_t lineno₋first, lineno₋last;
  __builtin_int_t column₋first, column₋last;
  enum lexer₋mode mode; short symbols₋in₋regular; short symbols₋in₋fract;
  char32̄_t regular[2048]; Sequenta ongoing; short fract₋𝟶to𝟿s[2049];
  char8₋t * src₋path; int integer₋alt₋fract₋regular₋passed;
} lexer;

char8₋t * utf8dupn(char8₋t * u8s, __builtin_int_t maxu8bytes)
{ __builtin_int_t bytes = Utf8BytesUntilNull(u8s,maxu8bytes);
   void * start = Heap₋alloc(bytes);
   Copy8Memory((ByteAlignedRef)start, (ByteAlignedRef)u8s, bytes);
   return start;
} /* ⬷ a․𝘬․a strdup₋for₋utf8. Note U+8000 in UTF-8 is E0 *) *). */

inexorable int context₋init(char8₋t * utf8txtpath, lexer * ctx)
{
   __builtin_int_t i=0,j=0, bytesActual, bytes;
   char8₋t * leadOr8Bit; char32̄_t uc;
   char8₋t * utf8₋text = (char8₋t *)mapfileʳᵚ((const char *)utf8txtpath,0,0,0,&bytesActual);
   if (utf8₋text == ΨΛΩ) { return -1; }
   ctx->text₋heap = (char32̄_t *)Heap₋alloc(4*(bytesActual + 1));
   if (ctx->text₋heap == ΨΛΩ) { return -2; }
   ctx->tip₋unicode=0;
   ctx->lineno₋first=1; ctx->lineno₋last=1;
   ctx->column₋first=1; ctx->column₋last=1;
   ctx->symbols₋in₋regular=0; ctx->symbols₋in₋fract=0;
   __builtin_int_t maxu8bytes = BUILTIN₋INT₋MAX;
   ctx->src₋path=utf8dupn(utf8txtpath,maxu8bytes);
   ctx->ongoing=accumulative₋zero();
   ctx->mode=mode₋initial;
   ctx->integer₋alt₋fract₋regular₋passed = false;
again:
   if (i >= bytesActual) { ctx->symbols = j; 
     *(ctx->text₋heap + ctx->symbols) = U'\x4';
     return 0;
   }
   leadOr8Bit = i + utf8₋text;
   bytes = Utf8Followers(*leadOr8Bit) + 1;
   uc = Utf8ToUnicode(leadOr8Bit,bytes);
   *(ctx->text₋heap + j) = uc;
   i += bytes; j += 1;
   goto again;
}

typedef void (^Context₋dealloc)(void *);
Context₋dealloc Fall⒪⒲ = ^(void * p) { free(p); };

inexorable void context₋deinit(lexer * ctx)
{
   Fall⒪⒲(ctx->src₋path);
}

enum token { END₋OF₋TRANSMISSION=1, TERMINATING₋END₋OF₋LINE₋AND₋ASSIGN, 
 VAR_KEYWORD, IDENT, EQUALS_KEYWORD, NUMERIC₋CONST, SEMICOLON, 
 LTE_KEYWORD, GTE_KEYWORD, GT_KEYWORD, LT_KEYWORD, 
 PLUS_KEYWORD, MINUS_KEYWORD, MULT_KEYWORD, DIV_KEYWORD, CIRCUM_KEYWORD, 
 LPAREN_KEYWORD, RPAREN_KEYWORD
};

struct token₋detail {
  union {
    struct Regular𝘖rIdent { int symbols; char32̄_t * start; } regular𝘖rIdent;
    Sequenta literal;
  } store;
  int kind;
  __builtin_int_t lineno₋first, column₋first, column₋last, lineno₋last;
  lexer * predecessor₋src;
};

char * tokenname(enum token gritty)
{
  switch (gritty) {
  case TERMINATING₋END₋OF₋LINE₋AND₋ASSIGN: return "statement-separative-eol";
  case END₋OF₋TRANSMISSION: return "eot";
  case VAR_KEYWORD: return "var";
  case IDENT: return "Ident";
  case EQUALS_KEYWORD: return "=";
  case NUMERIC₋CONST: return "numeric-const";
  case SEMICOLON: return "semicolon";
  case LTE_KEYWORD: return "<=";
  case GTE_KEYWORD: return ">=";
  case GT_KEYWORD: return ">";
  case LT_KEYWORD: return "<";
  case PLUS_KEYWORD: return "+";
  case MINUS_KEYWORD: return "-";
  case MULT_KEYWORD: return "*";
  case DIV_KEYWORD: return "/";
  case CIRCUM_KEYWORD: return "^";
  case LPAREN_KEYWORD: return "(";
  case RPAREN_KEYWORD: return ")";
  }
}

/* rt₋namespace { */
uint32_t diagnosis₋count=0;
/* } */

EXT₋C long write(int fd, const void * s, long unsigned nbyte);
EXT₋C int print﹟(void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
 const char * utf8format, __builtin_va_list argument);

void Diagnos(int type, void * /* lexer₋alt₋detail */ ctx, int bye, char * text, ...)
{ va_prologue(text); char8₋t * src₋path;
  __builtin_int_t lineno₋first, first₋column, linecount, last₋column;
  if (type == 2) { lexer * s₋ctxt = (lexer *)ctx;
    lineno₋first = s₋ctxt->lineno₋first, 
    first₋column = s₋ctxt->column₋first, 
    linecount = 1 + s₋ctxt->lineno₋last - lineno₋first, 
    last₋column = s₋ctxt->column₋last; /* ⬷ diagnos-2. */
    src₋path = s₋ctxt->src₋path;
  } else if (type == 1) { struct token₋detail * ahead = 
     (struct token₋detail *)ctx;
    lineno₋first = ahead->lineno₋first, 
    first₋column = ahead->column₋first, 
    linecount = 1 + ahead->lineno₋last - lineno₋first, 
    last₋column = ahead->column₋last;
    src₋path = ahead->predecessor₋src->src₋path;
  } else if (type == 0) {
   /* see --[Twinbeam]--<Radiosymbol>--<AST.h> */
  }
  typedef void (^Utf8)(char8₋t * u8s, __builtin_int_t bytes);
  Utf8 out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1,(const void *)u8s,bytes); };
  print(out,"⬚:⬚:⬚—⬚ ", ﹟s(src₋path), ﹟d(lineno₋first), ﹟d(first₋column), 
   ﹟d(last₋column));
  print﹟(out, text, __various);
  print(out, " (⬚ line", ﹟d(linecount));
  if (linecount != 1) { print("s"); }
  print(out, ")\n");
  va_epilogue;
  if (bye) { exit(1); } else { Pult💡(diagnosis₋count); }
} /*  ⬷ write texts prefixed with 'error:', 'warning:' and 'internal-error:'. */

enum token next₋token(lexer * s₋ctxt, 
  struct token₋detail * detail₋out)
{
   __builtin_int_t i,symbols=s₋ctxt->symbols;
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 char32̄_t ucode, ucode₊₁; int uc₋last=0;
   detail₋out->predecessor₋src = s₋ctxt;
   
   typedef int (^type)(char32̄_t unicode);
   typedef void (^collect)(char32̄_t);
   typedef void (^perform)(void);
   typedef int (^query)(void);
   
   type digit = ^(char32̄_t c) { return U'0' <= c && c <= U'9'; };
   type derender₋newline = ^(char32̄_t c) { return c == U'\xa'; };
   type newline = ^(char32̄_t c) { return derender₋newline(c) || c == U'\xd'; };
   type whitespace = ^(char32̄_t c) { return c == U' ' || U'\t' == c || newline(c); };
   type letter = ^(char32̄_t c) { return (U'a' <= c && c <= U'z') || (U'A' <= c && c <= U'Z'); };
   type letter₋alt₋digit = ^(char32̄_t c) { return letter(c) || digit(c); };
   type period = ^(char32̄_t c) { return c == U'.'; };
   
   perform reset = ^{
     s₋ctxt->symbols₋in₋fract=0;
     s₋ctxt->symbols₋in₋regular=0;
     s₋ctxt->ongoing = accumulative₋zero();
     s₋ctxt->mode = mode₋initial;
   };
   
   collect append₋to₋fraction = ^(char32̄_t uc) {
    short idx = s₋ctxt->symbols₋in₋fract;
    if (idx >= 2049) Diagnos(2,s₋ctxt,1,"error: fractional too precise.");
    s₋ctxt->fract₋𝟶to𝟿s[idx] = uc;
    s₋ctxt->symbols₋in₋fract += 1; };
   
   collect append₋to₋regular = ^(char32̄_t uc) {
    short idx = s₋ctxt->symbols₋in₋regular;
    if (idx >= 2048) { Diagnos(2,s₋ctxt,1,"error: identifier too long."); }
    s₋ctxt->regular[idx] = uc;
    s₋ctxt->symbols₋in₋regular += 1; };
   
   query is₋regular₋last = ^{ return !letter₋alt₋digit(ucode₊₁); };
   query is₋fractional₋last = ^{ return !digit(ucode₊₁); };
   query is₋integer₋last = ^{ return !(digit(ucode₊₁) || period(ucode₊₁)); };
#define NEXT(s) s₋ctxt->mode = s
#define STATE(s) (s == s₋ctxt->mode)
   
   perform increment₋simplebook = ^{ s₋ctxt->lineno₋first+=1, s₋ctxt->lineno₋last+=1; };
   
   perform sample₋window = ^{
     detail₋out->lineno₋first=s₋ctxt->lineno₋first;
     detail₋out->lineno₋last=s₋ctxt->lineno₋last;
     detail₋out->column₋first=s₋ctxt->column₋first;
     detail₋out->column₋last=s₋ctxt->column₋last;
     s₋ctxt->integer₋alt₋fract₋regular₋passed = false;
   };
   
   🧵(identifier,number₋literal,lex₋error,completion) {
    case identifier: detail₋out->kind=1; 
     detail₋out->store.regular𝘖rIdent.symbols=s₋ctxt->symbols;
     detail₋out->store.regular𝘖rIdent.start=s₋ctxt->text₋heap;
     sample₋window();
     reset(); return IDENT/*IFIER*/;
    case number₋literal: detail₋out->kind=2; 
     /* s₋ctxt->ongoing is valid and s₋ctxt->fract₋0to9 is still. */
     int₋to₋sequent(0,&(detail₋out->store.literal));
     sample₋window();
     reset(); return NUMERIC₋CONST; /* ⬷ relative-to-letters big-endian. */
    case lex₋error: Diagnos(2,s₋ctxt,1,"error: scanner error."); return 0;
    case completion: return END₋OF₋TRANSMISSION;
   }
   
again:
   i=s₋ctxt->tip₋unicode; s₋ctxt->tip₋unicode += 1;
   if (i >= symbols && STATE(mode₋initial)) { confess(completion); }
   if (i == symbols - 1) { uc₋last=1; }
   ucode = s₋ctxt->text₋heap[i], ucode₊₁ = (uc₋last ? 0 : s₋ctxt->text₋heap[i+1]);
   if (STATE(mode₋initial)) { s₋ctxt->column₋first+=1; s₋ctxt->column₋last=s₋ctxt->column₋first; }
   if (!STATE(mode₋initial)) { s₋ctxt->column₋last+=1; }
   if (STATE(mode₋initial) && derender₋newline(ucode)) {
    increment₋simplebook(); if (s₋ctxt->integer₋alt₋fract₋regular₋passed) { 
     sample₋window(); return TERMINATING₋END₋OF₋LINE₋AND₋ASSIGN; } }
   else if (STATE(mode₋initial) && newline(ucode)) { /* do nothing */ }
   else if (STATE(mode₋initial) && whitespace(ucode)) { /* do nothing */ }
   else if (STATE(mode₋initial) && ucode == U'/' && ucode₊₁ == U'*')
    { NEXT(mode₋multiline₋comment); }
   else if (STATE(mode₋multiline₋comment) && ucode == U'*' && ucode₊₁ == U'/')
    { NEXT(mode₋initial); s₋ctxt->tip₋unicode += 1; }
   else if (STATE(mode₋multiline₋comment) /* && ucode != U'*' && ucode₊₁ != U'/' */)
    { if (derender₋newline(ucode)) { increment₋simplebook(); } }
   else if (STATE(mode₋initial) && ucode₊₁ == U'/' && ucode == U'/')
    { NEXT(mode₋singleline₋comment); }
   else if (STATE(mode₋singleline₋comment) && newline(ucode))
    {
    NEXT(mode₋initial);
    if (derender₋newline(ucode)) { increment₋simplebook(); }
    }
   else if (STATE(mode₋singleline₋comment)) { /* do nothing */ }
   else if (STATE(mode₋initial) && letter(ucode)) {
     append₋to₋regular(ucode);
     if (is₋regular₋last()) { confess(identifier); } else { NEXT(mode₋multiregular); }
   } else if (STATE(mode₋multiregular) && letter₋alt₋digit(ucode)) {
     append₋to₋regular(ucode);
     if (is₋regular₋last()) { confess(identifier); }
   }
   else if (STATE(mode₋initial) && ucode == U'=') { sample₋window(); return EQUALS_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'-') { sample₋window(); return MINUS_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'+') { sample₋window(); return PLUS_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'*') { sample₋window(); return MULT_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'(') { sample₋window(); return LPAREN_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U')') { sample₋window(); return RPAREN_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U';') { sample₋window(); return SEMICOLON; }
   else if (STATE(mode₋initial) && ucode₊₁ != U'/' && ucode₊₁ != U'*' && ucode == U'/')
    { sample₋window(); return DIV_KEYWORD; }
   else if (STATE(mode₋initial) && period(ucode)) { NEXT(mode₋fract); }
   else if (STATE(mode₋integer) && period(ucode) && is₋integer₋last()) { confess(number₋literal); }
   else if (STATE(mode₋integer) && period(ucode) && !is₋integer₋last()) { NEXT(mode₋fract); }
   else if (STATE(mode₋initial) && digit(ucode))
    {
    int₋to₋sequent(ucode - U'0',&s₋ctxt->ongoing);
    if (is₋integer₋last()) { confess(number₋literal); } else { NEXT(mode₋integer); }
    }
   else if (STATE(mode₋integer) && digit(ucode))
    {
    Sequenta ten=piano₋ten(),augment;
    s₋ctxt->ongoing=mult_sequent(ten,s₋ctxt->ongoing);
    int₋to₋sequent(ucode - U'0',&augment);
    s₋ctxt->ongoing=add_sequent(s₋ctxt->ongoing,augment);
    if (is₋integer₋last()) { confess(number₋literal); }
    }
   else if (STATE(mode₋fract) && digit(ucode) && is₋fractional₋last())
    {
    append₋to₋fraction(ucode);
    int count₋upto64 = s₋ctxt->symbols₋in₋fract; struct sequent lessthanone;
    rounded₋fraction(count₋upto64,s₋ctxt->fract₋𝟶to𝟿s,&lessthanone);
    s₋ctxt->ongoing=add_sequent(s₋ctxt->ongoing,lessthanone);
    confess(number₋literal);
    }
   else if (STATE(mode₋fract) && digit(ucode))
    {
    append₋to₋fraction(ucode);
    }
   else { confess(lex₋error); }
   goto again;
}

/*
 *  unicode parser.
 */

enum token lookahead, retrospect; /* alternatively back-pack. */
struct token₋detail current, gal₋out₊₁;
Stack 🥞; /* ...and backtrack (vol 5) alternatively argument-stack. */
/* ⬷ later struct token_fifo * tf for LL(k). */

static void match(enum token expected, lexer * context, 
 struct token₋detail * gal₋out, int first₋time)
{
   if (lookahead == expected) {
     /* print("equal tokens '⬚' matched", ﹟s(tokenname(expected))); */
     if (first₋time) { lookahead = next₋token(context,gal₋out);
     current = *gal₋out; } /* ⬷ first time */
     /* for LL(1) second time relates to */
     if (!first₋time) { current=gal₋out₊₁; lookahead = retrospect; }
     retrospect = next₋token(context,&gal₋out₊₁);
   } else { Diagnos(1,&current,0,"error: syntax expected ⬚, got ⬚.", 
    ﹟s(tokenname(expected)), 
    ﹟s(tokenname(lookahead))); }
}

static int optional₋sometime₋match(enum token expected, enum token conditional, 
 lexer * context, struct token₋detail * gal₋out)
{
  int selected = (lookahead == expected && retrospect == conditional);
  if (selected) { match(expected,context,gal₋out,0); }
  return selected;
}

static void parse₋assign(lexer * ctx);
static void parse₋expr(lexer * ctx);
static void parse₋term(lexer * ctx);
static void parse₋factor(lexer * ctx);
static void parse₋affidare(lexer * ctx);
static void parse₋circum(lexer * ctx);

void Ⓑ() { print("ASSIGN "); }
void Ⓒ(enum token op) { print("BIADD/BISUB "); 
  if (count(&🥞) < 2) { return; }
  uint8_t *young=pop(&🥞), *old=pop(&🥞);
  Sequenta r={ .detail.bits=*(__uint128_t *)old }, 
   l={ .detail.bits=*(__uint128_t *)young };
  Sequenta both = (op == PLUS_KEYWORD ? __builtin_fixpoint_add(l,r) : 
   __builtin_fixpoint_sub(l,r));
  uint32_t item=13; uint8_t * bitem = (uint8_t *)&item;
  if (push(&🥞,(uint8_t *)&both.detail.bits)) { return; }
}
void Ⓓ() { print("BIMULT/BIDIV "); }
void Ⓔ() { print("+/-/± "); }
void Ⓕ() { print("ASSOC "); }
void Ⓖ() { print("LITERAL "); }
void Ⓗ() { print("FUNCT "); }
void Ⓘ() { print("BIND-PARAM "); }

static void parse₋program(lexer * s₋ctxt)
{ struct token₋detail gal;
   if (optional₋sometime₋match(IDENT,EQUALS_KEYWORD,s₋ctxt,&gal)) { parse₋assign(s₋ctxt); }
   else { parse₋expr(s₋ctxt); }
}

static void parse₋assign(lexer * s₋ctxt)
{ struct token₋detail gal;
   match(IDENT,s₋ctxt,&gal,1);
   match(EQUALS_KEYWORD,s₋ctxt,&gal,0);
   parse₋expr(s₋ctxt);
   match(SEMICOLON,s₋ctxt,&gal,0); Ⓑ();
}

static void parse₋expr(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋term(s₋ctxt);
   while (lookahead == PLUS_KEYWORD || lookahead == MINUS_KEYWORD) {
     match(lookahead,s₋ctxt,&gal,0);
     parse₋term(s₋ctxt); Ⓒ(lookahead);
   }
}

static void parse₋term(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋factor(s₋ctxt);
   while (lookahead == MULT_KEYWORD || lookahead == DIV_KEYWORD) {
     match(lookahead,s₋ctxt,&gal,0);
     parse₋factor(s₋ctxt); Ⓓ();
   }
}

static void parse₋factor(lexer * s₋ctxt)
{ struct token₋detail gal;
   if (lookahead == MINUS_KEYWORD || lookahead == PLUS_KEYWORD) {
     while (lookahead == MINUS_KEYWORD || lookahead == PLUS_KEYWORD) {
       match(lookahead,s₋ctxt,&gal,0);
     }
   }
   parse₋affidare(s₋ctxt); Ⓔ();
}

static void parse₋affidare(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋circum(s₋ctxt);
   if (lookahead == CIRCUM_KEYWORD) {
     match(CIRCUM_KEYWORD,s₋ctxt,&gal,0);
     parse₋circum(s₋ctxt); Ⓕ();
   }
}

static void parse₋circum(lexer * s₋ctxt)
{ struct token₋detail gal;
   switch (lookahead) {
   case NUMERIC₋CONST: match(NUMERIC₋CONST,s₋ctxt,&gal,0); Ⓖ(); break;
   case LPAREN_KEYWORD: match(LPAREN_KEYWORD,s₋ctxt,&gal,0); 
    parse₋expr(s₋ctxt); match(RPAREN_KEYWORD,s₋ctxt,&gal,0); break;
   case IDENT: match(IDENT,s₋ctxt,&gal,0); 
    if (lookahead == LPAREN_KEYWORD) {
      match(LPAREN_KEYWORD,s₋ctxt,&gal,0);
      if (lookahead == RPAREN_KEYWORD) { Ⓗ(); }
      else { parse₋expr(s₋ctxt); Ⓘ(); }
      match(RPAREN_KEYWORD,s₋ctxt,&gal,0);
    }
    break;
   default: Diagnos(1,&current,0,"error: expecting IDENT, LPAREN and NUMERIC₋CONST, "
    "got ⬚.", ﹟s(tokenname(lookahead))); break;
   }
}

void print₋tokens(lexer * bag, struct token₋detail * gritty)
{
again:
   lookahead = next₋token(bag,gritty);
   char * text = tokenname(lookahead);
   print("⬚ ", ﹟s(text));
   if (lookahead == END₋OF₋TRANSMISSION) { print("\n\n"); return; }
   goto again;
}

void print₋unicodes(char32̄_t * text)
{ char32̄_t uc; __builtin_int_t i=0, ext₋count=0;
again:
   uc = *(i + text);
   if (uc == 0x0004) { print("(ext₋count=⬚)\n", ﹟d(ext₋count)); return; }
   print("U+");
   Base𝕟((__builtin_uint_t)uc,16,4,^(char 𝟶to𝟿) { print("⬚", ﹟c(𝟶to𝟿)); });
   if (uc & 0xffff0000) { ext₋count += 1; print("⌜"); } else { print(" "); }
   i += 1; goto again;
}

void debugbuild(lexer * ctx, struct token₋detail * notes)
{
   print₋unicodes(ctx->text₋heap);
   print("\n");
   print₋tokens(ctx,notes);
   ctx->tip₋unicode=0;
   ctx->lineno₋first=1; ctx->lineno₋last=1;
   ctx->column₋first=1; ctx->column₋last=1;
   ctx->symbols₋in₋regular=0; ctx->symbols₋in₋fract=0;
   ctx->ongoing=accumulative₋zero();
   ctx->mode=mode₋initial;
}

/*
 *  main function.
 */

int
main(
  int argc, 
  const char * argv[]
)
{
   lexer bag; const char * binary = argv[0];
   if (argc != 2) { print("usage: ⬚ file \n", ﹟s(binary)); }
   char8₋t * model = (char8₋t *)argv[1]; /* u8"./test.txt" */
   if (context₋init(model,&bag)) { print("incomprehensible ⬚\n", ﹟s(model)); return 1; }
   if (bag.symbols == 0) { return 2; }
   debugbuild(&bag,&current); short bytes₋per₋elem = 16;
   if (init₋stack(&🥞,bytes₋per₋elem)) { return 2; }
   lookahead = next₋token(&bag,&current);
   parse₋assign(&bag); lookahead = next₋token(&bag,&current);
   if (lookahead == END₋OF₋TRANSMISSION) print("parsing successful.\n");
   else print("parsing unsuccessful, found '⬚' token.\n", ﹟s(tokenname(lookahead)));
   /* stack₋unalloc(&🥞); */
   /* set₋parse(3, { "./express/comment.txt", "./express/optimal.txt", "./express/natural.txt" }); */
   context₋deinit(&bag);
   return 0;
}


