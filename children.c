//Ambrosia Ingoglia

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define NPROCS 2 /* numbeer of child processes */
int blocker();
int main(int argc, char *argv[]){
	pid_t pid;
	int i;
	int stat; /* child's exit value */
	/*create the child process */
	for(i = 0; i < NPROCS; i++){
		//creates a child process using fork()
		pid = fork();
		if (pid == -1){
			fprintf(stderr, "fork() failed, errno=%d\n", errno);
		} else if (pid == 0) {
			/* this is the child process */
			//sleep for 3 seconds
			sleep(3);
            //run a 'blocker' program
            blocker();
            //the pid of the 'blocker' program
            pid_t process_id;
            process_id = getpid();
            printf("Child: The blocker id: %d\n",process_id);
            //how the 'blocker' program terminated 
            printf("Child: The blocker program terminated normally\n");
			return(0);
		}
	}
	/*this is the parent */
    //the pid of the child
    fprintf(stdout, "Parent: I'm a new born child, my pid=%u\n", getpid());
	//wait for the child to complete then sends SIGKILL
	kill(pid, SIGKILL);
	/* wait for the child process to exit */
	for(i = 0; i < NPROCS; i++){
		pid = wait(&stat);
		fprintf(stdout, "Parent: Child %u has terminated\n", pid);
		//how the child process terminated 
		 if(WIFEXITED(stat)){
			fprintf(stdout, "Child %u has terminated normally\n", pid);
			if(WEXITSTATUS(stat)){
				fprintf(stdout, "The lowest byte of exit value for child %u is %d\n", pid, WEXITSTATUS(stat));
			} else {
				fprintf(stdout, "Child %d has returned a value of 0\n", pid);
			}
		}
		if (WIFSIGNALED(stat) != 0) {
			/* child terminated due to a signal */
			fprintf(stdout, "Child %d terminated due to a signal\n", pid);
			fprintf(stdout, "Child %d terminated due to getting singnal %d\n", pid, WTERMSIG(stat));
		}
	}
	return(0);
}

int blocker() {
  struct sigaction sact;
  sigset_t new_set, old_set;
  sigemptyset(&sact.sa_mask);
  sact.sa_flags=0;
  sigaction(SIGALRM, &sact, NULL);
  sigemptyset(&new_set);
  sigaddset(&new_set,SIGALRM);
  sigprocmask(SIG_BLOCK,&new_set,&old_set);
  //the status of the 'blocker' program
  printf("All signals are blocked\n");
  sleep(3);
  sigprocmask(SIG_SETMASK,&old_set,NULL);
  printf("All signals are unblocked\n");
  return 0;
}
