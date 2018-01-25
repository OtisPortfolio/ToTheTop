// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Ability.generated.h"

UCLASS(ClassGroup = (Custom), abstract)
class TOTHETOP_API UAbility : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbility() : cooldown(15.0f), cooldownRemaining(cooldown), activatedTime(5.0f), bIsOnCooldown(false)
	{
		PrimaryComponentTick.bCanEverTick = true;
	}

	UFUNCTION(BlueprintCallable, Category = "Ability")
		virtual void Execute() { check(0); };
	UFUNCTION(BlueprintCallable, Category = "Ability")
		float GetCooldown() const { return cooldown; }
	UFUNCTION(BlueprintCallable, Category = "Ability")
		float GetCooldownRemaining() const { return cooldownRemaining; }

	UFUNCTION(BlueprintCallable, Category = "Ability")
		float GetAcivatedTime() const { return activatedTime; }

	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool IsOnCooldown() const { return bIsOnCooldown; }

protected:
	UPROPERTY(visibleAnywhere, Category = "Ability")
		float cooldown;
	UPROPERTY(visibleAnywhere, Category = "Ability")
		float cooldownRemaining;

	UPROPERTY(visibleAnywhere, Category = "Ability")
		float activatedTime;

	UPROPERTY(visibleAnywhere, Category = "Ability")
		bool bIsOnCooldown;

};

 
