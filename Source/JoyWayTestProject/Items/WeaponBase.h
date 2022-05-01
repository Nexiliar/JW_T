// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "JoyWayTestProject/Items/Projectile.h"
#include "WeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FBurstMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		int32 NumberProjectileByShot = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		float BurstRate = 0.1f;
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Auto,
	Burst,
	SingleShot
};

USTRUCT(BlueprintType)
struct FWeaponInfo 
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CFG")
		FName WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		EWeaponType TypeOfFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CFG")
		FBurstMode BurstSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CFG")
		float RateOfFire = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CFG")
		int32 MaxRound = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CFG")
		int32 CurrentRound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ")
		USoundBase* SoundFireWeapon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX ")
		UParticleSystem* EffectFireWeapon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace ")
		float WeaponDamage = 20.0f;
	//one decal on all?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitEffect ")
		UDecalComponent* DecalOnHit = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh ")
		UStaticMesh* Shell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh ")
		UStaticMesh* Magazin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory ")
		UTexture2D* WeaponIcon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
		TSubclassOf<class AProjectile> Projectile = nullptr;
};

UCLASS()
class JOYWAYTESTPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class USkeletalMeshComponent* SkeletalMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class UArrowComponent* ShootLocation = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Components)
		class UArrowComponent* MagazineDropLocation = nullptr;

	FTimerHandle TimerHandle_ShootTimer;
	FTimerHandle TimerHandle_BurstTimer;
	FTimerHandle TimerHandle_SingleShotTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
		FWeaponInfo WeaponInfo;

	bool CanFire = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable, Category = "Action")
		void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Action")
		void EndFire();
	UFUNCTION()
		void BurstFire();
	UFUNCTION()
		void Fire();
	
	void SetCanFire();
	

	UFUNCTION(BlueprintCallable, Category = "Action")
		int32 ReloadEvent(int32 AvailableAmmo);
	int32 BurstProjectileCount = 0;
};
