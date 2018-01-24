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
class ABaseCharacter;
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
		UAbility* const GetAbilityBySlot(int slotNum) const;
 
	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		void AddAbility(class ABaseCharacter* const baseChar, EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		void RemoveAbility(EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		bool HasAbility(EAbilities ability);

	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		UAbility* const GetAbility(EAbilities ability) const;


	UFUNCTION(BlueprintCallable, Category = "Ability|Manager")
		int GetAbilitySlotNumber(EAbilities ability) const;

	template <typename T>
	int GetAbilitySlotNumber() const
	{
		return std::distance(characterAbilities.begin(), GetAbility<T>());
	}

	template <typename T>
	FORCEINLINE void AddAbility(ABaseCharacter* const owner)
	{
		if (!HasAbility<T>())
		{
			if (currentNumberOfAbilities < maxAbilitySlots)
			{
				UAbility* ability = NewObject<T>(owner);
				if (ability != nullptr)
				{
					ability->RegisterComponent();
					ability->AttachToComponent(owner->GetAbilityManager(), FAttachmentTransformRules::KeepWorldTransform);
					characterAbilities.push_back(ability);
					currentNumberOfAbilities++;
				}
			}
		}

	}

	template <typename T>
	FORCEINLINE void RemoveAbility()
	{
		if (currentNumberOfAbilities > 0)
		{
			std::vector<UAbility*>::iterator abilityActor;
			//find the actor that matches the ability being removed
			for (auto itr = characterAbilities.begin(); abilityActor < characterAbilities.end(); ++itr)
			{
				if (Cast<T>(*itr))
				{
					T* ability = Cast<T>(*itr);
					abilityActor = itr;
					break;
				}
			}
			if (abilityActor != characterAbilities.end())
			{
				(*abilityActor)->DestroyComponent();
				delete &(*abilityActor);
				currentNumberOfAbilities--;
			}
		}
	}
	template <typename T>
	FORCEINLINE bool HasAbility()
	{
		if (currentNumberOfAbilities > 0)
		{
			//find the actor that matches the ability being removed
			for (auto itr = characterAbilities.begin(); itr < characterAbilities.end(); ++itr)
			{
				if (Cast<T>(*itr))
				{
					return true;
				}
			}
		}
		return false;
	}
	template <typename T>
	FORCEINLINE UAbility* const GetAbility() const
	{
		if (currentNumberOfAbilities > 0)
		{
			//find the actor that matches the ability being removed
			for (auto itr = characterAbilities.begin(); itr < characterAbilities.end(); ++itr)
			{
				if (Cast<T>(*itr))
				{
					T* ability = Cast<T>(*itr);
					return *itr;
				}
			}
			return nullptr;
		}
		return nullptr;
	}
};
