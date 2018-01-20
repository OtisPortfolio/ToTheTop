// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
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
UCLASS( ClassGroup=(Custom) )
class TOTHETOP_API UAbilityManagerComponent : public USceneComponent
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Manager", meta = (AllowPrivateAccess = "true"))
		int maxAbilitySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|Manager", meta = (AllowPrivateAccess = "true"))
		int currentNumberOfAbilities;


	std::vector<class UAbility*> characterAbilities;
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
		void RemoveAbility(EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		bool HasAbility(EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		UAbility* const GetAbility(EAbilities ability) const;


	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		UAbility* const GetAbilityBySlot(int slotNum) const;

};
