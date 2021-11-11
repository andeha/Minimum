/*  lingustics-epi.c | an epitomic recursive descent parser. */

import ClibTwinbeam;

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
  / * factor -> unary @ N(sigma,my), [max,min], [min,max], [mA] * /
  factor -> unary
  
  unary -> circum ^ circum
  / * unary -> circum 'basväljare' circum   ⬷ hilbertväljare * /
  unary -> circum
  
  circum -> real-literal
  circum -> integer-literal
  circum -> ( expr )
  circum -> funct ( expr )
  circum -> identifier
  
 *//*
  
  clang -o x86_epitom-7 -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"       \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap      \
    -g -std=c18 -lc++ lingustics-epit.c ../Releases/libClibTwinbeam.a
 
 */

/*
 *  unicode scanner.
 */

enum lexer₋mode { mode₋initial, mode₋regular };

struct lexer₋ctxt {
  __builtin_int_t symbols; char32_t * text₋heap;
  __builtin_int_t tip₋unicode;
  __builtin_int_t lineno₋first, lineno₋last;
  enum lexer₋mode mode; short symbols₋in₋regular;
  char32_t regular[2048];
};

inexorable int context₋init(const char * utf8txtpath, struct lexer₋ctxt * ctx)
{
   __builtin_int_t i=0,j=0, bytesActual, bytes;
   char8_t * leadOr8Bit; char32_t uc;
   uint8_t * utf8₋text = (uint8_t *)mapfileʳᵚ(utf8txtpath,0,0,0,&bytesActual);
   ctx->text₋heap = (char32_t *)Heap₋alloc(4*(bytesActual + 1));
again:
   if (i >= bytesActual) {
     ctx->symbols = j + 1; ctx->tip₋unicode = 0;
     *(ctx->text₋heap + ctx->symbols) = U'\x4';
     ctx->lineno₋first=1, ctx->lineno₋last=1;
     ctx->mode=mode₋initial;
     ctx->symbols₋in₋regular=0;
   }
   leadOr8Bit = i + utf8₋text;
   bytes = Utf8Followers(*leadOr8Bit) + 1;
   uc = Utf8ToUnicode(leadOr8Bit,bytes);
   i += bytes; j += 1;
   *(ctx->text₋heap + j) = uc;
   goto again;
}

enum token {
 VAR_KEYWORD, IDENT, EQUALS, NUMERIC₋CONST, SEMICOLON, END₋OF₋TRANSMISSION, 
 LTE_KEYWORD, GTE_KEYWORD, GT_KEYWORD, 
 PLUS_KEYWORD, MINUS_KEYWORD, MULT_KEYWORD, DIV_KEYWORD, CIRCUM_KEYWORD, 
 LPAREN_KEYWORD, RPAREN_KEYWORD
};

struct token₋detail {
  union {
    struct Regular𝘖rIdent { int symbols; char32_t * start; } regular𝘖rIdent;
    double literal;
  } storage₋detail;
  int kind;
};

enum token next₋token(struct lexer₋ctxt * s₋ctxt, 
  struct token₋detail * detail₋out)
{
   __builtin_int_t i,symbols=s₋ctxt->symbols;
   char32_t unicode, unicode₊₁;
   
   typedef int (^type)(char32_t unicode);
   typedef void (^collect)(char32_t);
   typedef void (^perform)(void);
   
   type digit = ^(char32_t c) { return U'0' <= c && c <= U'9'; };
   type derender₋newline = ^(char32_t c) { return c == U'\xa'; };
   type newline = ^(char32_t c) { return derender₋newline(c) || c == U'\xd'; };
   type whitespace = ^(char32_t c) { return c == U' ' || U'\t' == c || newline(c); };
   type letter = ^(char32_t c) { return (U'a' <= c && c <= U'z') || (U'A' <= c && c <= U'Z'); };
   type letter₋alt₋digit = ^(char32_t c) { return letter(c) || digit(c); };
   
   collect unicodes₋for₋regular = ^(char32_t uc) {
    short idx = s₋ctxt->symbols₋in₋regular;
    if (idx >= 2048) { print(""); exit(-2); }
    s₋ctxt->regular[idx] = uc;
    s₋ctxt->symbols₋in₋regular += 1; };
   
   perform reset = ^{
     s₋ctxt->symbols₋in₋regular=0;
     s₋ctxt->mode = mode₋initial;
   };
   
again:
   i=s₋ctxt->tip₋unicode;
   if (i >= symbols) { reset(); return END₋OF₋TRANSMISSION; }
   unicode = s₋ctxt->text₋heap[i], unicode₊₁ = s₋ctxt->text₋heap[i+1];
   if (derender₋newline(unicode)) { s₋ctxt->lineno₋first+=1, s₋ctxt->lineno₋last+=1; }
   else if (newline(unicode)) { }
   else if (whitespace(unicode)) { }
   else if (s₋ctxt->mode == mode₋initial && letter(unicode)) {
     unicodes₋for₋regular(unicode);
     s₋ctxt->mode = mode₋regular;
   }
   else if (s₋ctxt->mode == mode₋regular && letter₋alt₋digit(unicode)) {
     unicodes₋for₋regular(unicode);
   }
   else { print("scanner₋error"); exit(-1); }
   s₋ctxt->tip₋unicode += 1;
   goto again;
}

/*
 *  unicode parser.
 */

static enum token lookahead; /* ⬷ later struct token_fifo * tf for LL(k). */

static void match(enum token expected, struct lexer₋ctxt * s₋ctxt, 
 struct token₋detail * detail₋out)
{
   if (lookahead == expected) { lookahead = next₋token(s₋ctxt,detail₋out); }
   else { print("syntax error: expected ⬚, got ⬚\n", 
   ﹟d((__builtin_int_t)expected), 
   ﹟d((__builtin_int_t)lookahead)); }
}

static void parse₋assign(struct lexer₋ctxt * s₋ctxt);
static void parse₋expr(struct lexer₋ctxt * s₋ctxt);
static void parse₋term(struct lexer₋ctxt * s₋ctxt);
static void parse₋factor(struct lexer₋ctxt * s₋ctxt);
static void parse₋unary(struct lexer₋ctxt * s₋ctxt);
static void parse₋circum(struct lexer₋ctxt * s₋ctxt);

static void parse₋assign(struct lexer₋ctxt * s₋ctxt)
{ struct token₋detail detail;
   match(IDENT,s₋ctxt,&detail);
   match(EQUALS,s₋ctxt,&detail);
   parse₋expr(s₋ctxt);
   match(SEMICOLON,s₋ctxt,&detail);
}

static void parse₋expr(struct lexer₋ctxt * s₋ctxt)
{ struct token₋detail detail;
   parse₋term(s₋ctxt);
   while (lookahead == PLUS_KEYWORD || lookahead == MINUS_KEYWORD) {
     match(lookahead,s₋ctxt,&detail);
     parse₋term(s₋ctxt);
   }
}

static void parse₋term(struct lexer₋ctxt * s₋ctxt)
{ struct token₋detail detail;
   parse₋factor(s₋ctxt);
   while (lookahead == MULT_KEYWORD || lookahead == DIV_KEYWORD) {
     match(lookahead,s₋ctxt,&detail);
     parse₋factor(s₋ctxt);
   }
}

static void parse₋factor(struct lexer₋ctxt * s₋ctxt)
{ struct token₋detail detail;
   while (lookahead == PLUS_KEYWORD || lookahead == MINUS_KEYWORD) {
     match(lookahead,s₋ctxt,&detail);
     parse₋unary(s₋ctxt);
   }
}

static void parse₋unary(struct lexer₋ctxt * s₋ctxt)
{
   
}

static void parse₋circum(struct lexer₋ctxt * s₋ctxt)
{ struct token₋detail detail;
   switch (lookahead) {
   case IDENT: match(IDENT,s₋ctxt,&detail); break;
   case NUMERIC₋CONST: match(NUMERIC₋CONST,s₋ctxt,&detail); break;
   default: print("expecting IDENT alternatively NUMERIC₋CONST, got type-of-token."); break;
   }
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
   struct lexer₋ctxt s₋ctx; struct token₋detail detail;
   if (context₋init("/tmp/test.txt", &s₋ctx)) { return 1; }
   lookahead = next₋token(&s₋ctx,&detail); parse₋assign(&s₋ctx);
   if (lookahead == END₋OF₋TRANSMISSION) print("parsing successful\n");
   else print("parsing unsuccessful\n");
   return 0;
}


