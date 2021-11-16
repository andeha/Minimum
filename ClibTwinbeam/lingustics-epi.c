/*  􀥳 lingustics-epi.c | an epitomic recursive descent parser. */

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
  
 */

/*
 *  unicode scanner.
 */

enum lexer₋mode { mode₋initial, mode₋regular };

struct lexer₋ctxt {
  __builtin_int_t symbols; char32_t * text₋heap;
  __builtin_int_t tip₋unicode;
  __builtin_int_t lineno₋first, lineno₋last;
  __builtin_int_t column₋first, column₋last;
  enum lexer₋mode mode; short symbols₋in₋regular;
  char32_t regular[2048];
  char8_t * src₋path;
};

char8_t * utf8dup(char8_t * u8s)
{ __builtin_int_t maxutf8bytes = BUILTIN₋INT₋MAX, 
    bytes = Utf8BytesUntilNull(u8s,maxutf8bytes);
   void * start = Heap₋alloc(bytes);
   Copy8Memory((ByteAlignedRef)start, (ByteAlignedRef)u8s, bytes);
   return start;
} /* ⬷ a․𝘬․a strdup₋for₋utf8. */

inexorable int context₋init(char8_t * utf8txtpath, struct lexer₋ctxt * ctx)
{
   __builtin_int_t i=0,j=0, bytesActual, bytes;
   char8_t * leadOr8Bit; char32_t uc;
   uint8_t * utf8₋text = (uint8_t *)mapfileʳᵚ((const char *)utf8txtpath,0,0,0,&bytesActual);
   if (utf8₋text == ΨΛΩ) { return -1; }
   ctx->text₋heap = (char32_t *)Heap₋alloc(4*(bytesActual + 1));
   if (ctx->text₋heap == ΨΛΩ) { return -2; }
   ctx->tip₋unicode=0;
   ctx->lineno₋first=1; ctx->lineno₋last=1;
   ctx->column₋first=1; ctx->column₋last=1;
   ctx->mode=mode₋initial;
   ctx->symbols₋in₋regular=0;
   ctx->src₋path=utf8dup(utf8txtpath);
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

/* rt₋namespace Diag₊nosis { extern */
int inited=0, tapeinit₋failed=0, acquire₋failed=0, lengthen₋failed=0, 
 conversion₂₋failed=0, print₋failed=0, conversion₁₋failed=0, 
 diagnosis₋count=0, append₋failed=0;
/* } */

__builtin_int_t symbolcount(struct Unicodes text, short unicodes, 
 char32_t * symbol) { short similar=unicodes-1;
  __builtin_int_t found₋count=0, count=text.tetras;
  for (__builtin_int_t i=count-1; i>=0; --i) {
    if (symbol[similar] == text.start[i]) {
      if (similar==0) { ++found₋count; similar=unicodes-1; }
      else { --similar; }
    } else { similar=unicodes-1; }
  }
  return found₋count;
} /* ⬷ transpressions when in art-context, not 'impression'. */

EXT₋C long write(int fd, const void * s, long unsigned nbyte);
EXT₋C int print﹟(void (^out)(char8_t * u8s, __builtin_int_t bytes), 
 const char * utf8format, __builtin_va_list argument);

void Diagnosis(struct lexer₋ctxt * s₋ctxt, int bye, char32_t * text, ... )
{
  __builtin_int_t lineno₋first = s₋ctxt->lineno₋first, 
   column₋first = s₋ctxt->column₋first, 
   linecount = 1 + s₋ctxt->lineno₋last - lineno₋first;
  char8_t * src₋path = s₋ctxt->src₋path;
  typedef void (^Out)(char8_t * u8s, __builtin_int_t bytes);
  Out out = ^(char8_t * u8s, __builtin_int_t bytes) { write(1,(const void *)u8s,bytes); };
  print(out,"⬚:⬚:⬚ ", ﹟s(src₋path), ﹟d(lineno₋first), ﹟d(column₋first));
  va_prologue(text);
  print﹟(out,"⬚", __various); /* __builtin_va_list argument; */
  print(out," (⬚ lines)\n", ﹟d(linecount));
  va_epilogue;
  if (bye) { exit(-2); } else { Pult💡(diagnosis₋count); }
} /*  ⬷ write 'error:', 'warning:' and 'internal-error:' prefixed texts. */

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
    if (idx >= 2048) { Diagnosis(s₋ctxt,1,U"error: identifier too long."); }
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
   else if (newline(unicode)) { /* do nothing */ }
   else if (whitespace(unicode)) { /* do nothing */ }
   else if (s₋ctxt->mode == mode₋initial && letter(unicode)) {
     unicodes₋for₋regular(unicode);
     s₋ctxt->mode = mode₋regular;
   }
   else if (s₋ctxt->mode == mode₋regular && letter₋alt₋digit(unicode)) {
     unicodes₋for₋regular(unicode);
   }
   else { Diagnosis(s₋ctxt,1,U"error: scanner error."); }
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
   else { Diagnosis(s₋ctxt,0,U"error: syntax expected ⬚, got ⬚.\n", 
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
   default: Diagnosis(s₋ctxt,0,U"expecting IDENT alternatively NUMERIC₋CONST, "
    "got type-of-token."); break;
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
   if (context₋init((char8_t *)u8"/tmp/test.txt", &s₋ctx)) { return 1; }
   lookahead = next₋token(&s₋ctx,&detail); parse₋assign(&s₋ctx);
   if (lookahead == END₋OF₋TRANSMISSION) print("parsing successful.\n");
   else print("parsing unsuccessful\n");
   return 0;
}


