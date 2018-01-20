// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "AbilityManagerComponent.h"
#include "BaseCharacter.h"
#include "Ability.h"
#include "Leap.h"
#include "Haste.h"
#include "FireAOE.h"
#include "HealSelf.h"




UAbilityManagerComponent::UAbilityManagerComponent()
	: maxAbilitySlots(3), currentNumberOfAbilities(0)
{
}


int UAbilityManagerComponent::GetMaxAbilitySlots() const
{
	return maxAbilitySlots;
}

int UAbilityManagerComponent::GetCurrentNumberOfAbilities() const
{
	return currentNumberOfAbilities;
}

void UAbilityManagerComponent::AddAbility(class ABaseCharacter* const owner, EAbilities Eability)
{
	if (!HasAbility(Eability))
	{
		if (currentNumberOfAbilities < maxAbilitySlots)
		{
			UAbility* ability = nullptr;
 
			switch (Eability)
			{
			case EAbilities::EFireAOE:
				ability = NewObject<UFireAOE>(owner);
				break;
			case EAbilities::EHaste:
				ability = NewObject<UHaste>(owner);
				break;
			case EAbilities::EHeal:
				ability = NewObject<UHealSelf>(owner);
				break;
			case EAbilities::ELeap:
				ability = NewObject<ULeap>(owner);
				break;
			}
			if (ability != nullptr)
			{
				ability->AttachToComponent(owner->GetAbilityManager(), FAttachmentTransformRules::KeepWorldTransform);
				characterAbilities.push_back(ability);
				currentNumberOfAbilities++;
			}
		}
	}

}


void UAbilityManagerComponent::RemoveAbility(EAbilities ability)
{
	if (currentNumberOfAbilities > 0)
	{

		std::vector<UAbility*>::iterator abilityActor;

		//find the actor that matches the ability being removed
		for (auto itr = characterAbilities.begin(); abilityActor < characterAbilities.end(); ++itr)
		{

			if (ability == EAbilities::EFireAOE)
			{
				UFireAOE* fireAoe = Cast<UFireAOE>(*itr);
				if (fireAoe)
				{
					abilityActor = itr;
					break;
				}
			}
			else if (ability == EAbilities::EHaste)
			{

				UHaste* haste = Cast<UHaste>(*itr);
				if (haste)
				{
					abilityActor = itr;
					break;
				}
			}
			else if (ability == EAbilities::EHeal)
			{
				UHealSelf* healSelf = Cast<UHealSelf>(*itr);
				if (healSelf)
				{
					abilityActor = itr;
					break;
				}

			}
			else if (ability == EAbilities::ELeap)
			{

				ULeap* leap = Cast<ULeap>(*itr);
				if (leap)
				{
					abilityActor = itr;
					break;
				}
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

bool UAbilityManagerComponent::HasAbility(EAbilities ability)
{
	if (currentNumberOfAbilities > 0)
	{
		//find the actor that matches the ability being removed
		for (auto itr = characterAbilities.begin(); itr < characterAbilities.end(); ++itr)
		{

			if (ability == EAbilities::EFireAOE)
			{
				UFireAOE* fireAoe = Cast<UFireAOE>(*itr);
				if (fireAoe)
				{
					return true;
				}
			}
			else if (ability == EAbilities::EHaste)
			{

				UHaste* haste = Cast<UHaste>(*itr);
				if (haste)
				{
					return true;
				}
			}
			else if (ability == EAbilities::EHeal)
			{
				UHealSelf* healSelf = Cast<UHealSelf>(*itr);
				if (healSelf)
				{
					return true;
				}

			}
			else if (ability == EAbilities::ELeap)
			{

				ULeap* leap = Cast<ULeap>(*itr);
				if (leap)
				{
					return true;
				}
			}

		}
		return false;

	}
	return false;

}

UAbility* const UAbilityManagerComponent::GetAbility(EAbilities ability) const
{
	if (currentNumberOfAbilities > 0)
	{


		//find the actor that matches the ability being removed
		for (auto itr = characterAbilities.begin(); itr < characterAbilities.end(); ++itr)
		{

			if (ability == EAbilities::EFireAOE)
			{
				UFireAOE* fireAoe = Cast<UFireAOE>(*itr);
				if (fireAoe)
				{
					return *itr;
				}
			}
			else if (ability == EAbilities::EHaste)
			{

				UHaste* haste = Cast<UHaste>(*itr);
				if (haste)
				{
					return *itr;
				}
			}
			else if (ability == EAbilities::EHeal)
			{
				UHealSelf* healSelf = Cast<UHealSelf>(*itr);
				if (healSelf)
				{
					return *itr;
				}

			}
			else if (ability == EAbilities::ELeap)
			{

				ULeap* leap = Cast<ULeap>(*itr);
				if (leap)
				{
					return *itr;
				}
			}

		}
		return nullptr;

	}
	return nullptr;
}

UAbility* const UAbilityManagerComponent::GetAbilityBySlot(int slotNum) const
{
	return characterAbilities[slotNum];
}

