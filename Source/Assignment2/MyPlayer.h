// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class ASSIGNMENT2_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditAnywhere, Category = "setup")
		USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, Category = "setup")
		UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, Category = "setup")
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, Category = "setup")
		class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, Category = "setup")
		float Velocity = 500.0f;
	UPROPERTY(VisibleAnywhere, Category = Character)
		class UInventoryComponent* InventoryComponent;
	class AWeaponActor* LeftWeapon;
	class AWeaponActor* RightWeapon;
	UPROPERTY(EditAnywhere, Category = "setup")
		TSubclassOf<class UUserWidget> HealthBar;
	class UProgressBar* HealthBarProgress = nullptr;
private:
	float MoveForwardAmount = 0;
	float MoveRightAmount = 0;
	virtual void MoveForward(float Amount);
	virtual void MoveRight(float Amount);
	virtual void PickupWeapon();
	virtual void LeftShoot();
	virtual void RightShoot();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
