// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.h"
#include "Haste.generated.h"

UCLASS(ClassGroup = (Custom))
class TOTHETOP_API AHaste : public AAbility
{
	GENERATED_BODY()

public:
	friend class UAbilityManagerComponent;
	//Heals the character
	UFUNCTION(BlueprintCallable, Category = "Ability|Haste")
		void Execute() override;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	void ResetHaste();

protected:

	//default walk speed for character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|Haste", Meta = (BlueprintProtected = "true"))
		float defaultWalkSpeed;

private:
	AHaste();
	FTimerHandle cooldownTimer;
	FTimerHandle activationTimer;

};
