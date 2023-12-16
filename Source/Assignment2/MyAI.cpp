// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAI.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyAI::AMyAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMyAI::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<AMyPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPlayer::StaticClass()));
}

// Called every frame
void AMyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (player)
	{
		FVector PlayerDirection = (player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector Location = GetActorLocation() + PlayerDirection * FVector(3.0f, 3.0f, 0.0f);
		SetActorRotation(PlayerDirection.Rotation());
		SetActorLocation(Location, true);
	}
}