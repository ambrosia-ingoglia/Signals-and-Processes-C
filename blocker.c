//Ambrosia Ingoglia

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct sigaction sact;
  sigset_t new_set, old_set;
  sigemptyset(&sact.sa_mask);
  sact.sa_flags=0;
  sigaction(SIGALRM, &sact, NULL);
  sigemptyset(&new_set);
  sigaddset(&new_set,SIGALRM);
  sigprocmask(SIG_BLOCK,&new_set,&old_set);
  printf("All signals are blocked\n");
  sleep(3);
  sigprocmask(SIG_SETMASK,&old_set,NULL);
  printf("All signals are unblocked\n");
  return 0;
}