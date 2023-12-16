// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include <Components/SphereComponent.h>


// Sets default values
APickupActor::APickupActor()
{
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereCollision->SetSphereRadius(24.f);
    RootComponent = SphereCollision;
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(SphereCollision);
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereCollision->SetCollisionProfileName("OverlapAll");
    SphereCollision->SetGenerateOverlapEvents(true);
    SphereCollision->SetSimulatePhysics(false);
    // Tags.Add("Pickup");
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::Disable()
{
    if (SphereCollision)
    {
        this->SetActorHiddenInGame(true);
        SphereCollision->SetActive(false);
        SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void APickupActor::Enable()
{
    if (SphereCollision)
    {
        this->SetActorHiddenInGame(false);
        SphereCollision->SetActive(true);
        SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
}

