// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString MyName = GetOwner()->GetName();
	//FString LogText = TEXT("Test");
	//FString* PtrLog = &LogText;
	//LogText.Len(); //Way to get here for a reference normal varible
	//PtrLog->Len(); //Way to get to the dot stuff for a pointer 

	UE_LOG(LogTemp, Warning,TEXT("%s"), *MyName);
	

	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjectPosition);

	//UE_LOG(LogTemp, Error, TEXT("ERROR!!"));
	//UE_LOG(LogTemp, Display, TEXT("Nothin to see here"));

	// ...
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

