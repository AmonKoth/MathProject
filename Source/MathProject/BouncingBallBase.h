// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncingBallBase.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class MATHPROJECT_API ABouncingBallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncingBallBase();

	virtual void Tick(float DeltaTime) override;

	void setVelocity(FVector value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ballMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ballMovement;

	UPROPERTY(EditAnywhere)
	float friction;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FVector previousVelocity;

	bool bIsSpeedStored = false;

};
