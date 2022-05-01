// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayTestProject/Items/Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BulletCollision"));
	RootComponent = CollisionSphere;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//Declare event to listen to overlap component
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::CollisionSphereBeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Collision sphere overlap logic
void AProjectile::CollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check whether comp exist and has simulating physics Enabled 
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(ProjectileMovement->Velocity*1.0f);
	
	}
	//Check whether actor exist and aplly damage to it
	if (OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor,BulletDamage, GetInstigatorController(),this, NULL);
	}
	Destroy();
}

void AProjectile::InitProjectile(float Damage)
{
	BulletDamage = Damage;
}

