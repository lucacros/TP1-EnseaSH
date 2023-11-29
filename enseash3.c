//2. Execute commadn and back to prompt
#include<stdio.h>
#include<unistd.h>//necessary to use the write function
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h> 

#define SIZE 256 // High of memory for the command line


char COMMAND[SIZE]; // stock the command user
int number;


int main (){
    char message[]="Bienvenue sur le shell ENSEA. \nPour quitter tapez sur 'exit'.\n";
    char goodbye[] = "Bye bye...";
    size_t messageSize = sizeof(message)-1; //the size of the message excluding the null character
    
    //using the write fonction to write to the standard output(int fildes=1)
    write(1,message, messageSize); 

    while(1){
        write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));


        //we read the command line
        number = read(STDOUT_FILENO,COMMAND,SIZE);


        if (number == 1) {
            strcpy(COMMAND, "date"); // Sending date if user send "enter" with nothing
        } else {
            COMMAND[number - 1] = '\0'; // Verifying that the command line is terminated
        }
      
        //creating a child process
        pid_t pid = fork();
        int status;
        
        if (strcmp(COMMAND, "exit") == 0) {
            // write "Bye bye" and get out of the while
            write(STDOUT_FILENO, goodbye, sizeof(goodbye) - 1);
            break;
        }
        //verification that ctrl+d has been pressed
        if (number==0){
            write(STDOUT_FILENO, goodbye, sizeof(goodbye) - 1);
            break;
        }

        if (pid==-1)
        {
            perror("the fork bog down...\n"); // error message
        }
        
        if (pid==0)
        {
            //Child process
            execlp(COMMAND,COMMAND,(char *) NULL);
        }

        else
        {
            //Parent process
            wait(&status);
        
        }
    }


    



}