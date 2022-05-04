// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayTestProject/ActorComponents/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ChangeHealth(MaxHealth);

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ChangeHealth(float Amount)
{
	if (!isDead)
	{
		CurrentHealth += Amount;		
		if (CurrentHealth >= MaxHealth)
		{			
			CurrentHealth = MaxHealth;
		}		
		else if(CurrentHealth <=0)		
		{
			CurrentHealth = 0.0f;
			isDead = true;
			OnDead.Broadcast();			
		}
		OnHealthChange.Broadcast(CurrentHealth, Amount);
	}	
	if (Debug)
	UE_LOG(LogTemp, Warning, TEXT("HealthChangeValue:,%f"), Amount);
		
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}




