// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class ASSIGNMENT2_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void SetFireDirection(FVector dir);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Movement")
		class UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int MaximumSpeed = 20000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int InitialSpeed = 5000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		class USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		class UStaticMeshComponent* StaticMeshComponent;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
