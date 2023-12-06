//6. Complex command execution
#include<stdio.h>
#include<unistd.h>//necessary to use the write function
#include<stdlib.h>
#include<string.h>// Q6. strtok function
#include<sys/wait.h> 
#include<time.h> //Q5. importing clock_getime function

#define SIZE 256 // High of memory for the command line


char COMMAND[SIZE]; // stock the command user
int number;
char startline[256] = "enseash % "; 

//Q5. time initialization
struct timespec Start;
struct timespec End;
long duration;

//Q6. Commandline
char*Word[SIZE] = {NULL};


int main (){
    char message[]=" ~~~ WELCOME to the Fabulous ENSEA SHELL !!! ~~~ \nPour quitter tapez sur 'exit'.\nenseash %";
    char goodbye[] = "Bye bye...\n";
    size_t messageSize = sizeof(message)-1; //the size of the message excluding the null character



    
    
    
    //using the write fonction to write to the standard output(int fildes=1)
    write(1,message, messageSize); 

    while(1){



        //we read the command line
        number = read(STDOUT_FILENO,COMMAND,SIZE);

        //Q6.Separation argument command function 
        int k=0;
        Word[k] = strtok(COMMAND, " ");
        while (Word[k]!= NULL)
        {
           k++;
           Word[k]= strtok(NULL, " ");
        }
        


        if (number == 1) {
            strcpy(COMMAND, "date"); // Sending date if user send "enter" with nothing
        } 
        
        else {
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


        //Creating a child process
        pid_t pid = fork();
        int status;
        

        if (pid==-1)
        {
            perror("the fork bog down...\n"); // error message
        }
        

        //Child process
        if (pid==0)
        {
            //Q6 take command argument and then tab of arguments separated with " "
            execvp(Word[0],Word);
            //

            execlp(COMMAND,COMMAND,(char *) NULL);
            perror("error enseash %%");
            exit(127); // command not found


            
        }


        //Parent process
        else
        {
           
            wait(&status);
            //Q5. time end
            clock_gettime(CLOCK_REALTIME,&End);
            //Q5. duration calcul
            duration = ((End.tv_sec- Start.tv_sec)*1000 + End.tv_nsec - Start.tv_nsec)/1000000 ; 



            //Q4. we will stock the char in startline with the function sprintf
            if(WIFEXITED(status)){
                sprintf(startline,"enseash [exit:%d | %ld ms] %%" , WEXITSTATUS(status),duration); //Q5.%ld for long integer duration value
            }
            else if(WIFSIGNALED(status)){
                sprintf(startline,"enseash [sig:%d | %ld ms] %%",WTERMSIG(status),duration);//Q5. ms unit : because child process execution time takes millisecond
            }

            write(STDOUT_FILENO,startline,strlen(startline));
        
        }

    }
}