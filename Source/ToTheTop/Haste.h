// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.h"
#include "Haste.generated.h"

UCLASS(ClassGroup = (Custom))
class TOTHETOP_API UHaste : public UAbility
{
	GENERATED_BODY()

public:
	friend class UAbilityManagerComponent;
	//Heals the character
		void Execute() override;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void ResetHaste();

protected:

	//default walk speed for character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|Haste", Meta = (BlueprintProtected = "true"))
		float defaultWalkSpeed;

private:
	UHaste();
	FTimerHandle cooldownTimer;
	FTimerHandle activationTimer;

};
