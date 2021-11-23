/*  􀥳 lingustics-epi.c | an epitomic recursive descent parser. */

import ClibTwinbeam;
import Setjmp;

/*
  
  assign -> Ident '=' expr ';'
  
  expr -> term + term
  expr -> term - term
  expr -> term
  
  term -> factor * factor
  term -> factor / factor
  term -> factor
  
  factor -> - unary
  factor -> + unary
  factor -> unary
  
  unary -> circum ^ circum
  unary -> circum
  
  circum -> real-literal
  circum -> integer-literal
  circum -> ( expr )
  circum -> funct ( expr )
  circum -> identifier
  
 */

/* factor -> unary @ N(sigma,my), [max,min], [min,max], [mA] */
/* unary -> circum 'basväljare' circum   ⬷ hilbertväljare */

/*
  
  clang -o x86_epitom-7 -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"       \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap      \
    -g -std=c18 -lc++ lingustics-epi.c ../Releases/libClibTwinbeam.a
  
  ./x86_epitom-7 /tmp/test.txt
  
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
  char32̄_t regular[2048]; Sequent ongoing; short fract₋𝟶to𝟿s[2049];
  char8₋t * src₋path;
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

enum token { END₋OF₋TRANSMISSION=1, 
 VAR_KEYWORD, IDENT, EQUALS_KEYWORD, NUMERIC₋CONST, SEMICOLON, 
 LTE_KEYWORD, GTE_KEYWORD, GT_KEYWORD, LT_KEYWORD, 
 PLUS_KEYWORD, MINUS_KEYWORD, MULT_KEYWORD, DIV_KEYWORD, CIRCUM_KEYWORD, 
 LPAREN_KEYWORD, RPAREN_KEYWORD
};

struct token₋detail {
  union {
    struct Regular𝘖rIdent { int symbols; char32̄_t * start; } regular𝘖rIdent;
    double literal;
  } store;
  int kind;
};

char * tokenname(enum token gritty)
{
  switch (gritty) {
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

void Diagnos(lexer * s₋ctxt, int bye, char * text, ...)
{ va_prologue(text);
  __builtin_int_t lineno₋first = s₋ctxt->lineno₋first, 
   column₋first = s₋ctxt->column₋first, 
   linecount = 1 + s₋ctxt->lineno₋last - lineno₋first;
  char8₋t * src₋path = s₋ctxt->src₋path;
  typedef void (^Utf8)(char8₋t * u8s, __builtin_int_t bytes);
  Utf8 out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1,(const void *)u8s,bytes); };
  print(out,"⬚:⬚:⬚ ", ﹟s(src₋path), ﹟d(lineno₋first), ﹟d(column₋first));
  print﹟(out, text, __various);
  print(out, " (⬚ lines)\n", ﹟d(linecount));
  va_epilogue;
  if (bye) { exit(1); } else { Pult💡(diagnosis₋count); }
} /*  ⬷ write texts prefixed with 'error:', 'warning:' and 'internal-error:'. */

enum token next₋token(lexer * s₋ctxt, 
  struct token₋detail * detail₋out)
{
   __builtin_int_t i,symbols=s₋ctxt->symbols;
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 char32̄_t ucode, ucode₊₁; int uc₋last=0;
   
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
    if (idx >= 2049) Diagnos(s₋ctxt,1,"error: fractional too precise.");
    s₋ctxt->fract₋𝟶to𝟿s[idx] = uc;
    s₋ctxt->symbols₋in₋fract += 1; };
   
   collect append₋to₋regular = ^(char32̄_t uc) {
    short idx = s₋ctxt->symbols₋in₋regular;
    if (idx >= 2048) { Diagnos(s₋ctxt,1,"error: identifier too long."); }
    s₋ctxt->regular[idx] = uc;
    s₋ctxt->symbols₋in₋regular += 1; };
   
   query is₋regular₋last = ^{ return !letter₋alt₋digit(ucode₊₁); };
   query is₋fractional₋last = ^{ return !digit(ucode₊₁); };
   query is₋integer₋last = ^{ return !(digit(ucode₊₁) || period(ucode₊₁)); };
#define NEXT(s) s₋ctxt->mode = s
#define STATE(s) (s == s₋ctxt->mode)
   
   perform increment₋simplebook = ^{ s₋ctxt->lineno₋first+=1, s₋ctxt->lineno₋last+=1; };
   
   🧵(identifier,number₋literal,lex₋error,completion) {
    case identifier: detail₋out->kind=1; 
     detail₋out->store.regular𝘖rIdent.symbols=s₋ctxt->symbols;
     detail₋out->store.regular𝘖rIdent.start=s₋ctxt->text₋heap;
     reset(); return IDENT/*IFIER*/;
    case number₋literal: detail₋out->kind=2; 
     /* s₋ctxt->ongoing is valid and s₋ctxt->fract₋0to9 is still. */
     detail₋out->store.literal=0.0;
     reset(); return NUMERIC₋CONST; /* ⬷ relative-to-letters big-endian. */
    case lex₋error: Diagnos(s₋ctxt,1,"error: scanner error."); return 0;
    case completion: return END₋OF₋TRANSMISSION;
   }
   
again:
   i=s₋ctxt->tip₋unicode; s₋ctxt->tip₋unicode += 1;
   if (i >= symbols) { confess(completion); }
   if (i == symbols - 1) { uc₋last=1; }
   ucode = s₋ctxt->text₋heap[i], ucode₊₁ = (uc₋last ? 0 : s₋ctxt->text₋heap[i+1]);
   /* if (STATE(mode₋initial)) { s₋ctxt->column₋first+=1; }
   if (STATE(mode-initial)) { s₋ctxt->column₋last+=1; } */
   if (STATE(mode₋initial) && derender₋newline(ucode)) { increment₋simplebook(); }
   else if (STATE(mode₋initial) && newline(ucode)) { /* do nothing */ }
   else if (STATE(mode₋initial) && whitespace(ucode)) { /* do nothing */ }
   else if (STATE(mode₋initial) && letter(ucode)) {
     append₋to₋regular(ucode);
     if (is₋regular₋last()) { confess(identifier); } else { NEXT(mode₋multiregular); }
   } else if (STATE(mode₋multiregular) && letter₋alt₋digit(ucode)) {
     append₋to₋regular(ucode);
     if (is₋regular₋last()) { confess(identifier); }
   }
   else if (STATE(mode₋initial) && ucode == U'=') { return EQUALS_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'-') { return MINUS_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'+') { return PLUS_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'*') { return MULT_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U';') { return SEMICOLON; }
   else if (STATE(mode₋initial) && ucode₊₁ != U'/' && ucode₊₁ != U'*' && ucode == U'/')
    { return DIV_KEYWORD; }
   else if (STATE(mode₋initial) && ucode == U'/' && ucode₊₁ == U'*')
    { NEXT(mode₋multiline₋comment); }
   else if (STATE(mode₋multiline₋comment) && ucode == U'*' && ucode₊₁ == U'/')
    { NEXT(mode₋initial); }
   else if (STATE(mode₋multiline₋comment) /* && ucode != U'*' && ucode₊₁ != U'/' */)
    { if (derender₋newline(ucode)) { increment₋simplebook(); } }
   else if (STATE(mode₋initial) && ucode₊₁ == U'/' && ucode == U'/' )
    { NEXT(mode₋singleline₋comment); }
   else if (STATE(mode₋singleline₋comment) && newline(ucode))
    { NEXT(mode₋initial); if (derender₋newline(ucode)) { increment₋simplebook(); } }
   else if (STATE(mode₋singleline₋comment)) { /* do nothing */ }
   else if (STATE(mode₋initial) && period(ucode)) { NEXT(mode₋fract); }
   else if (STATE(mode₋integer) && period(ucode) && is₋integer₋last()) { confess(number₋literal); }
   else if (STATE(mode₋initial) && digit(ucode))
    {
    int₋to₋sequent(ucode - U'0',&s₋ctxt->ongoing);
    if (is₋integer₋last()) { confess(number₋literal); } else { NEXT(mode₋integer); }
    }
   else if (STATE(mode₋integer) && digit(ucode))
    {
    Sequent ten=piano₋ten(),augment;
    s₋ctxt->ongoing=mult_sequent(ten,s₋ctxt->ongoing);
    int₋to₋sequent(ucode - U'0',&augment);
    s₋ctxt->ongoing=add_sequent(s₋ctxt->ongoing,augment);
    if (is₋integer₋last()) { confess(number₋literal); }
    }
   else if (STATE(mode₋fract) && digit(ucode) && is₋fractional₋last())
    {
    append₋to₋fraction(ucode);
    int count₋upto64 = s₋ctxt->symbols₋in₋fract; Sequent lessthanone;
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

static enum token lookahead; /* ⬷ later struct token_fifo * tf for LL(k). */

static void match(enum token expected, lexer * log, 
 struct token₋detail * detail₋out)
{
   if (lookahead == expected) { lookahead = next₋token(log,detail₋out); }
   else { Diagnos(log,0,"error: syntax expected ⬚, got ⬚.\n", 
   ﹟d((__builtin_int_t)expected), 
   ﹟d((__builtin_int_t)lookahead)); }
// if debugbuild() {
   char * text = tokenname(lookahead);
   print("token ⬚ ", ﹟s(text));
// }
}

static void parse₋assign(lexer * s₋ctxt);
static void parse₋expr(lexer * s₋ctxt);
static void parse₋term(lexer * s₋ctxt);
static void parse₋factor(lexer * s₋ctxt);
static void parse₋unary(lexer * s₋ctxt);
static void parse₋circum(lexer * s₋ctxt);

static void parse₋assign(lexer * s₋ctxt)
{ struct token₋detail gal;
   match(IDENT,s₋ctxt,&gal);
   match(EQUALS_KEYWORD,s₋ctxt,&gal);
   parse₋expr(s₋ctxt);
   match(SEMICOLON,s₋ctxt,&gal);
}

static void parse₋expr(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋term(s₋ctxt);
   while (lookahead == PLUS_KEYWORD || lookahead == MINUS_KEYWORD) {
     match(lookahead,s₋ctxt,&gal);
     parse₋term(s₋ctxt);
   }
}

static void parse₋term(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋factor(s₋ctxt);
   while (lookahead == MULT_KEYWORD || lookahead == DIV_KEYWORD) {
     match(lookahead,s₋ctxt,&gal);
     parse₋factor(s₋ctxt);
   }
}

static void parse₋factor(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋unary(s₋ctxt);
   while (lookahead == PLUS_KEYWORD || lookahead == MINUS_KEYWORD) {
     match(lookahead,s₋ctxt,&gal);
     parse₋unary(s₋ctxt);
   }
}

static void parse₋unary(lexer * s₋ctxt)
{ struct token₋detail gal;
   parse₋circum(s₋ctxt);
   if (lookahead == CIRCUM_KEYWORD) {
     match(CIRCUM_KEYWORD,s₋ctxt,&gal);
     parse₋circum(s₋ctxt);
   }
}

static void parse₋circum(lexer * s₋ctxt)
{ struct token₋detail gal;
   switch (lookahead) {
   case IDENT: match(IDENT,s₋ctxt,&gal); break;
   case NUMERIC₋CONST: match(NUMERIC₋CONST,s₋ctxt,&gal); break;
   default: Diagnos(s₋ctxt,0,"expecting IDENT alternatively NUMERIC₋CONST, "
    "got type-of-token."); break;
   }
}

void print₋tokens(lexer * bag, struct token₋detail * gritty)
{
again:
   lookahead = next₋token(bag,gritty);
   char * text = tokenname(lookahead);
   print("⬚ ", ﹟s(text));
   if (lookahead == END₋OF₋TRANSMISSION) { exit(3); }
   goto again;
}

void print₋unicodes(char32̄_t * text)
{ char32̄_t uc; __builtin_int_t i=0;
again:
   uc = *(i + text);
   if (uc == 0x0004) { return; }
   print("U+");
   Base𝕟((__builtin_uint_t)uc,16,4,^(char 𝟶to𝟿) { print("⬚", ﹟c(𝟶to𝟿)); });
   print(" ");
   i += 1; goto again;
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
   lexer bag; struct token₋detail notes;
   if (argc != 2) { print("usage: ⬚ file \n", ﹟s(argv[0])); }
   char8₋t * model = (char8₋t *)argv[1]; /* u8"./test.txt" */
   if (context₋init(model,&bag)) { print("incomprehensible ⬚\n", ﹟s(argv[1])); return 1; }
   if (bag.symbols == 0) { return 2; }
   print₋unicodes(bag.text₋heap); print("\n");
   print₋tokens(&bag,&notes); /* debugbuild */
   lookahead = next₋token(&bag,&notes); parse₋assign(&bag);
   if (lookahead == END₋OF₋TRANSMISSION) print("parsing successful.\n");
   else print("parsing unsuccessful\n");
   return 0;
}


