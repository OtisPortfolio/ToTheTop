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

		/** Attack Sphere */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* AttackSphere;
public:
	// Sets default values for this component's properties
	UHealSelfComponent();
	/** Returns Attack Sphere **/
	FORCEINLINE class USphereComponent* GetAttackSphere() const { return AttackSphere; }

	//Heals the character
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void Execute() override;

protected:
 
	//how much the healing spell will heal character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities", Meta = (BlueprintProtected = "true"))
		int healIncrement;

 
};
