#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

__attribute__((constructor))
void setup(){
  setvbuf(stdout,NULL,2,0);
  setvbuf(stderr,NULL,2,0);
  setvbuf(stdin,NULL,2,0);
}

int get_index(char* item, char* arr[]){
	for(int i = 0 ; i < 10 ; i++){
		if (strncmp(item, arr[i], strlen(item)) == 0){
			return i ;
		}
	}
	return -1 ;
}

void add_topping(void* pizza[], char* toppings[], int topping_status[]){
	int quantity ;
	int id ;
	char topping[15] ;

	puts("Which topping ?") ;
	fgets(topping, 14, stdin) ;
	topping[strcspn(topping, "\n")] = '\0' ;
	id = get_index(topping, toppings) ;
	if (id == -1){
		puts("We don't provide this topping yet !") ;
		return ;
	}
	puts("How much ?") ;
	scanf("%d", &quantity) ;
	getchar() ;
	if (quantity < 0){
		puts("Enter a positive quantiy !") ;
		return ;
	}
	else if (quantity > 63){
		puts("Thats too much !") ;
		return ;
	}
	pizza[id] = malloc(8 * quantity) ;
	topping_status[id] = quantity ;
	printf("Ok, adding %s\n", toppings[id]) ;
}

void customize_topping(void* pizza[], char* toppings[], int* topping_status){
	int id ;
	printf("Which one to customize ?\n") ;
	char topping[15] ;

	fgets(topping, 14, stdin) ;
	topping[strcspn(topping, "\n")] = '\0' ;
	id = get_index(topping, toppings) ;
	if (!(0 <= id <= 9)){
		puts("Don't try to be fishy !") ;
		return ;
	}
	if (topping_status[id] == 0){
		printf("%s is not yet added on pizza\n", toppings[id]) ;
		return ;
	}
	printf("Enter new modified topping : ") ;
	read(0, pizza[id], topping_status[id] * 8);
	puts("New topping added successfully !") ;
}


void remove_topping(void* pizza[], char* toppings[], int* topping_status){
	int id ;
	char topping[15] ;
	puts("Which topping to remove ?") ;
	fgets(topping, 14, stdin) ;
	topping[strcspn(topping, "\n")] = '\0' ;
	id = get_index(topping, toppings) ;

	free(pizza[id]) ;
	topping_status[id] = 0 ;
	printf("%s removed successfully !\n", toppings[id]) ;
}

void verify_topping(void* pizza[], char* toppings[], int* topping_status){
	int id ;
	char topping[15] ;

	puts("Which topping to verify ?") ;
	fgets(topping, 14, stdin) ;
	topping[strcspn(topping, "\n")] = '\0' ;
	id = get_index(topping, toppings) ;
	if (id != -1){
		puts(pizza[id]) ;
		return ;
	}
	else {
		puts("Nope.") ;
	}
}


void bake_pizza(void* pizza[], int* topping_status){
	puts("Baking ....") ;
	for (int id = 0 ; id < 10 ; id++){
		if (topping_status[id]) {
			free(pizza[id]) ;
		}
	}
	puts("Here it is : 🍕") ;
	exit(69) ;
}

void menu(){
	puts("\nChoose one of the following options:") ;
	puts("1. Add topping") ;
	puts("2. Customize topping") ;
	puts("3. Remove topping") ;
	puts("4. Verify toppings") ;
	puts("5. Bake Pizza") ;
}

void banner(){
puts(" ____    _                        _ ");
puts("|  _ \\  | |      __ _  _ __    __| |");
puts("| |_) | | |     / _` || '_ \\  / _` |");
puts("|  _ <  | |___ | (_| || | | || (_| |");
puts("|_| \\_\\ |_____| \\__,_||_| |_| \\__,_|");
puts("                                    ");
puts(" ____   _                        _        ");
puts("|  _ \\ (_) ____ ____  ___  _ __ (_)  __ _ ");
puts("| |_) || ||_  /|_  / / _ \\| '__|| | / _` |");
puts("|  __/ | | / /  / / |  __/| |   | || (_| |");
puts("|_|    |_|/___|/___| \\___||_|   |_| \\__,_|");
}

int main(){
	void* pizza[10] ;
	int topping_status[10] = {0} ;
	char* toppings[10] = {"Tomato", "Onion", "Capsicum", "Corn", "Mushroom", "Pineapple", "Olives", "Double Cheese", "Paneer", "Chicken"} ;
	banner() ;
	while (1){
		menu() ;
		int choice ;
		printf("Enter your choice : ") ;
		scanf("%d", &choice) ;
		getchar() ;
		puts("") ;
		switch (choice)
		{
		case 1 :
			add_topping(pizza, toppings, topping_status) ;
			break ;
		case 2 :
			customize_topping(pizza, toppings, topping_status) ;
			break ;
		case 3 :
			remove_topping(pizza, toppings, topping_status) ;
			break ;
		case 4 :
			verify_topping(pizza, toppings, topping_status) ;
			break ;
		case 5 :
			bake_pizza(pizza, topping_status) ;
			break ;
		default:
			puts("Enter appropriate choice !") ;
			break ;
		}
	}
}
