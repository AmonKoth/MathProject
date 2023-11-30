// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateActor.generated.h"

class AMathGamemodeBase;

UCLASS()
class MATHPROJECT_API AStateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStateActor();

	UPROPERTY(EditAnywhere)
	AActor* player;

	AMathGamemodeBase* gameMode;

	UPROPERTY(EditAnywhere)
	float detectAngle = 30.0f;
	UPROPERTY(EditAnywhere)
	float killDistance = 100.0f;
	UPROPERTY(EditAnywhere)
	float killAngle = 135.0f;

	UPROPERTY(EditAnywhere)
	float detectionRate = 5.0f;
	UPROPERTY(EditAnywhere)
	float maxDetection = 100.0f;

	float currentDetection = 0.0f;

	bool bIsDetected = false;
	bool bIsSuspicious = false;
	bool bIsBeingWatched = false;

	//I could not really understand this part (I can create a noisemap using shader graph though)
	float noise = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void handleState(float DeltaTime);

	void iSeeYou();

	void checkupYourFriends();

	TArray<AActor*> actorsToIgnore;
};
