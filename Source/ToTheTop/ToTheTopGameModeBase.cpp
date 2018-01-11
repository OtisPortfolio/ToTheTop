// Fill out your copyright notice in the Description page of Project Settings.

#include "ToTheTopGameModeBase.h"
#include "BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"

AToTheTopGameModeBase::AToTheTopGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;

	//Default Game State
	currentState = EGameState::ENone;
	//Seconds to complete level
	timeToCompleteLevel = 60;


}

void AToTheTopGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}
	currentState = EGameState::EPlaying;

	//Set timer to complete level
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AToTheTopGameModeBase::TimesUp, timeToCompleteLevel, false);
}

void AToTheTopGameModeBase::SetGameState(EGameState newGameState)
{
	currentState = newGameState;
}

EGameState AToTheTopGameModeBase::GetGameState() const
{
	return currentState;
}

float AToTheTopGameModeBase::GetGameTimer() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(timerHandle);
}

void AToTheTopGameModeBase::LevelCompleted()
{
	currentState = EGameState::EWin;
	ABaseCharacter* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (player)
	{
		UCharacterMovementComponent* movementComp = player->GetCharacterMovement();
		if (movementComp)
		{
			movementComp->DisableMovement();
			
			GetWorld()->GetTimerManager().PauseTimer(timerHandle);
		}
	}
}

void AToTheTopGameModeBase::TimesUp()
{
	currentState = EGameState::EGameOver;
	ABaseCharacter* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (player)
	{
		//kill player if they did not finish in time
		player->Death();
	}
 
}

