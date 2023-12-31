// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

UCLASS()
class ASSIGNMENT2_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION()
		virtual void Disable();

	UFUNCTION()
		virtual void Enable();
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USphereComponent* SphereCollision;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* StaticMeshComponent;
};
