#include <iostream>
#include <ctime>

//Unreal naming conventions require pascal case ie PascalCase

//void doesn't return data
void PrintIntro(int Difficulty){
    //print welcome message to the terminal 
    std::cout << std::endl; //new line same as \n
    std::cout << "\nYou are a secret agent breaking into a Level " << Difficulty << " secure server room. \n";
    std::cout << "You need to enter the correct codes to continue...";
    std::cout << std::endl;
}

bool PlayGame(int Difficulty){
    
    PrintIntro(Difficulty);    
    //declare 3 variable for number code
    const int CodeA = rand() % Difficulty + Difficulty;
    const int CodeB = rand() % Difficulty + Difficulty;
    const int CodeC = rand() % Difficulty + Difficulty;

    int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    //print CodeSum and CodeProduct to the terminal
    std::cout << std::endl;
    std::cout << "There are 3 numbers in the code...\n" << std::endl;

    std::cout << "The code adds up to: ";
    std::cout << CodeSum << std::endl;

    std::cout << "The code multiply to give: " << CodeProduct << std::endl;

    //get input from user and store it in the PlayerGuess variable 
    std::cout << "\nEnter your guess seperated by spaces: ";
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;

    std::cout << "You entered: " << GuessA << GuessB << GuessC << std::endl;
    
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    std::cout << "Your code adds up to: ";
    std::cout << GuessSum << std::endl;

    std::cout << "Your code multiplies to give:  " << GuessProduct << std::endl;

    //checks if players guess is correct
    if(GuessSum == CodeSum && GuessProduct == CodeProduct){
        std::cout<<"\n***   Well Done Agent! You Cracked the code and extracted the file. Keep going!!! ***";
        return true;
    }
    else{
        std::cout << "\n***   You entered the wrong code... Alarm Triggered!   ***\n***   Try Again!!!   ***";
        return false;
    }
}


int main(){
    srand(time(NULL)); //create new randow sequence based on time of day

    int LevelDifficulty = 1;
    const int MaxLevel = 10;

    while(LevelDifficulty <= MaxLevel){
        bool bLevelComplete = PlayGame(LevelDifficulty); // Unreal naming conventions require any boolean variable to start with a lowercase b
    
        std::cin.clear();//clears cin of any errors 
        std::cin.ignore();//discards what caused the error or discards the buffer

        if(bLevelComplete){
            ++LevelDifficulty;
        }
    }

    std::cout << "\n***   Great work Agent! You Got all the files. Now get out of there!   ***\n";
    
    return 0;
}
