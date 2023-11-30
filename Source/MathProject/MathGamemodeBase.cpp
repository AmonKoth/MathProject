// Fill out your copyright notice in the Description page of Project Settings.


#include "MathGamemodeBase.h"

void AMathGamemodeBase::addToList(AActor* actor)
{
	actorList.Add(actor);
}

TArray<AActor*> AMathGamemodeBase::getTheList()
{
	return actorList;
}
