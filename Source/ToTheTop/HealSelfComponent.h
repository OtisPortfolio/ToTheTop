// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "HealSelfComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOTHETOP_API UHealSelfComponent : public UAbilityComponent
{
	GENERATED_BODY()

	/** Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|HealSelf|ParticleEffect", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* HealParticleSystem;
public:
	// Sets default values for this component's properties
	UHealSelfComponent();
 
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
