// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.h"
#include "FireAOE.generated.h"

UCLASS(ClassGroup = (Custom))
class TOTHETOP_API UFireAOE : public UAbility
{
	GENERATED_BODY()

	/** Attack Sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|FireAoe", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackSphere;
public:

	friend class UAbilityManagerComponent;

	virtual void BeginPlay() override;

	/** Returns Attack Sphere **/
	FORCEINLINE class USphereComponent* GetAttackSphere() const { return AttackSphere; }

	UFUNCTION(BlueprintCallable, Category = "Ability|FireAoe")
		void Execute() override {};

	private:
		UFireAOE();

};
