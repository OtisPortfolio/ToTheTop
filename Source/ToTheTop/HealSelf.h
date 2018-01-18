// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.h"
#include "HealSelf.generated.h"

UCLASS(ClassGroup = (Custom))
class TOTHETOP_API AHealSelf : public AAbility
{
	GENERATED_BODY()


	AHealSelf();
public:
 
	friend class UAbilityManagerComponent;
	/** Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|HealSelf|ParticleEffect", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* HealParticleSystem;

	UFUNCTION(BlueprintPure, Category = "Ability|HealSelf")
		int GetHealIncrement() const { return healIncrement; }

	virtual void BeginPlay() override;

	//Heals the character
	UFUNCTION(BlueprintCallable, Category = "Ability|HealSelf")
		void Execute() override;

protected:

	//how much the healing spell will heal character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|HealSelf", Meta = (BlueprintProtected = "true"))
		int healIncrement;


};
