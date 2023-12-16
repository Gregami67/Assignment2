// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "WeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT2_API AWeaponActor : public APickupActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		float FireRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int CurrentAmmo;
	UPROPERTY(EditAnywhere, Category = Projectile)
		class TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UArrowComponent* Muzzle;
	AWeaponActor();
	void Equip(class AMyPlayer* Character, bool isBlue);
	void UnEquip();
	UFUNCTION()
		void Fire();
	FVector GetMuzzleLocation() const;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SpawnProjectile();
	bool isRight;
};
