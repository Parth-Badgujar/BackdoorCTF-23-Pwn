#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>



__attribute__((constructor))
void setup(){
  setvbuf(stdout,NULL,2,0);
  setvbuf(stderr,NULL,2,0);
  setvbuf(stdin,NULL,2,0);
}



char *fruits[] = {
    "Apple", 
    "Orange", 
    "Mango", 
    "Banana", 
    "Pineapple", 
    "Watermelon", 
    "Guava", 
    "Kiwi", 
    "Strawberry", 
    "Peach"
} ;

int main(){
    srand(time(NULL)) ;
    int shell = 1 ;

    puts("There is a basket full of fruits, guess the fruit which I am holding ..."); 
    puts("This seems hard, so I will give an awesome reward, something like a shell if you guess all the fruits right :)") ;

    usleep(2000000) ;
    puts("\nThe game starts now !") ;

    char *fruit ;
    char input[12] ;

    for(int i = 0 ; i < 50 ; i++){
        fruit = fruits[rand() % 10] ;

        printf("%d\n", i + 1) ;
        printf("Your guess : ") ;

        fgets(input, 12, stdin) ;
        input[strcspn(input, "\n")] = '\0' ;

        if (strncmp(fruit, input, strlen(fruit)) == 0){
            puts("Correct !") ;
            puts("") ;
        }
        else {
            puts("Oops ! Wrong Guess ..") ;
            puts("No shell for you :(") ;
            shell = 0 ; ;
            break ;
        }
    }
    if (shell){
        system("/bin/sh") ;
    }
    
}

