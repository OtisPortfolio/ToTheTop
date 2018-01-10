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

AToTheTopGameModeBase::AToTheTopGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BaseCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//Seconds to complete level
	timeToCompleteLevel = 60;
	gameOver = false;

}

void AToTheTopGameModeBase::BeginPlay()
{
	//Set timer to complete level
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AToTheTopGameModeBase::Loss, timeToCompleteLevel, false);
}

 
float AToTheTopGameModeBase::GetGameTimer()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(timerHandle);
}

void AToTheTopGameModeBase::Win()
{
	gameOver = true;
}

void AToTheTopGameModeBase::Loss()
{
	ABaseCharacter* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (player)
	{
		//kill player if they did not finish in time
		player->Death();
	}
	gameOver = true;
}

bool AToTheTopGameModeBase::IsGameOver()
{
	return gameOver;
}
