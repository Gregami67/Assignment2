// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetSphereRadius(4.f);
    SphereComponent->BodyInstance.SetCollisionProfileName("BlockAll");
    SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
    RootComponent = SphereComponent;
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(SphereComponent);
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->UpdatedComponent = SphereComponent;
    ProjectileMovementComponent->InitialSpeed = InitialSpeed;
    ProjectileMovementComponent->MaxSpeed = MaximumSpeed;
    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    InitialLifeSpan = 5.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetFireDirection(FVector dir)
{
    ProjectileMovementComponent->Velocity = InitialSpeed * dir;

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
        if (OtherActor != this->GetOwner())
        {
            if (OtherActor->Tags.Contains(FName("RedEnemy")))
            {
                UE_LOG(LogTemp, Warning, TEXT("Hit Red"));
                if (Tags.Contains(FName("RedKiller"))) {
                    UE_LOG(LogTemp, Warning, TEXT("Hit Red"));
                    OtherActor->Destroy();
                }
            }
            if (OtherActor->Tags.Contains(FName("BlueEnemy")))
            {
                if (Tags.Contains(FName("BlueKiller"))) {
                    UE_LOG(LogTemp, Warning, TEXT("Hit Blue"));
                    OtherActor->Destroy();
                }
            }
            Destroy();
        }
}

