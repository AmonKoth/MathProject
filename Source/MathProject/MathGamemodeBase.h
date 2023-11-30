// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MathGamemodeBase.generated.h"

/**
 * 
 */
UCLASS()
class MATHPROJECT_API AMathGamemodeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

		TArray<AActor*> actorList;

		void addToList(AActor* actor);
		TArray<AActor*> getTheList();
};
