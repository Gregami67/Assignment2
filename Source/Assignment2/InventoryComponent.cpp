// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "PickupActor.h"
#include "MyPlayer.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddToInventory(APickupActor* pickup)
{
	Inventory.AddUnique(pickup); // Prob remove these.
	pickup->Disable();
	EquipNewInventoryItem(pickup);
}

void UInventoryComponent::EquipNewInventoryItem(APickupActor* NewItem)
{
	if (NewItem)
	{
		NewItem->Enable();
		AMyPlayer* OwningActor = Cast<AMyPlayer>(GetOwner());
		NewItem->AttachToComponent(OwningActor->StaticMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
	}
}

