// Copyright Roseville Studios
#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("DROPPY DROPPY"));
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
	

	
}

void UGrabber::Grab()
{

	UE_LOG(LogTemp, Warning, TEXT("GRABBY GRABBY"));

	FHitResult HitResult =  GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	

	FVector PlayerFPLocation;
	FRotator PlayerFPRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerFPLocation, OUT PlayerFPRotation);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerFPLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerFPRotation.ToString());


	FVector LineTraceEnd = PlayerFPLocation + PlayerFPRotation.Vector() * Reach;
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
	}
	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("MISSING INPUT on: %s "), *(GetOwner()->GetName()));
	}

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::FindPhysicsHandle ()
{

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{

		UE_LOG(LogTemp, Error, TEXT("MISSING PHYSICS on: %s "), *(GetOwner()->GetName()));
	}
}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerFPLocation;
	FRotator PlayerFPRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerFPLocation, OUT PlayerFPRotation);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerFPLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerFPRotation.ToString());


	FVector LineTraceEnd = PlayerFPLocation + PlayerFPRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerFPLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());


	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerFPLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	AActor* ActorHit = Hit.GetActor();


	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(ActorHit->GetName()));

	}

	return Hit;


}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerFPLocation;
	FRotator PlayerFPRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerFPLocation, OUT PlayerFPRotation);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerFPLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerFPRotation.ToString());


	FVector LineTraceEnd = PlayerFPLocation + PlayerFPRotation.Vector() * Reach;

	//GetFirstPhysicsBodyInReach();
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);

	}
	
	


	//check hit and can pick
}

