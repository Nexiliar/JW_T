// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayTestProject/HostileActors/Hostile.h"

// Sets default values
AHostile::AHostile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHostile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHostile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

