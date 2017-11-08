#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
char** parse_line(char *line);
int line_execute(char **instruction);
void signalHandler(int signal){
//	printf("Caught signal %d!\n", signal);
	if(signal == SIGCHLD){
	//	printf("Child ended\n");
		wait(NULL);
	}

}
int main(){
	
	char *input_line = NULL;
	ssize_t buffer_size = 0;
	char **instruction = NULL;
	int status=1;
	while(status){
		printf(">");
		getline(&input_line, &buffer_size, stdin);
		instruction = parse_line(input_line);
		
		status = line_execute(instruction);
	//	printf("hello world!!!");
	}

	return 0;
}

char** parse_line(char *line){
	int bufsize = 64, index = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if(tokens==NULL){
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while(token!=NULL){
		tokens[index++]=token;
		
		if(index >= bufsize){
			bufsize*=2;		
			tokens = realloc(tokens, bufsize*sizeof(char*));
			if(tokens == NULL){fprintf(stderr, "allocation error"); exit(EXIT_FAILURE);}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[index] = NULL;
	return tokens;
}
int line_execute(char **instruction){

	if(instruction[0]==NULL){return 1;}/*no command read*/
	int status;
	int backgnd=0, index=0;
		
	while(instruction[index]){index++;}
	if(strcmp(instruction[index-1],"&")==0){instruction[index-1] =NULL; backgnd=1;}

	signal(SIGCHLD,signalHandler);
	pid_t pid,wait_pid;
	
	/*fork a child process*/
	pid = fork();
	if (pid<0){/*error occurred*/
		fprintf(stderr, "Fork Failed");
	}
	else if (pid == 0){/*child process*/
		if(backgnd){setpgid(pid,0);}
		if(execvp(instruction[0],instruction)==-1){
			perror(instruction[0]);
		}
		exit(EXIT_FAILURE);
	}
	else{/*parent process*/
		/*parent will wait for the child to complete*/

		if(backgnd!=1){
			do{
				wait_pid = waitpid(pid, &status, WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));/*wait until either the processes are exited or killed*/
		}
	//	printf("Child complete\n");
	}
	return 1;
}
