// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "BouncingBallBase.h"

// Sets default values
ABouncingBallBase::ABouncingBallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = ballMesh;

	ballMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BallMovement"));
	ballMovement->InitialSpeed = 0.0f; // The ball starts at rest
	ballMovement->bShouldBounce = true;

	friction = 0.98f;

	ballMesh->OnComponentHit.AddDynamic(this, &ABouncingBallBase::OnHit);
}

// Called when the game starts or when spawned
void ABouncingBallBase::BeginPlay()
{
	Super::BeginPlay();
	previousVelocity = ballMovement->Velocity;
}

// Called every frame
void ABouncingBallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	previousVelocity = ballMovement->Velocity;

	ballMovement->Velocity *= friction;
}

void ABouncingBallBase::setVelocity(FVector value)
{
	ballMovement->Velocity = value;
}

void ABouncingBallBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (previousVelocity.Length() <= 10)
	{
		Destroy();
	}

	if (OtherActor != GetOwner())
	{
		float proj = FVector::DotProduct(Hit.Normal, previousVelocity);
		ballMovement->Velocity = previousVelocity - 2 * proj * Hit.Normal;
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddForce((previousVelocity - proj * Hit.Normal) * 10000);
		}
	}
}

