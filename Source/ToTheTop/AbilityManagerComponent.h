// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "AbilityManagerComponent.generated.h"

UENUM(BlueprintType)
enum class EAbilities : uint8
{
	ELeap,
	EHeal,
	EHaste,
	EFireAOE,
	ENone
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOTHETOP_API UAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()
private:
  
	UPROPERTY(EditAnywhere, Category = "Ability|Manager")
	int maxAbilitySlots;

	UPROPERTY(VisibleAnywhere, Category = "Ability|Manager")
	int currentNumberOfAbilities;


	std::vector<class AAbility*> characterAbilities;
 public:	
	// Sets default values for this component's properties
	UAbilityManagerComponent();
 
public:	
	UFUNCTION(BlueprintPure, Category = "Ability|Manager")
	int GetMaxAbilitySlots() const;

	UFUNCTION(BlueprintPure, Category = "Ability|Manager")
	int GetCurrentNumberOfAbilities() const;

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		void AddAbility(class ABaseCharacter* const baseChar, EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
	void RemoveAbility(EAbilities ability) ;

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		bool HasAbility(EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		AAbility* const GetAbility(EAbilities ability) const;


	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		AAbility* const GetAbilityBySlot(int slotNum) const;

};
