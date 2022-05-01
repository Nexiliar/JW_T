// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChange, int32, ChangedAmmoValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOYWAYTESTPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FOnAmmoChange OnAmmoChange;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
		int32 AvailableAmmo = 0;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		void ChangeAmmo(int32 AmountToChange);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Action")
		int32 GetAvailableAmmo();
};
