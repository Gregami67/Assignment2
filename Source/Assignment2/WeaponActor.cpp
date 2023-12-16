// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
#include "MyPlayer.h"
#include <Components/ArrowComponent.h>
#include "Projectile.h"
#include "MyGameStateBase.h"


AWeaponActor::AWeaponActor()
{
	FireRate = 10.0f;
	CurrentAmmo = 300;
	Muzzle = CreateDefaultSubobject<UArrowComponent>("Muzzle");
	Muzzle->SetupAttachment(RootComponent);
}

void AWeaponActor::Equip(AMyPlayer* Character, bool isBlue)
{
	Enable();
	SetOwner(Character);
	if (isBlue)
	{
		AttachToComponent(Character->StaticMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("RightSocket"));
	}
	else
	{
		AttachToComponent(Character->StaticMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LeftSocket"));
	}
	AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>();
	if (isBlue) {
		GameState->RedAmmo = CurrentAmmo;
	}
	else {
		GameState->BlueAmmo = CurrentAmmo;
	}
	this->isRight = isBlue;
}

void AWeaponActor::UnEquip()
{
	Disable();
	SetOwner(nullptr);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AWeaponActor::Fire()
{
	AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>();
	if (CurrentAmmo > 0)
	{
		SpawnProjectile();
	}
	if (isRight) {
		GameState->RedAmmo = CurrentAmmo;
	}
	else {
		GameState->BlueAmmo = CurrentAmmo;
	}
}

FVector AWeaponActor::GetMuzzleLocation() const
{
	return Muzzle->GetComponentToWorld().GetLocation();
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::SpawnProjectile()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ActorSpawnParams.Owner = this;
	ActorSpawnParams.Instigator = Cast<APawn>(GetOwner());
	FTransform Transform = Muzzle->GetComponentTransform();
	FVector t = Muzzle->GetForwardVector();
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Transform.GetLocation(), Transform.GetRotation().Rotator(), ActorSpawnParams);
	if (projectile != NULL)
	{
		FVector direction = FRotationMatrix(Transform.Rotator()).GetScaledAxis(EAxis::X);
		projectile->SetFireDirection(direction);
	}
	CurrentAmmo--;
}
