/* 􀶷 main.cpp | test harness for ClibTwinbeam units written in C and C++. */

import ClibTwinbeam;
import Stdlib;

/* clang -o x86_confidence -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"     \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap       \
    -g -std=c++20 -lc++ decalogue.cpp eight-utf.cpp endian-base.cpp            \
     entry-main.cpp present-print.cpp                                          \
    unittests/ᛟ-test-utf8.cpp unittests/ᛟ-test-half.cpp                        \
    account-italian.o amend-augment.o arabic-edit.o avant-garde.o              \
    chronolog-y.o float-short.o kiddle-table.o lock-arrange.o o-binary.o       \
    queue-invent.o round-fixed.o search-symbol.o semantic-symbol.o             \
    thread-fork.o tiles-map.o x-error-stack.o x-partial-referen.o */

/* clang -c -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"                    \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap       \
    -g -std=c18 account-italian.c amend-augment.c arabic-edit.c avant-garde.c  \
    chronolog-y.c float-short.c kiddle-table.c lock-arrange.c o-binary.c       \
    queue-invent.c round-fixed.c search-symbol.c semantic-symbol.c             \
    thread-fork.c tiles-map.c x-error-stack.c x-partial-referen.c */

/* $(CC) main.c -o arm_app -target arm64-apple-macos11
   $(CC) main.c -o x86_app -target x86_64-apple-macos10.12
   lipo -create -output confidence x86_confidence arm_confidence
   lipo -archs confidence */

/* clang -o arm_confidence -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\" -D__armv8a__ \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap       \
    -g -std=c++20 -lc++ -target arm64-apple-macos11 -march=armv8.4a+tme+fp16   \
    decalogue.cpp eight-utf.cpp endian-base.cpp entry-main.cpp                 \
    present-print.cpp unittests/ᛟ-test-utf8.cpp unittests/ᛟ-test-half.cpp      \
    account-italian.o amend-augment.o arabic-edit.o avant-garde.o              \
    float-short.o kiddle-table.o lock-arrange.o o-binary.o queue-invent.o      \
    round-fixed.o search-symbol.o semantic-symbol.o thread-fork.o tiles-map.o  \
    x-error-stack.o x-partial-referen.o */

/* clang -c -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\" -D__armv8a__       \
    -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap       \
    -g -std=c18 -target arm64-apple-macos11 -march=armv8.4a+crypto+tme+fp16    \
    account-italian.c amend-augment.c arabic-edit.c avant-garde.c              \
    chronolog-y.c float-short.c kiddle-table.c lock-arrange.c o-binary.c       \
    queue-invent.c round-fixed.c search-symbol.c semantic-symbol.c             \
    thread-fork.c tiles-map.c x-error-stack.c x-partial-referen.c */

#define BUILDINFO_COPYRIGHT_MESSAGE "Copyright " PROGRESS_START_YEAR "—"       \
  PROGRESS_BUILD_YEAR " " BUILDINFO_BRAND
#define BUILDINFO_BRAND "⚖️  sublimates experimentally"
#define PROGRESS_START_YEAR QUOTE(2021)
#define PROGRESS_BUILD_YEAR QUOTE(2021)

inexorable void printGreetings()
{
   print("▞ twinbeam exercised...please stand-by. ▚\n"); 
   print("test harness for clibTwinbeam.a, release "
     "⬚\n⬚\n\n", ﹟s(SHA1GIT), ﹟s(BUILDINFO_COPYRIGHT_MESSAGE));
   /* ⬷ Epson MX-80 166 and 169. */
}

inexorable
void
runUnitTest(
  void *addr,
  const char *symbol,
  void (^completion)(const char *symbol, uint64_t dt)
)
{
    typedef void (*Testcase)(); void (*testcase)() = (Testcase)addr;
    uint64_t startInstant = cycles(); testcase();
    uint64_t dt = cycles() - startInstant;
    completion(symbol,dt);
}

inexorable void lastChance()
{
#if defined(_DEBUG)
    print("\nThe binary is a debug build.\n\n");
#else
    print("\nThe binary is a release build.\n\n");
#endif
}

#pragma mark glue and boilerplate

__builtin_int_t
RunUnittests(
  const char * execfilePath,
  const char32_t * regex,
  const char32_t * blacklist,
  bool doNotRun,
  int64_t * timetotal
)
{
    __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 count = 0;
    extern void Symbols(const char * utf8exepath, void (^callback)(const
      char *, uint64_t, int *));
    Symbols(execfilePath, ^(const char * sym, uint64_t addr, int * stop) {
       if (addr && IsPrefixOrEqual((char *)sym, (char *)"_Unittest_")) {
          print("\nRunning ⬚ from 0x⬚\n\n", ﹟s(sym), ﹟x((__builtin_uint_t)addr));
          runUnitTest((void *)addr, sym, ^(const char * symbol, uint64_t dt) {
             print("\n\nEND ");
             Base𝕟(dt, 10, 0,^(char 𝟶to𝟿) { print("⬚", ﹟c(𝟶to𝟿)); });
             print(" ns when running ⬚\n", ﹟s(symbol));
             *timetotal += dt;
          });
          ++count;
       }
    });
    
    return count;
}

int
main(
  int argc,
  const char * argv[]
)
{
    printGreetings();
    int64_t nanosecs = 0;
    __builtin_int_t units = RunUnittests(argv[0], U"", U"", false, &nanosecs);
    atexit(lastChance);
    print("\nUnit(s): ⬚\nTotal: ⬚ ns\n\n", ﹟d(units), ﹟d(nanosecs));
    print("𝐴𝑢𝑡𝑜𝑚𝑎𝑡𝑒𝑑 𝑡𝑒𝑠𝑡𝑠 𝑑𝑖𝑑 𝑛𝑜𝑡 𝑓𝑖𝑛𝑑 𝑎𝑛𝑦 𝑒𝑟𝑟𝑜𝑟𝑠 😐 \n");
    return 0;
}


