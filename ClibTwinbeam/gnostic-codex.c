/*  gnostic-codex.c a․𝘬․a 'Jesuit' | and 'behind the urns'. */

import ClibTwinbeam;

int draw₋vector(int px, const char * utf8format, ...)
{
   int y; va_prologue(utf8format);
   typedef void (^Out)(char8₋t *, __builtin_int_t);
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, 
   	(const void *)u8s, bytes); };
   print("\xe2\bf\xaf"); /* \U2FEF */
   extern int print﹟(void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
    const char * utf8format, __builtin_va_list argument);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   print("\xe2\xbf\xab"); /* \U2FEB */
   return y;
}

/* and v-space 2cm */
/* draw(250, "vspace 250; draw (100.0, 100.0)--(150, 150)--(200, 200)--(174, 175)--cycle; " straight lines, ---
 "draw (100.0, 100.0)..(150, 150)..(200, 200)..(174, 175)..cycle"); curves, ... */

int markdown₋83(const char * utf8format, ...)
{
   int y; va_prologue(utf8format);
   typedef void (^Out)(char8₋t *, __builtin_int_t);
   Out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
   print("\xe2\xbf\xad"); /* \U2FED */
   extern int print﹟(void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
    const char * utf8format, __builtin_va_list argument);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   print("\xe2\xbf\xab"); /* \U2FEB */
   return y;
}

/* **bold**, _italic_, `monospace`, +underline+, ~~stricken~~, ---, # Heading-1, ## Heading-2,  */
/* :--, :--:, --: and one-alt-more blank lines to separate paragraphs. */
/* attr.addAttribute(.font, value: Rendition.textfont, range: NSRange(location: 0, length: 4)) */
/* .underlineStyle, .stringthroughStyle and NSUnderlineStyle; .paragraphStyle and NSMutableParagraphStyle. */
/* print("**this is not bold**"); markdown("**this is bold**"); */

int interact₋regional(unsigned retrospect₋rows, int (*decree)(int64_t param))
{
   /* rescriptum 1..N. */
   return 0;
} /* ⬷ a․𝘬․a for₋terminal₋line₋stepping. */