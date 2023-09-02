# Minimum

After extensive terminal use the `Minimum` application: finally a terminal with support for text and multiple-column renditions with images, vector-art and playable simulations. 

With `Minimum` also known as 'toblerone', implementations written in C and C++ may utilize the full power of your computer.

To compile multiple platforms with just one `.ninja` build file — as illustrated in `X.sh` — you must recompile `ninja` with a small change to your `lexer.in.cc` file:

```
"$"simple_varname {
  ...
}
[a-zA-Z0-9_.-]*[=]?"{$"varname"}"[a-zA-Z0-9_.-]* {
  int count=p-start; char *key,*text;
  const char * onevar = strstr(start,"{$");
  const char * flag = strstr(start,"}");
  if (onevar != start) { eval->AddText(StringPiece(start,onevar-start)); }
  if (onevar && flag) {
    key = strndup(onevar+2,flag-onevar-2);
    text = getenv(key);
    if (text == 0) { text = ""; }
    /* printf("found environment key '%s' = '%s'\n",key,text); */
    int len = strlen(text);
    eval->AddText(StringPiece(text,len));
    free(key);
  }
  if (flag && flag-start!=count) { eval->AddText(StringPiece(flag+1,count-(flag-start)-1)); }
  continue;
}


