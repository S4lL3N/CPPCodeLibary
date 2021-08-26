// Copyright Shae Allen 2020.

#include "Grabber.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



//user defined macro for "out" parameters (meaning they will be changed) needed indicate that the (OUT PlayerViewPointLocation, OUT PlayerViewPointRotation) variables are out --SA
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (PhysicsHandle->GrabbedComponent) 
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
	
}

//check for physics handle component 
void UGrabber::FindPhysicsHandle()
{
	//check for physics handle component 
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s"), *GetOwner()->GetName());
	}
	
}

void UGrabber::SetupInputComponent()
{
	//check for key press set in the project settings "f" and "LMB"
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Input component found on: %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component MISSING on: %s"), *GetOwner()->GetName());
	}
}

FVector UGrabber::GetPlayerWorldPos() const 
{
	//get player view point --SA
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	// draws a debug line to indicate the players reach --SA
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	return PlayerViewPointLocation;
}

FVector UGrabber::GetLineTraceEnd() const {

	//get player view point --SA
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//log to console --SA
	/*UE_LOG(LogTemp, Warning, TEXT("Location = %s, & Direction = %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);*/


	// draws a debug line to indicate the players reach --SA
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/*
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5
	);

	*/
	//Documentation information for above code DrawDebugLine() --SA
	/*
	*Documentation information
	*
		#include "DrawDebugHelpers.h"

		void DrawDebugLine(

			const UWorld * InWorld,
			FVector const & LineStart,
			FVector const & LineEnd,
			FColor const & Color,
			bool bPersistentLines,
			float LifeTime,
			uint8 DepthPriority,
			float Thickness
		)
		https://docs.unrealengine.com/en-US/API/Runtime/Engine/DrawDebugLine/index.html
	*/

	return LineTraceEnd;
}

//if the key is pressed run this function.
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("grabber pressed"));
	
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation
			(
				ComponentToGrab,
				NAME_None,
				GetLineTraceEnd()
			);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Grabber Released"));
	PhysicsHandle->ReleaseComponent();

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	//Ray-cast out and see what it hits --SA
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	//Documentation for FCollisionQueryParams see above --SA
	/*Documentation for FCollisionQueryParams
	#include "CollisionQueryParams.h"

	FCollisionQueryParams
	(
		FName InTraceTag,
		bool bInTraceComplex,
		const AActor * InIgnoreActor
	)
	https://docs.unrealengine.com/en-US/API/Runtime/Engine/FCollisionQueryParams/index.html
	*/

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPos(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//Documentation for ineTraceSingleByObjectType see above
	/*/Documentation for ineTraceSingleByObjectType see above --SA
			#include "Engine/World.h"

		bool LineTraceSingleByObjectType
		(
			struct FHitResult & OutHit,
			const FVector & Start,
			const FVector & End,
			const FCollisionObjectQueryParams & ObjectQueryParams,
			const FCollisionQueryParams & Params
		) const
		https://docs.unrealengine.com/en-US/API/Runtime/Engine/Engine/UWorld/LineTraceSingleByObjectType/index.html
	*/

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
	}

	return Hit;
}


