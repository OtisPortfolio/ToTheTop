// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToTheTopGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOTHETOP_API AToTheTopGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AToTheTopGameModeBase();

	//Handle used to get info for our game timer
	FTimerHandle timerHandle;

	bool gameOver;


	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		float GetGameTimer();
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void Win();
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void Loss();
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		bool IsGameOver();
	//time allowed for completing level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
		float timeToCompleteLevel;
};
