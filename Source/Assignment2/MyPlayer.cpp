// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PickupActor.h"
#include "WeaponActor.h"
#include "MyAI.h"
#include "MyGameStateBase.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AMyPlayer::OnHit);
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(SceneComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (HealthBar) {
		UUserWidget* HealthBarWidget = CreateWidget<UUserWidget>(GetWorld(), HealthBar);
		HealthBarWidget->AddToViewport();
		HealthBarProgress = Cast<UProgressBar>(HealthBarWidget->GetWidgetFromName("HealthBar"));
		HealthBarProgress->SetPercent(1.0f);
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller) {
		FRotator Rotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		FVector Direction = FVector::ZeroVector;
		if (MoveForwardAmount != 0.0) {
			Direction = GetActorLocation() + FRotationMatrix(Rotation).GetUnitAxis(EAxis::X) * MoveForwardAmount * Velocity * DeltaTime;
			SetActorLocation(Direction);
		}

		if (MoveRightAmount != 0.0) {
			Direction = GetActorLocation() + FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y) * MoveRightAmount * Velocity * DeltaTime;
			SetActorLocation(Direction);
		}
		SetActorRotation(FRotator(0.0f, GetControlRotation().Yaw, GetControlRotation().Roll));
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent) {
		PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
		// PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
		// PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AMyPlayer::PickupWeapon);
		PlayerInputComponent->BindAction("LeftShoot", IE_Pressed, this, &AMyPlayer::LeftShoot);
		PlayerInputComponent->BindAction("RightShoot", IE_Pressed, this, &AMyPlayer::RightShoot);
	}
}

void AMyPlayer::MoveForward(float Amount)
{
	MoveForwardAmount = Amount;
}

void AMyPlayer::MoveRight(float Amount)
{
	MoveRightAmount = Amount;
}

void AMyPlayer::PickupWeapon()
{
	TArray<AActor*> overlappingActors;
	StaticMeshComponent->GetOverlappingActors(overlappingActors);
	for (AActor* overlappingActor : overlappingActors)
	{
		if (overlappingActor->Tags.Contains(FName("Red")))
		{
			LeftWeapon = Cast<AWeaponActor>(overlappingActor);
			LeftWeapon->Equip(this, true);
			LeftWeapon->Tags.Add("RedKiller");
		}
		if (overlappingActor->Tags.Contains(FName("Blue")))
		{
			RightWeapon = Cast<AWeaponActor>(overlappingActor);
			RightWeapon->Equip(this, false);
			RightWeapon->Tags.Add("BlueKiller");

		}
	}
}

void AMyPlayer::LeftShoot()
{
	if (LeftWeapon)
	{
		//Fire the CurrentWeapon
		LeftWeapon->Fire();
		UE_LOG(LogTemp, Warning, TEXT("Left Shoot"));
	}
}

void AMyPlayer::RightShoot()
{
	if (RightWeapon)
	{
		//Fire the CurrentWeapon
		RightWeapon->Fire();
		UE_LOG(LogTemp, Warning, TEXT("Right Shoot"));
	}
}

void AMyPlayer::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>();
	AMyAI* AI = Cast<AMyAI>(OtherActor);
	if (AI) {
		GameState->PlayerHealth -= 0.07f * GetWorld()->DeltaTimeSeconds;
		HealthBarProgress->SetPercent(GameState->PlayerHealth);
		if (GameState->PlayerHealth <= 0.0f) {
			GameState->PlayerHealth = 0.0f;
			GameState->PromptEndGame();
			this->Destroy();
		}
	}
}