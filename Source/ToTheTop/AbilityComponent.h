// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), abstract)
class TOTHETOP_API UAbilityComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent()  : abilityCooldown(15.0f), activatedTime(5.0f), bisOnCooldown(false) {}

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Execute() { check(0 && "You must override this"); };

 
protected:
	UPROPERTY(visibleAnywhere, Category="Ability")
	float abilityCooldown;

	UPROPERTY(visibleAnywhere, Category = "Ability")
	float activatedTime;

	UPROPERTY(visibleAnywhere, Category = "Ability")
	bool bisOnCooldown;
	
};
