// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.h"
#include "Leap.generated.h"

 
UCLASS()
class TOTHETOP_API ALeap : public AAbility
{
	GENERATED_BODY()
		ALeap();
	virtual void Tick(float DeltaTime) override;
	FTimerHandle cooldownTimer;
	FTimerHandle activationTimer;


public:
	friend class UAbilityManagerComponent;

	UFUNCTION(BlueprintCallable, Category = "Ability|SuperJump")
		void Execute() override;

	virtual void BeginPlay() override;
 
	void ResetSuperJump();

protected:
	//default jump velocity for character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|SuperJump", Meta = (BlueprintProtected = "true"))
		float defaultZVelocity;
 
};
