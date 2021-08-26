// Copyright Shae Allen 2020.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	
	//Gets Object name and outputs to the Window/DeveloperTools/OutputLog
	FString ObjectName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Object Name is: %s"), *ObjectName); //the * before the ObjectName variable means that it is a pointer to a location in memory (not a copy)
	
	
	//gets the objects location... returns a FVector thats been converted to a FString
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	//prints objects name and location 
	UE_LOG(LogTemp, Warning, TEXT("Object Name is: %s, and is located @:%s"), *ObjectName, *ObjectPosition);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

