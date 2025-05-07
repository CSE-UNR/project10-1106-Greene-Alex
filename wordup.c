//Alex Greene
//Final Project

#include<stdio.h>

#define WORD_FILE "mystery.txt"
#define WORD_SIZE 6
#define NUM_ROWS 12

void takeGuess(char userGuesses[][WORD_SIZE], int internalGuess, int currentGuess);
int guessCheck(char userGuesses[WORD_SIZE]);
int comparison(char userGuesses[][WORD_SIZE], char theWord[WORD_SIZE], int internalGuess, int currentGuess);
void display(char userGuesses[][WORD_SIZE], int internalGuess);
void lowercase(char userGuesses[][WORD_SIZE], int internalGuess);
int noCapitalPointing(char theWord, char capitals[WORD_SIZE], int count);

int main(){
//Variables(char userGuesses[][WORD_SIZE], int internalGuess)
	char mysteryWord[WORD_SIZE];
	FILE* readFilePointer;
	char guesses[NUM_ROWS][WORD_SIZE];
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
	}while(test == 0 && guessNumber < 7);
	
	if(test == 1){
		printf("\n===========================================\n");
		printf("Congrats! You guessed the word in %d tries!\n", guessNumber - 1);
		printf("===========================================\n");
	}
	
	else if(test == 0 && guessNumber == 6){
		printf("\n===========================================\n");
		printf("You lost. The word was %s\n", mysteryWord);
		printf("===========================================\n");
	}
	
return 0;
}

void takeGuess(char userGuesses[][WORD_SIZE], int internalGuess, int currentGuess){
	
	char tempGuess[WORD_SIZE];
	
	if(currentGuess < NUM_ROWS/2){
		do{
			printf("Guess %d! Enter your guess: ", currentGuess);
			scanf("%s", tempGuess);	
		}while(guessCheck(tempGuess) == 1);
		
		for(int i = 0; i < WORD_SIZE; i++){
			userGuesses[internalGuess][i] = tempGuess[i];
		}
		
		lowercase(userGuesses, internalGuess);
		
	}
	
	else{
		do{
			printf("Final Guess! Enter your guess: ");
			scanf("%s", tempGuess);
		}while(guessCheck(tempGuess) == 1);
		
		for(int i = 0; i < WORD_SIZE; i++){
			userGuesses[internalGuess][i] = tempGuess[i];
		}
		
		lowercase(userGuesses, internalGuess);
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

void lowercase(char userGuesses[][WORD_SIZE], int internalGuess){
	
	for(int i = 0; i < WORD_SIZE; i++){
		if(userGuesses[internalGuess][i] >= 65 && userGuesses[internalGuess][i] <= 90){
		userGuesses[internalGuess][i] += 32;
		}
	}
}

int comparison(char userGuesses[][WORD_SIZE], char theWord[WORD_SIZE], int internalGuess, int currentGuess){
	
	char guessStorage[WORD_SIZE];
	int count = 0, counter = 0;
	char capitals[WORD_SIZE];
	
	
	for(int i = 0; i < WORD_SIZE; i++){
		userGuesses[internalGuess+1][i] = ' ';
	}
	
	for(int i = 0; i < WORD_SIZE; i++){
		guessStorage[i] = userGuesses[internalGuess][i];
	}
	
	for(int i = 0; i < WORD_SIZE; i++){
		if(guessStorage[i] == theWord[i]){
			noCapitalPointing(theWord[i], capitals, counter);
			counter++;
		}
	}
	
	for(int i = 0; i < WORD_SIZE; i++){
		for(int j = 0; j < WORD_SIZE; j++){
			
			if(guessStorage[i] == '\0'){
			}
			
			else if(guessStorage[i] == theWord[i]){
				userGuesses[internalGuess][i] = guessStorage[i] - 32;
				noCapitalPointing(theWord[i], capitals, count);
				count++;
			}
			
			else if(guessStorage[i] == theWord[j] && guessStorage[i] != capitals[j]){
				userGuesses[internalGuess+1][i] = '^';
			}
		}
	}
	
	if(count / WORD_SIZE == 5){
		return 1;
	}
	
return 0;
}

int noCapitalPointing(char theWord, char capitals[WORD_SIZE], int count){

		capitals[count] == theWord;
return 0;
}

void display(char userGuesses[][WORD_SIZE], int internalGuess){
	
	for(int i = 0; i < internalGuess+1; i++){
		printf("%s\n", userGuesses[i]);
		for(int j = 0; j < WORD_SIZE; j++){
			printf("%c", userGuesses[i+1][j]);
		}
		printf("\n\n");
		i++;
	}
}
