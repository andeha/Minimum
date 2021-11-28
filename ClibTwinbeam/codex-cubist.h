/*  yello-cubist.h | graphics and image memory. */

/* No left-recursion and somtimes backtracking alt. recursive-ascent:
  
  E․𝘨 .size 89.0  .offset -5.0, 12.0  .origo 50.0, 50.0 .columned 1
  
  program -> directive-list statement-list-nandalt-twolevel
  directive-list -> directive directive-list
  statement-list-alt-hierarchy -> statement statement-list
  statement-list alt. directive-list -> empty
  
  directive -> '.pixel-height' real 
  directive -> '.origo' real ',' real
  directive -> '.offset' real ',' real
  directive -> '.columned' natural
  
  real-literal -> '-'* digit+ '.' digit*
  
  statement -> 'start-line' real ',' real
  statement -> 'add-line' real ',' real
  statement -> 'last-line' real ',' real
  statement -> 'base16-image' [a-z]+                               and not base 21
  statement -> 'utf8-text' ␜ <text> ␜
  statement -> 'next'
  statement -> 'azimuth' azimuth-flavor real ',' real ',' real ',' real
  azimuth-flavor -> 'relative' | unit 'absolut' 
  statement -> identifier '<-' 'cyan' real ',' real ',' real ',' real 
   'mangenta' real ',' real ',' real ',' real 
   'yellow' real ',' real ',' real ',' real 
   'black' real ',' real ',' real ',' real color-unit real
  statement -> 'color-clog' identifier 'on' identifier 
  statement -> 'pressure' ⬷ with later relative alt. absolut ∓ADSR F
  color-unit -> 'relative' | 'absolute'
  statement -> 'ellipsoid' '(' real ',' real ')' 'and' '(' real ',' real ')'
  statement -> 'intention' 'inner' | 'middle' | 'outer'
  statement -> 'bleed' real unit
  
  unit -> 'mm'
  unit -> 'cm'
  unit -> 'in'
  unit -> 'pc'
  unit -> 'throu'
  
  two-level -> 'frame' statement-list 'closed' ⬷ a․𝘬․a 'draft'.
  
 */

union Artwork₋directive {
  int Count; /* ar: short. */
  double Scalar;
  /* struct */ A₋size Size;
  struct A₋point Point;
};

enum Artwork₋token₋symbol { dotsize, dotorigo, dotoffset, real, comma₋0x2c, 
 start₋line, add₋line, end₋line, base16₋image, base16₋text, 
 utf8₋text, rawtext₋sentinel, text, next, END₋OF₋TRANSMISSION };

union Artwork₋instruction₋detail {
  double * four₋parameters;                                        /*  (1) */
  Nonabsolute symbol;                                              /*  (2) */
  struct Unicodes identifier;                                      /*  (3) */
  union Artwork₋directive various₋signatures;                      /*  (4) */
};

typedef char8₋t uchar;
typedef void (*semantics)(int artwork₋instruction, 
 union Artwork₋instruction₋detail parameters, void * ctx);

enum Artwork₋scanner₋mode { initial, regular, 
 integer, period, fractional, 
 base16₋image₋text, raw₋unicode₋text, 
 div₋prefix₋comment, div₋suffix₋comment₋ie₋comment
};

struct Scanner₋ctxt {
  __builtin_int_t lineno₋first, lineno₋last;
  __builtin_int_t idx₋unicode; /* ⬷ and not idx₋u8s. */
  struct sequent ongoing;
  char32̄_t regular[1024]; short symbols₋in₋regular;
  enum Artwork₋scanner₋mode mode;
};

EXT₋C int Parse₋Artwork₋LL₍1₎(__builtin_int_t symbols, char32̄_t text[], 
 struct Scanner₋ctxt * s₋ctxt, semantics truly₋your);
EXT₋C int Parse₋Artwork₋LL₍k₎(__builtin_int_t symbols, char32̄_t text[], 
 struct Scanner₋ctxt * s₋ctxt, semantics truly₋your);

typedef enum Artwork₋instruction { columned=1, 
 pixel₋height, place₋origo, offset₋drawing₋on,          /* ⬷ directive. */
 dualbezier₋initial, dualbezier₋add, dualbezier₋last,   /* ⬷ instruction. */
 quadbezier₋initial, quadbezier₋add, quadbezier₋last, 
 beziercurve₋initial, beziercurve₋add, beziercurve₋last, 
 line₋initial, line₋add, line₋last, 
 bezier₋alt₋line₋close, 
 𝟸ᵈ₋intervallic, sample, link₋master₋detail, 
 base16₋encoded₋later₋layered₋png, place₋png, 
 color₋select, fill, 
 set₋letterbox₋anchor, set₋letterbox₋origo, 
 place₋text /* p3₋color₋select */
} Artwork₋instruction; /* ⬷ a․𝘬․a ¹directives and ¹instruction. */

/* Överhandsavtal och underhandsuppfattning: 
 
 ━━━   ━━━
  ┊ 􀲯  ┊   ⤐ t 
 ━━━   ━━━
 
 samtalar utan uppmärksamhet kvicknar. */


