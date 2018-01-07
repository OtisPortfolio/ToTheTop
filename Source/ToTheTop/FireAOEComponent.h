// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AbilityComponent.h"
#include "FireAoeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOTHETOP_API UFireAoeComponent : public UAbilityComponent
{
	GENERATED_BODY()

	/** Attack Sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackSphere;
public:	
	// Sets default values for this component's properties
	UFireAoeComponent();
	/** Returns Attack Sphere **/
	FORCEINLINE class USphereComponent* GetAttackSphere() const { return AttackSphere; }

 	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void Execute() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

 
	
};
