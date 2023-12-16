// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 *
 */
UCLASS()
class ASSIGNMENT2_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = "HUD")
        int32 RedAmmoX;
    UPROPERTY(EditAnywhere, Category = "HUD")
        int32 RedAmmoY;
    UPROPERTY(EditAnywhere, Category = "HUD")
        float RedAmmoScale;
    UPROPERTY(EditAnywhere, Category = "HUD")
        int32 BlueAmmoX;
    UPROPERTY(EditAnywhere, Category = "HUD")
        int32 BlueAmmoY;
    UPROPERTY(EditAnywhere, Category = "HUD")
        float BlueAmmoScale;
    virtual void DrawHUD() override;
};