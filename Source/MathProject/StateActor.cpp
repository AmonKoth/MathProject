// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

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
	
}

// Called every frame
void AStateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		UE_LOG(LogTemp, Warning, TEXT("OIOI YOU THERE!"));
	}
	else if (angleInDegrees > killAngle && FVector::Distance(playerLocation,actorLocation) < killDistance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Insert Mount and blade DEATH sound here"));

	}


}

