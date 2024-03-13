#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


__attribute__((constructor))
void setup(){
  setvbuf(stdout,NULL,2,0);
  setvbuf(stderr,NULL,2,0);
  setvbuf(stdin,NULL,2,0);
}


typedef struct marks
{
    char name[32] ;
    char comment[64]; 
    int roll ;
    int marks ;    
} data ;


int main(){
    srand(time(NULL)) ;
    data student ;

    puts("Enter your details to view your marks ...");
    printf("Roll Number : ") ;
    scanf("%d", &student.roll) ;
    
    printf("Name : ") ;
    scanf("%s", student.name) ;
    puts("Please Wait ...\n") ;
    usleep(1000000) ;

    student.marks = rand() % 75 ;
    printf("You got %d marks out of 100\n", student.marks) ;

    puts("Any Comments ?") ;
    scanf("%s", student.comment) ;

    puts("Thanks !") ;

    if (student.marks != 100){
        printf("Next time get 100/100 marks for shell :)\n") ;
    }
    else {
        printf("Cool ! Here is your shell !\n") ;
        system("/bin/sh") ;
    }

}
