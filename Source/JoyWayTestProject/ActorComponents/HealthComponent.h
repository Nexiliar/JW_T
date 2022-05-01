// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float, CurrentHealth, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);


UCLASS( Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOYWAYTESTPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Health")
		FOnHealthChange OnHealthChange;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Health")
		FOnDead OnDead;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CFG")
		float MaxHealth;
	bool isDead = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void ChangeHealth(float Amount);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Info")
		float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Info")
		float GetMaxHealth();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
		bool Debug = false;
};
