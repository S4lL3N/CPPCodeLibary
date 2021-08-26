#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"//for the FMath::RandRange(0, 10)


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    

    //loading in the wordlist located in the content folder
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("HiddenWordLists/HiddenWords.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);


    //setting up the game
    MyInitGame();

   
}
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{ 
    if (bEndGame) 
    {
        ClearScreen();
        MyInitGame();
    }
    else
    {
        //PrintLine(TEXT("You entered %s."), *Input); //parrots the users input
        ProcessGuess(Input);  
    }
} 
void UBullCowCartridge::MyInitGame()
//function i made and called in the header file
{

    //HiddenWord = TEXT("Cakes"); // this variable is declared in the header file.  //was hard coded for debugging
    HiddenWord = Words[FMath::RandRange(0, 4)];
    NumberOfLives = HiddenWord.Len();
    bEndGame = false;

    //welcome message 
    //anytime you have a string you have to wrap it in the TEXT() macro to ensure compadibility.
    //how to properly format adding data to a string. we do not have to do that in this example beccause it is defined in the cartrige class to include the FString::Printf(TEXT(""));
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), NumberOfLives);
    PrintLine(TEXT("Press TAB to enter the Terminal,"));
    PrintLine(TEXT("Type in your guess and \npress ENTER to continue."));

    //debugging
    //PrintLine(FString::Printf(TEXT("The Hidden Word Is: %s"),*HiddenWord));//how to properly format adding data to a string. we do not have to do that in this example beccause it is defined in the cartrige class to include the FString::Printf(TEXT(""));
    //PrintLine(TEXT("The Hidden Word Is: %s. \nIt is %i characters long."), *HiddenWord, HiddenWord.Len()); //degug line to get the hidden word.    
    PrintLine(TEXT("\nThe Hidden Word Is: %s. "), *HiddenWord);

    
}
void UBullCowCartridge::EndGame() 
{
    bEndGame = true;
    //ClearScreen();
    PrintLine(TEXT("\nPress ENTER to play again."));
}
void UBullCowCartridge::ProcessGuess(const FString& UserGuess)
{
    if (NumberOfLives == 0)
    {
        PrintLine(TEXT("You have no lives left.\n***   GAME OVER   ***"));
        PrintLine(TEXT("The Hidden Word was: %s. "), *HiddenWord);
        EndGame();
        return;
    }
    if (!IsIsogram(UserGuess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }
    if (UserGuess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("Correct, You Win!!!"));
        EndGame();
        return;
    }
    if (UserGuess.Len() != HiddenWord.Len())
    {
        ClearScreen();
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, Try again!"));
       
    }
    else if (HiddenWord.Len() == UserGuess.Len() && UserGuess != HiddenWord)
    {
        NumberOfLives -= 1;
        PrintLine(TEXT("Sorry, try again!"));
        PrintLine(TEXT("You have %i lives left."), NumberOfLives);
        
        
    }
    else if (HiddenWord != UserGuess) {
        NumberOfLives -= 1;
        PrintLine(TEXT("Sorry, try again!"));
        PrintLine(TEXT("You have %i lives left."), NumberOfLives);
    }

    //Show the player how many bulls and cows 
    FBullCowCount Score = GetBullCows(UserGuess);
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);
    PrintLine(TEXT("Guess Again, You have %i lives left."), NumberOfLives);
}
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{ //adding the & at the end of the Fstring indicates that it is being passed by refrence it needs to be a constant because it cannot be changed it also needs to be declared as such in the header file.
    for (int32 Index = 0; Index < Word.Len(); Index++) 
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}
FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess)
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
        
    }
    return Count;
}