#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

__attribute__((constructor))
void setup(){
  setvbuf(stdout,NULL,2,0);
  setvbuf(stderr,NULL,2,0);
  setvbuf(stdin,NULL,2,0);
}

//gcc -o chal -fno-stack-protector -no-pie chal.c

void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (float) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}


int main(){
    char key[30] ;
    char actual_key[30];

    srand(time(NULL)) ;

    rand_str(actual_key, 30) ;

    puts("Welcome to Escape the R00m !") ;
    puts("You have only two chances to escape the room ...");
    printf("Enter key : ") ;
    read(0, key, 0x50);
    if (strncmp(actual_key, key, 30) == 0){
        puts("That was a nice escape ... But there is more to it !") ;
    }
    else {
    	printf("%s is not the key, try again !\n", key);
    }
    printf("Enter key : ") ;
    scanf("%s", key) ;
    if (strncmp(actual_key, key, 30) == 0){
        puts("That was a nice escape ... But there is more to it !") ;
    }
    else {
    	puts("Wrong, go away !");
    }
    return 0 ;
 }


int escape(){
    puts("Sweet !") ;
    system("/bin/sh") ;
}
