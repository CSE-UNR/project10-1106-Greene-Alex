//Alex Greene
//Final Project

#include<stdio.h>

#define WORD_FILE "mystery.txt"
#define WORD_SIZE 6
#define GUESSES 12

void takeGuess(char userGuesses[][WORD_SIZE], int currentGuess);
int guessCheck(char userGuesses[WORD_SIZE]);
int comparison(char userGuesses[][WORD_SIZE], char theWord[WORD_SIZE], int currentGuess);
void display(char userGuesses[][WORD_SIZE], int currentGuess);

int main(){
//Variables(char userGuesses[][WORD_SIZE], int currentGuess)
	char mysteryWord[WORD_SIZE];
	FILE* readFilePointer;
	char guesses[GUESSES][WORD_SIZE];
	int guessNumber = 0;
	
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
	takeGuess(guesses, guessNumber);
	
//Compare each letter to the char array
	comparison(guesses, mysteryWord, guessNumber);
	
//Display and point to the correct letters (if any).
	display(guesses, guessNumber);
	
//Repeat until A: All letters are correct or B: All guesses have been used.
	guessNumber++;
	guessNumber++;
	}while(comparison(guesses, mysteryWord, guessNumber) != 1);
	
return 0;
}

void takeGuess(char userGuesses[][WORD_SIZE], int currentGuess){
	
	char tempGuess[WORD_SIZE];
	
	if(currentGuess < GUESSES){
		do{
			printf("Guess %d! Enter your guess: ", currentGuess+1);
			scanf("%s", tempGuess);	
		}while(guessCheck(tempGuess) == 1);
		
		for(int i = 0; i < WORD_SIZE; i++){
			userGuesses[currentGuess][i] = tempGuess[i];
		}
		
		for(int i = 0; i < WORD_SIZE; i++){
			//Changes letters to lowercase
			if(userGuesses[currentGuess][i] >= 65 && userGuesses[currentGuess][i] <= 90){
			userGuesses[currentGuess][i] += 32;
			}
		}
		
	}
	
	else{
		do{
			printf("Final Guess! Enter your guess: ");
			scanf("%s", tempGuess);
		}while(guessCheck(tempGuess) == 1);
		
		for(int i = 0; i < WORD_SIZE; i++){
			userGuesses[i][currentGuess] = tempGuess[i];
		}
		
		for(int i = 0; i < WORD_SIZE; i++){
			//Changes letters to lowercase
			if(userGuesses[currentGuess][i] >= 65 && userGuesses[currentGuess][i] <= 90){
			userGuesses[currentGuess][i] += 32;
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

int comparison(char userGuesses[][WORD_SIZE], char theWord[WORD_SIZE], int currentGuess){
	
	char guessStorage[WORD_SIZE];
	int count = 0;
	
	for(int i = 0; i < WORD_SIZE; i++){
		userGuesses[currentGuess+6][i] = ' ';
	}
	
	for(int i = 0; i < WORD_SIZE; i++){
		guessStorage[i] = userGuesses[currentGuess][i];
	}
	
	for(int i = 0; i < GUESSES; i++){
		for(int j = 0; j < WORD_SIZE; j++){
			
			if(guessStorage[i] == '\0'){
			}
			
			else if(guessStorage[i] == theWord[i]){
				userGuesses[currentGuess][i] = guessStorage[i] - 32;
				count++;
			}
			
			else if(guessStorage[i] == theWord[j]){
				userGuesses[currentGuess+6][i] = '^';
			}
		}
	}
	
	//ENDING NOTE: start on the problem w/ it not ending
	if(count / WORD_SIZE == 5){
		printf("Congrats! You guessed the word in %d tries!\n", currentGuess+1);
		return 1;
	}
	
return 0;
}

void display(char userGuesses[][WORD_SIZE], int currentGuess){
	
	for(int i = 0; i < currentGuess+1; i++){
		printf("%s\n", userGuesses[i]);
		printf("%s\n", userGuesses[i+6]);
		printf("\n");
		i++;
	}
	
}
