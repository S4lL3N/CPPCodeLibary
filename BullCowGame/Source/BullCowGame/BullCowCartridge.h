

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void MyInitGame();
	void EndGame();
	void ProcessGuess(const FString& UserGuess);
	bool IsIsogram(const FString& Word) const;
	FBullCowCount GetBullCows(const FString& Guess);
	TArray<FString> Words;
	


	
	private:
		FString HiddenWord;
		int32 NumberOfLives;
		bool bEndGame;
	
};
