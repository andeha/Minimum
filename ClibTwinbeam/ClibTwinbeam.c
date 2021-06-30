/*  ClibTwinbeam.cpp | bridging Swift and Twinbeam. */

/* #include <Twinbeam.h> */
#include "ClibTwinbeam.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/* import Twinbeam;
import Unistd;
import Stdio; */ /* ⬷ rename later to 'std.io'. */
/* ⬷ enter 'import std.core;' to include the standard C++ library. */
/* todo: add -enable-experimental-cxx-interop. */

/* extern "C" */
#if defined 𝟷𝟸𝟾₋bit₋integers
int Details_in_C(uint64_t pid, int32_t cross, __uint128_t all) { return -1; }
#else
int Details_in_C(uint64_t pid, int32_t cross) { return -1; }
#endif

#define mfprint(x) printf(x)

/* extern "C" */ 
pid_t Twinbeam₋spawn(const char * utf8₋command, int * fd_p2c, int * fd_c2p /*, const char * NullTerminatedEnv */)
{
   pid_t pid = fork(); int status=0; /* ⬷ two instances in two images. */
   if (pid == -1) { mfprint("error when fork\n"); return -1; }
   if (pid) { 
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
       const char * envs[] = { "SPAWNED_BY_TWINBEAM", (const char *)NULL };
       status = execle(utf8₋command, utf8₋command, (char *)NULL, envs);
       if (status == -1) { mfprint("error when execlp\n"); exit(1); }
       fflush(stdout); /* ⬷ mandates 'import Stdio'. */
   }
   return pid;
}