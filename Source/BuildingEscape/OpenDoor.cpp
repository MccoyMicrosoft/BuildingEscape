// Copyright Roseville Studios


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts GetOwner is the component im on!!
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	ClosedYaw = CurrentYaw;
	TargetYaw = CurrentYaw - TargetYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no plate assigned !!"), *GetOwner()->GetName());
	}
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{

	//UE_LOG(LogTemp,Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp,Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	// This is liner and is framerate dependent
		//GetOwner()->SetActorRotation(FMath::Lerp(GetOwner()->GetActorRotation(), FRotator(0.0f, TargetYaw, 0.0f), .01f));

		//This is better and not framerate dependent 
		FRotator OpenDoorRot(0.f, TargetYaw, 0.f);
	//OpenDoor.Yaw= FMath::FInterpConstantTo(GetOwner()->GetActorRotation().Yaw,TargetYaw, DeltaTime, 45);
	//This one has easing, and will slow at the end.. neat 
	OpenDoorRot.Yaw = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw, TargetYaw, DeltaTime,DoorOpenSpeed);
	GetOwner()->SetActorRotation(OpenDoorRot);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{

	//UE_LOG(LogTemp,Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp,Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	// This is liner and is framerate dependent
		//GetOwner()->SetActorRotation(FMath::Lerp(GetOwner()->GetActorRotation(), FRotator(0.0f, TargetYaw, 0.0f), .01f));

		//This is better and not framerate dependent 
	FRotator OpenDoorRot(0.f, ClosedYaw, 0.f);
	//OpenDoor.Yaw= FMath::FInterpConstantTo(GetOwner()->GetActorRotation().Yaw,TargetYaw, DeltaTime, 45);
	//This one has easing, and will slow at the end.. neat 
	OpenDoorRot.Yaw = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw, ClosedYaw, DeltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRotation(OpenDoorRot);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//The first pressurePlate check is doing a null check
	if (PressurePlate)
	{
	
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if(LastOpenTime + DoorDelay <= GetWorld()->GetTimeSeconds())
	{
		CloseDoor(DeltaTime);
	}

	
}
	
	
}

