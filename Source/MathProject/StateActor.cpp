// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "MathGamemodeBase.h"
#include "StateActor.h"

// Sets default values
AStateActor::AStateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStateActor::BeginPlay()
{
	Super::BeginPlay();
	player = UGameplayStatics::GetPlayerPawn(this, 0);

	gameMode = Cast<AMathGamemodeBase>(UGameplayStatics::GetGameMode(this));

	if (gameMode)
	{
		gameMode->addToList(this);
	}
	actorsToIgnore.Add(GetOwner());
}

// Called every frame
void AStateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	checkupYourFriends();
	handleState(DeltaTime);

}

void AStateActor::handleState(float DeltaTime)
{
	if (player == nullptr)
	{
		return;
	}

	FVector playerLocation = player->GetActorLocation();
	FVector actorLocation = this->GetActorLocation();

	FVector directionToPlayer = playerLocation - actorLocation;
	directionToPlayer.Normalize();

	float dot = FVector::DotProduct(directionToPlayer, this->GetActorForwardVector());
	float angleInRadians = FMath::Acos(dot);
	float angleInDegrees = FMath::RadiansToDegrees(angleInRadians);


	if (angleInDegrees < detectAngle)
	{
		if (bIsSuspicious == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("HUH?!!!"));
			bIsSuspicious = true;
		}
		if (currentDetection >= maxDetection)
		{
			if (bIsDetected == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("OIOI YOU THERE!"));
				bIsDetected = true;
			}
			currentDetection = maxDetection;
		}

		if (currentDetection < maxDetection)
		{
			currentDetection += (detectionRate * DeltaTime * 10);
		}

	}
	else
	{
		bIsDetected = false;
		if (currentDetection > 0)
		{
			currentDetection -= (detectionRate * DeltaTime * 10);
		}
		if (currentDetection <= 0)
		{
			currentDetection = 0;
			bIsDetected = false;
			if (bIsSuspicious)
			{
				UE_LOG(LogTemp, Warning, TEXT("Must have been the wind!."));
				bIsSuspicious = false;
			}
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("current detection %f?!!!"),currentDetection);

	if (angleInDegrees > killAngle && FVector::Distance(playerLocation, actorLocation) < killDistance && 
		bIsBeingWatched == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Insert Mount and blade DEATH sound here"));

	}

	bIsBeingWatched = false;
}

void AStateActor::iSeeYou()
{
	bIsBeingWatched = true;
}

void AStateActor::checkupYourFriends()
{
	if (!gameMode) return;
	TArray<AActor*> friendList;

	friendList = gameMode->getTheList();

	FHitResult hit;
	//I'm not your friend buddy!!??
	for (AActor* buddy : friendList)
	{
		if (buddy == this) continue;
	
		FVector actorLocation = this->GetActorLocation();
		FVector friendLocation = buddy->GetActorLocation();
		
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), actorLocation, friendLocation, ETraceTypeQuery::TraceTypeQuery1,
			true, actorsToIgnore, EDrawDebugTrace::ForOneFrame, hit ,true);
		AStateActor* guy;
		if (hit.bBlockingHit && IsValid(hit.GetActor()))
		{
			if (Cast<AStateActor>(hit.GetActor()))
			{
				guy = Cast<AStateActor>(hit.GetActor());
				guy->iSeeYou();
			}
		}
	}

}

