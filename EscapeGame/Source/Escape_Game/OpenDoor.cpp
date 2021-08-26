// Copyright Shae Allen 2020.

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	FindPresurePlate();
	FindAudioComponent();
	
	

	//this sets the actor that opens to the default pawn/the default player in unreal.
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the ActorThatOpens enters the trigger volume(PressurePlate) open the door SA
	if (TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		//logs the time when the player enters the tigger volume SA
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{	//if the current time - the DoorLastOpened time is greater than the DoorCloseDelay close the door. SA
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	/*
	//if the ActorThatOpens enters the trigger volume(PressurePlate) open the door SA
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		//logs the time when the player enters the tigger volume SA
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{	//if the current time - the DoorLastOpened time is greater than the DoorCloseDelay close the door. SA
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	*/
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	//log current yaw SA
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("The Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	
	
	
	bClosedDoorSound = false;
	if (!AudioComponent) { return; }
	if (bOpenDoorSound)
	{
		AudioComponent->Play();
		bOpenDoorSound = false;
	}
	
	


	//the below code is a better way of doing this. SA
	/*
	//the below code is a better way of doing this.
	//--------------------------------------------------------------------------------------------------------------------------------------------
	get current Yaw
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;

	set Yaw rotation
	TargetYaw is declared and intilized in the header file
	FRotator OpenDoor(0.f, TargetYaw, 0.f);
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2); the last paramater is speed 
	GetOwner()->SetActorRotation(OpenDoor);
	//-------------------------------------------------------------------------------------------------------------------------------------------
	*/	
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	
	//---------------------------------------------------------
	bOpenDoorSound = false;
	if (!AudioComponent) { return; }
	if (!bClosedDoorSound)
	{
		AudioComponent->Play();
		bClosedDoorSound = true;
	}
	
	//------------------------------------------------------------
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	//find all overlaping actors 
	TArray<AActor*>OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OverlappingActors);

	//add their masses 
	for (AActor* Actor: OverlappingActors) {

		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the PressurePlate/TriggerVolume"), *Actor->GetName());
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent() 
{
	
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing an audio component"), *GetOwner()->GetName())
	}
}

void UOpenDoor::FindPresurePlate()
{
	//this prevents crash and logs when the OpenDoor Component is attached to an actor but has no trigger volume/PressurePlate set. SA 
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Object %s, Has the OpenDoor Component but does not have a PressurePlate set. "), *GetOwner()->GetName())
	}

}