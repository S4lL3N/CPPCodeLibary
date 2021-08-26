// Copyright Shae Allen 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_GAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	//for all the actors in the trigger volume/ pressure plate
	float TotalMassOfActors() const;

	void FindAudioComponent() ;
	void FindPresurePlate();

	bool bOpenDoorSound = false;
	bool bClosedDoorSound = true;

private:
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)//allows for this value to be changed in the UE4 editor SA
	//the angle of the door open
	float TargetYaw = 90.f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
