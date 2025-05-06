//Alex Greene
//Final Project

#include<stdio.h>

#define WORD_FILE "mystery.txt"
#define WORD_SIZE 6
#define ROW_MAX 12

void takeGuess(char userGuesses[WORD_SIZE][ROW_MAX], int internalGuess, int currentGuess);
int guessCheck(char userGuesses[WORD_SIZE]);
int comparison(char userGuesses[WORD_SIZE][ROW_MAX], char theWord[WORD_SIZE], int internalGuess, int currentGuess);
void display(char userGuesses[WORD_SIZE][ROW_MAX], int internalGuess);

int main(){
//Variables(char userGuesses[][WORD_SIZE], int internalGuess)
	char mysteryWord[WORD_SIZE];
	FILE* readFilePointer;
	char guesses[WORD_SIZE][ROW_MAX];
	int internalValue = 0;
	int guessNumber = 1;
	int test = 0;
	
//File stuffs
	readFilePointer = fopen(WORD_FILE, "r");
	
	if(readFilePointer == NULL){
		printf("Can't open file\n");
		return 0;
	}
	
//Get the word from the file into a char array
	fscanf(readFilePointer, "%s", mysteryWord);
		
	fclose(readFilePointer);
	
//Take user's guess and check if its legal
	do{
	takeGuess(guesses, internalValue, guessNumber);
	
//Compare each letter to the char array
	test = comparison(guesses, mysteryWord, internalValue, guessNumber);
	
//Display and point to the correct letters (if any).
	display(guesses, internalValue);
	
//Repeat until A: All letters are correct or B: All guesses have been used.
	internalValue++;
	internalValue++;
	guessNumber++;
	}while(test == 0 && guessNumber < 6);
	
return 0;
}

void takeGuess(char userGuesses[WORD_SIZE][ROW_MAX], int internalGuess, int currentGuess){
	
	char tempGuess[WORD_SIZE];
	
	if(currentGuess < ROW_MAX/2){
		do{
			printf("Guess %d! Enter your guess: ", currentGuess);
			scanf("%s", tempGuess);	
		}while(guessCheck(tempGuess) == 1);
		
		for(int i = 0; i < WORD_SIZE; i++){
			userGuesses[internalGuess][i] = tempGuess[i];
		}
		
		for(int i = 0; i < WORD_SIZE; i++){
			//Changes letters to lowercase
			if(userGuesses[internalGuess][i] >= 65 && userGuesses[internalGuess][i] <= 90){
			userGuesses[internalGuess][i] += 32;
			}
		}
		
	}
	
	else{
		do{
			printf("Final Guess! Enter your guess: ");
			scanf("%s", tempGuess);
		}while(guessCheck(tempGuess) == 1);
		
		for(int i = 0; i < WORD_SIZE; i++){
			userGuesses[internalGuess][i] = tempGuess[i];
		}
		
		for(int i = 0; i < WORD_SIZE; i++){
			//Changes letters to lowercase
			if(userGuesses[internalGuess][i] >= 65 && userGuesses[internalGuess][i] <= 90){
			userGuesses[internalGuess][i] += 32;
			}
		}
	}
	
}

int guessCheck(char userGuesses[WORD_SIZE]){

	if(userGuesses[WORD_SIZE-1] != '\0'){
		printf("Invalid word size, please try again \n");
		return 1;
	}
	
	int charCheck = 0;
	for(int i = 0; i < WORD_SIZE-1; i++){
		if(userGuesses[i] < 65 || userGuesses[i] > 90 && userGuesses[i] < 97 || userGuesses[i] > 122){
			charCheck = 1;
		}
	}
	if(charCheck == 1){
		printf("Please enter a letter\n");
		return 1;
	}
	
	
return 0;	
}

int comparison(char userGuesses[WORD_SIZE][ROW_MAX], char theWord[WORD_SIZE], int internalGuess, int currentGuess){
	
	char guessStorage[WORD_SIZE];
	int count = 0;
	
	for(int i = 0; i < WORD_SIZE; i++){
		userGuesses[internalGuess+1][i] = ' ';
	}
	
	for(int i = 0; i < WORD_SIZE; i++){
		guessStorage[i] = userGuesses[internalGuess][i];
	}
	
	for(int i = 0; i < WORD_SIZE; i++){
		for(int j = 0; j < WORD_SIZE; j++){
			
			if(guessStorage[i] == '\0'){
			}
			
			else if(guessStorage[i] == theWord[i]){
				userGuesses[internalGuess][i] = guessStorage[i] - 32;
				count++;
			}
			
			else if(guessStorage[i] == theWord[j]){
				userGuesses[internalGuess+1][i] = '^';
			}
		}
	}
	printf("=%s=\n\n", userGuesses[7]);
	
	if(count / WORD_SIZE == 5){
		printf("\n===========================================\n");
		printf("Congrats! You guessed the word in %d tries!\n", currentGuess);
		printf("===========================================\n");
		return 1;
	}
	
return 0;
}

void display(char userGuesses[WORD_SIZE][ROW_MAX], int internalGuess){
	
	for(int i = 0; i < internalGuess+1; i++){
		printf("%s\n", userGuesses[i]);
		printf("%s\n\n", userGuesses[i+1]);
		i++;
	}
}
