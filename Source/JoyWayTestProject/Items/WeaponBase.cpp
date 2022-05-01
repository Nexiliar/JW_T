// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayTestProject/Items/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	RootComponent = SkeletalMeshWeapon;
	ShootLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootLocation"));
	ShootLocation->SetupAttachment(RootComponent);

	MagazineDropLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("MagazinDrop"));
	MagazineDropLocation->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::StartFire()
{
	//EWeaponType switchedType = WeaponInfo.TypeOfFire;
	switch (WeaponInfo.TypeOfFire)
	{
	case EWeaponType::Auto:
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShootTimer, this, &AWeaponBase::Fire, WeaponInfo.RateOfFire, true);
		break;
	case EWeaponType::Burst:
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_BurstTimer, this, &AWeaponBase::BurstFire,WeaponInfo.BurstSettings.BurstRate, true);
		BurstFire();
		break;
	case EWeaponType::SingleShot:
		if (CanFire)		
			Fire();				
		break;
	default:
		break;
	}

	
}

void AWeaponBase::EndFire()
{
	//Check is timer exist
	bool isTimerActive = GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_ShootTimer);
	if (isTimerActive)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ShootTimer);
	}	
}

void AWeaponBase::BurstFire()
{
	if (BurstProjectileCount < WeaponInfo.BurstSettings.NumberProjectileByShot)
	{
		BurstProjectileCount += 1;
		Fire();
	}
	else
	{
		BurstProjectileCount = 0;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_BurstTimer);
	}
}

void AWeaponBase::Fire()
{
	if (WeaponInfo.TypeOfFire == EWeaponType::SingleShot)
	{
		CanFire = false;		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_SingleShotTimer,this, &AWeaponBase::SetCanFire, WeaponInfo.RateOfFire, false);
	}
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		FVector SpawnLocation = ShootLocation->GetComponentLocation();
		FRotator SpawnRotation = ShootLocation->GetComponentRotation();
		if (WeaponInfo.CurrentRound > 0)
		{
			WeaponInfo.CurrentRound -= 1;
			AProjectile* myProjectile = Cast<AProjectile>(GetWorld()->SpawnActor(WeaponInfo.Projectile, &SpawnLocation, &SpawnRotation, SpawnParams));
			if (myProjectile)
			{
				myProjectile->InitProjectile(WeaponInfo.WeaponDamage);
			}
		}
		else
		{
			//AUTORELOAD?
		}
	
}

void AWeaponBase::SetCanFire()
{
	CanFire = true;
}

int32 AWeaponBase::ReloadEvent(int32 AvailableAmmo)
{
	int32 AmmoNeed = 0;
	if (AvailableAmmo+WeaponInfo.CurrentRound >= WeaponInfo.MaxRound)
	{		
		AmmoNeed = WeaponInfo.MaxRound - WeaponInfo.CurrentRound;
		WeaponInfo.CurrentRound = WeaponInfo.MaxRound;		
	}
	else
	{
		WeaponInfo.CurrentRound += AvailableAmmo;
		AmmoNeed = AvailableAmmo;
	}
	return AmmoNeed;
}





