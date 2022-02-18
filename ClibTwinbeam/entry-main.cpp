/* 􀶷 main.cpp | designed for outright performance. */

import ClibTwinbeam;

/* clang -o x86_confidence -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"     \
  -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap         \
  -g -std=c++20 -msse4.1 -lc++ -target x86_64-apple-darwin21.3.0               \
  -Wno-nullability-completeness entry-main.cpp unittests/ᛟ-test-utf8.cpp       \
   unittests/ᛟ-test-half.cpp unittests/ᛟ-test-chrono.cpp                       \
   unittests/ᛟ-test-keying.cpp unittests/ᛟ-test-timeserie.cpp                  \
   account-italian-1.o account-italian-2.o amend-tape.o arabic-edit.o          \
   built-altern.o chrono-logy.o cipher-rhode.o eight-utf.o endian-base.o       \
   float-short.o gnostic-codex.o lock-attempt.o o-binary.o present-print.o     \
   queue-invent.o regular-pool.o round-fixed.o search-symbol.o                 \
   semantic-block.o code-text.o symbol-texts.o thread-fork.o tiles-map.o       \
   x-error-stack.o x-partial-referen.o assoc-symbol.o
  
   clang -c -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"                    \
  -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap         \
  -g -std=c2x -target x86_64-apple-darwin21.3.0 -msse4.1                       \
  -Wno-nullability-completeness account-italian-1.c account-italian-2.c        \
   amend-tape.c arabic-edit.c built-altern.c chrono-logy.c cipher-rhode.c      \
   eight-utf.c endian-base.c float-short.c gnostic-codex.c lock-attempt.c      \
   o-binary.c present-print.c queue-invent.c regular-pool.c round-fixed.c      \
   search-symbol.c semantic-block.c code-text.c symbol-texts.c                 \
   thread-fork.c tiles-map.c x-error-stack.c x-partial-referen.c assoc-symbol.c
  
   $(CC) main-entry.c -o arm-mac_app -target arm64-apple-macos11
   $(CC) main-entry.c -o x86-mac_app -target x86_64-apple-macos10.12
   $(CC) main-entry.c -0 ios-arm_app -target arm64-apple-ios9.0
   lipo -create -output confidence x86_confidence arm_confidence
   lipo -archs confidence
  
   clang -o arm_confidence -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\"     \
  -D__armv8a__ -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap \
  -g -std=c++20 -lc++ -target arm64-apple-macos11 -Wno-nullability-completeness \
   entry-main.cpp unittests/ᛟ-test-utf8.cpp unittests/ᛟ-test-half.cpp         \
   unittests/ᛟ-test-chrono.cpp unittests/ᛟ-test-keying.cpp                    \
   unittests/ᛟ-test-timeserie.cpp account-italian-1.o account-italian-2.o     \
   amend-tape.o arabic-edit.o built-altern.o chrono-logy.o cipher-rhode.o     \
   eight-utf.o endian-base.o float-short.o gnostic-codex.o lock-attempt.o     \
   o-binary.o present-print.o queue-invent.o regular-pool.o round-fixed.o     \
   search-symbol.o semantic-block.o code-text.o symbol-texts.o                \
   thread-fork.o tiles-map.o x-error-stack.o x-partial-referen.o assoc-symbol.o
  
   clang -c -DSHA1GIT=\"`git log -1 '--pretty=format:%h'`\" -D__armv8a__      \
  -fmodules-ts -fimplicit-modules -fmodule-map-file=./module.modulemap        \
  -g -std=c2x -target arm64-apple-macos11 -Wno-nullability-completeness       \
   account-italian-1.c account-italian-2.c amend-tape.c arabic-edit.c         \
   built-altern.c chrono-logy.c cipher-rhode.c eight-utf.c endian-base.c      \
   float-short.c gnostic-codex.c lock-attempt.c o-binary.c present-print.c    \
   queue-invent.c regular-pool.c round-fixed.c search-symbol.c                \
   semantic-block.c code-text.c symbol-texts.c thread-fork.c tiles-map.c      \
   x-error-stack.c x-partial-referen.c assoc-symbol.c
  
   On 'target' and 'march' details, see the llvm files:
  
  --<clang>--<lib>--<Driver>--<ToolChains>--<Arch>--<AArch64.cpp>
  --<clang>--<test>--<Driver>--<aarch64-cpus.c>
  --<clang>--<test>--<Preprocessor>--<aarch-target-features.c>
  --<llvm>--<include>--<llvm>--<Support>--<AArch64TargetParser.def>
  --<llvm>--<lib>--<Target>--<AArch64>--<AArch64Subtarget.cpp|h>
  
 An update (15'th nov 2019) 'mcpu' may be set to 'apple-a13' and 'apple-s5' 
 alternatively '-target aarch64 -mcpu=+v8.4a+fp-armv8+neon+crc+crypto
 +dotprod+fullfp16+ras+lse+rdm+rcpc+zcm+zcz+fp16fml+sm4+sha3+sha2+aes' 
 alternatively '-target arm64-apple-macos11 -march=armv8-a+fp+simd+crypto+crc'. For 
 further investigations run 'clang --version' and 'clang -print-targets' and 
 'clang -march=dont-know eight-utf.c'.
  
 */

#define BUILDINFO_COPYRIGHT_MESSAGE "Copyright " PROGRESS_START_YEAR "—"      \
  PROGRESS_BUILD_YEAR " " BUILDINFO_BRAND
#define BUILDINFO_BRAND "⚖️  sublimates experimentally"
#define PROGRESS_START_YEAR QUOTE(2021)
#define PROGRESS_BUILD_YEAR QUOTE(2021)

inexorable void printGreetings()
{
   print("▞ twinbeam exercised...please stand-by. ▚\n");
   print("test harness for clibTwinbeam.a, release "
    "⬚\n⬚\n\n", ﹟s7(SHA1GIT), ﹟s7(BUILDINFO_COPYRIGHT_MESSAGE));
} /* ⬷ Epson MX-80 codes 166 and 169. */

inexorable
void
runUnitTest(
  void *addr,
  const char *symbol,
  void (^completion)(const char *symbol, uint64_t dt)
)
{
   typedef void (*Testcase)(); void (*testcase)() = (Testcase)addr;
   /* mprotect((void*)base, size, PROT_READ | PROT_EXEC); */
   uint64_t startInstant = cycles(); testcase();
   uint64_t dt = cycles() - startInstant;
   completion(symbol,dt);
}

inexorable void lastChance(int debug)
{
  if (debug) print("\nThe binary is a debug build.\n\n");
  else print("\nThe binary is a release build.\n\n");
}

#pragma mark glue and boilerplate

__builtin_int_t
RunUnittests(
  const char * execfilePath,
  const char32_t * regex,
  const char32_t * blacklist,
  bool doNotRun,
  /* int * is₋debug, */
  int64_t * timetotal
)
{
   __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 count = 0;
   extern void Symbols(const char * utf8exepath /*, int * is₋debug */, 
    void (^callback)(const char *, uint64_t, int *)); /* defined in --<o-binary.c>. */
   Symbols(execfilePath, /* is₋debug, */ ^(const char * sym, uint64_t addr, int * stop) {
     if (addr && IsPrefixOrEqual((char *)sym, (char *)"_Unittest_")) {
       print("\nRunning ⬚ from 0x⬚\n\n", ﹟s7(sym), ﹟x((__builtin_uint_t)addr));
       runUnitTest((void *)addr, sym, ^(const char * symbol, uint64_t dt) {
         print("\n\nEND ");
         Base𝕟(dt, 10, 0,^(char 𝟶to𝟿) { print("⬚", ﹟c7(𝟶to𝟿)); });
         print(" ns when running ⬚\n", ﹟s7(symbol));
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
{  printGreetings();
    int64_t nanosecs = 0; 
#if defined _NDEBUG
    int debug=1;
#else
    int debug=0;
#endif
    __builtin_int_t units = RunUnittests(argv[0], U"", U"", false /*, &debug */, &nanosecs);
    print("\nUnit(s): ⬚\nTotal: ⬚ ns\n\n", ﹟d(units), ﹟d(nanosecs));
    print("𝐴𝑢𝑡𝑜𝑚𝑎𝑡𝑒𝑑 𝑡𝑒𝑠𝑡𝑠 𝑑𝑖𝑑 𝑛𝑜𝑡 𝑓𝑖𝑛𝑑 𝑎𝑛𝑦 𝑒𝑟𝑟𝑜𝑟𝑠 😐 \n");
    lastChance(debug);
    return 0;
}


