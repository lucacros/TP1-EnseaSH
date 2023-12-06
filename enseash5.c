//5. Code time command
#include<stdio.h>
#include<unistd.h>//necessary to use the write function
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h> 
#include<time.h> // importing clock_getime function

#define SIZE 256 // High of memory for the command line


char COMMAND[SIZE]; // stock the command user
int number;
char startline[256] = "enseash % "; 

//Q5 time initialization
struct timespec Start;
struct timespec End;
long duration;


int main (){
    char message[]=" ~~~ WELCOME to the Fabulous ENSEA SHELL !!! ~~~ \nPour quitter tapez sur 'exit'.\nenseash %";
    char goodbye[] = "Bye bye...\n";
    size_t messageSize = sizeof(message)-1; //the size of the message excluding the null character



    
    
    
    //using the write fonction to write to the standard output(int fildes=1)
    write(1,message, messageSize); 

    while(1){



        //we read the command line
        number = read(STDOUT_FILENO,COMMAND,SIZE);


        if (number == 1) {
            strcpy(COMMAND, "date"); // Sending date if user send "enter" with nothing
        } else {
            COMMAND[number - 1] = '\0'; // Verifying that the command line is terminated
        }
        
        if (strcmp(COMMAND, "exit") == 0) {
            // write "Bye bye" and get out of the while
            write(STDOUT_FILENO, goodbye, sizeof(goodbye) - 1);
            exit(EXIT_SUCCESS);
        }
        //verification that ctrl+d has been pressed
        if (number==0){
            write(STDOUT_FILENO, goodbye, sizeof(goodbye) - 1);
            exit(EXIT_SUCCESS);
        }

        //Q5. time Start
        clock_gettime(CLOCK_REALTIME,&Start);
        //creating a child process
        pid_t pid = fork();
        int status;
        
        

        if (pid==-1)
        {
            perror("the fork bog down...\n"); // error message
        }
        
        if (pid==0)
        {
            //Child process
            execlp(COMMAND,COMMAND,(char *) NULL);
            perror("error enseash %%");
            exit(127); // command not found
        }

        else
        {
            //Parent process
            wait(&status);
            //Q5. time end
            clock_gettime(CLOCK_REALTIME,&End);
            //duration calcul
            duration = ((End.tv_sec- Start.tv_sec)*1000 + End.tv_nsec - Start.tv_nsec)/1000000 ; 
            // we will stock the char in startline with the function sprintf
            if(WIFEXITED(status)){
                sprintf(startline,"enseash [exit:%d | %ld ms] %%" , WEXITSTATUS(status),duration); //%ld for long integer duration value
            }
            else if(WIFSIGNALED(status)){
                sprintf(startline,"enseash [sig:%d | %ld ms] %%",WTERMSIG(status),duration);// ms unit : because child process execution time takes millisecond
            }

            write(STDOUT_FILENO,startline,strlen(startline));
        
        }
    }

    
    



}