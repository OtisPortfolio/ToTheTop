// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToTheTopGameModeBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameState : uint8
{
	EPlaying,
	EGameOver,
	EWin,
	ENone
};

UCLASS()
class TOTHETOP_API AToTheTopGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AToTheTopGameModeBase();


private:

	//Handle used to get info for our game timer
	FTimerHandle timerHandle;

	EGameState currentState;


	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void SetGameState(EGameState newGameState);
	UFUNCTION(BlueprintPure, Category = "GameMode")
		EGameState GetGameState() const;
	UFUNCTION(BlueprintPure, Category = "GameMode")
		float GetGameTimer() const;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void LevelCompleted();
	UFUNCTION(BlueprintCallable, Category = "GameMode")
		void TimesUp();


protected:

	//time allowed for completing level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameMode")
		float timeToCompleteLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameMode")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* currentWidget;
};
