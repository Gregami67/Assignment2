// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAISpawner.h"
#include "MyAI.h"

// Sets default values
AMyAISpawner::AMyAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AMyAISpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	intervalEachSpawn += DeltaTime;
	if (intervalEachSpawn >= 7.0f)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		float rndStuff = FMath::FRandRange(-20, 20);
		float rndStuff2 = FMath::FRandRange(-20, 20);
		FVector stuff = GetActorLocation() + FVector(rndStuff, rndStuff2, 0.0f);
		GetWorld()->SpawnActor<AMyAI>(AIPlayer, stuff, FRotator::ZeroRotator, Params);
		intervalEachSpawn = 0.0f;
	}
}

