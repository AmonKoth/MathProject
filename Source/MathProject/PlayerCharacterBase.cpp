// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BouncingBallBase.h"
#include "PlayerCharacterBase.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(RootComponent);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(cameraComponent);

	movementComponent = FindComponentByClass<UCharacterMovementComponent>();
	
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacterBase::fire()
{
	FVector ProjectileSpawnPointLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = projectileSpawnPoint->GetComponentRotation();

	if (ballClass && !bFired)
	{
		ABouncingBallBase* ball = GetWorld()->SpawnActor<ABouncingBallBase>(ballClass, ProjectileSpawnPointLocation, ProjectileRotation);
		ball->SetOwner(this);
		ball->setVelocity(projectileSpawnPoint->GetForwardVector() * 4000);
		bFired = true;
	}

}


// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCharacterBase::fire);

}

