// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyAISpawner.generated.h"

UCLASS()
class ASSIGNMENT2_API AMyAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	float intervalEachSpawn = 0;
	UPROPERTY(EditAnywhere, Category = "Setup")
		class TSubclassOf<class AMyAI> AIPlayer;
};
