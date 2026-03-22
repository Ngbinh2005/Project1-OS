#include "kernel/types.h"
#include "kernel/procinfo.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  struct procinfo info;
  int pid;

  if (argc > 1) {
    pid = atoi(argv[1]);
  } else {
    pid = getpid();
  }

  if(procinfo(pid, &info) == 0){
    printf("Process: %s\n", info.name);
    printf("PID: %d, PPID: %d\n", info.pid, info.ppid);
    printf("State: %d\n", info.state);
    printf("Memory: %d bytes\n", (int)info.sz);
  } else {
    printf("procinfo failed for pid %d\n", pid);
  }
  
  exit(0);
}
