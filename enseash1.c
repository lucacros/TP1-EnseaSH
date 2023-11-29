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
    size_t messageSize = sizeof(message)-1; //the size of the message excluding the null character
    
    //using the write fonction to write to the standard output(int fildes=1)
    write(1,message, messageSize); 

    while(1){
        // line before the command in the termina
        write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));  //strlen(string*) gives the char tab size
        
        //we read the command line
        number = read(STDOUT_FILENO,COMMAND,SIZE);
        COMMAND[number-1]='\0'; // Verifying that command line is over

        //creating a child process
        pid_t pid = fork() ;
        int status;
        

        if (pid==-1)
        {
            perror("the fork bog down...\n"); // error message
        }
        
        else
        {
            wait(&status);
        
        }
    }


    



}