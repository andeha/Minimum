/* 􀥢 fork-thread.c | details on bridging Swift and Twinbeam. */

import ClibTwinbeam;
import Stdio; /* ⬷ in c++ later renamed to 'std.io'. */
import Unistd; /* fork */
/* ⬷ modules not only in c++ but in c as well. Enter 
 'import std.core;' to include the standard C++ library. */
/* todo: add -enable-experimental-cxx-interop and base-16 mangling. */

#if defined 𝟷𝟸𝟾₋bit₋integers₋with₋calling₋conventions
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all) { return -1; }
#else
int Details_in_C(uint64_t pid, int32_t cross) { return -1; }
#endif

pid_t Twinbeam₋spawn(
  const char * pathandcommand₋u8s, 
  const char * command₋u8s, /* ⬷ two UnsafePointer<Int8>. */
  int * fd_p2c, int * fd_c2p /*, const char * NullTerminatedEnv */
)
{
   pid_t pid = fork(); int status=0; /* ⬷ two instances in two images. */
   if (pid == -1) { mfprint("error when fork\n"); return -1; }
   if (pid) { /* Parent ⤐ */
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
       const char * env[] = { "SPAWNED_BY_TWINBEAM", "TERM=xterm", (const char *)0 };
       status = execle(pathandcommand₋u8s,command₋u8s, (char *)0, env);
       if (status == -1) { mfprint("error when execlp\n"); exit(1); }
       fflush(stdout); /* ⬷ mandates 'import Stdio'. */
   }
   return pid;
}

