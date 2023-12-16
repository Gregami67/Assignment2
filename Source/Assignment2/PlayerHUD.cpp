// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "MyGameStateBase.h"

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
	AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>();
	DrawText(FString::Printf(TEXT("Ammo Red: %d"), GameState->RedAmmo), FLinearColor::White, RedAmmoX, RedAmmoY, NULL, RedAmmoScale);
	DrawText(FString::Printf(TEXT("Ammo Blue: %d"), GameState->BlueAmmo), FLinearColor::White, BlueAmmoX, BlueAmmoY, NULL, BlueAmmoScale);
}