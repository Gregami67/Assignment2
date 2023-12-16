// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include <Net/UnrealNetwork.h>
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "Kismet/GameplayStatics.h"


AMyGameStateBase::AMyGameStateBase()
{
	PlayerHealth = 1.0f;
	RedAmmo = 0;
	BlueAmmo = 0;
}

void AMyGameStateBase::PromptEndGame()
{
	if (!GameOverWidgetInstance) {
		GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidget);
		UButton* Button = Cast<UButton>(GameOverWidgetInstance->GetWidgetFromName("EndGame"));
		Button->OnClicked.AddDynamic(this, &AMyGameStateBase::EndGame);
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
	}
	GameOverWidgetInstance->AddToViewport();
}

void AMyGameStateBase::EndGame()
{
	FGenericPlatformMisc::RequestExit(false);

}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyGameStateBase, PlayerHealth);
	DOREPLIFETIME(AMyGameStateBase, RedAmmo);
	DOREPLIFETIME(AMyGameStateBase, BlueAmmo);
}
