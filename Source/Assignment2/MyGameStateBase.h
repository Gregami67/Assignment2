// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT2_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMyGameStateBase();
	UPROPERTY(Replicated)
		float PlayerHealth;
	UPROPERTY(Replicated)
		int RedAmmo;
	UPROPERTY(Replicated)
		int BlueAmmo;
	class UUserWidget* GameOverWidgetInstance;
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UUserWidget> GameOverWidget;
	virtual void PromptEndGame();
	UFUNCTION()
	virtual void EndGame();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
