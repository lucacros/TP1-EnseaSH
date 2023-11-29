//1.Display the welcome message

#include <unistd.h> //necessary to use the write function

int main (){
    char message[]="Bienvenue sur le shell ENSEA. \nPour quitter tapez sur 'exit'.\n";
    size_t messageSize = sizeof(message)-1; //the size of the message excluding the null character
    
    //using the write fonction to write to the standard output(int fildes=1)
    write(1,message, messageSize); 
}
