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

void UAbilityManagerComponent::AddAbility(class ABaseCharacter* const owner, EAbilities ability)
{
	if (!HasAbility(ability))
	{
		if (currentNumberOfAbilities < maxAbilitySlots)
		{
			AAbility* abilityActor = nullptr;
			FVector Location = owner->GetActorLocation();
			FRotator Rotation = owner->GetActorRotation();
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Owner = owner;

			switch (ability)
			{
			case EAbilities::EFireAOE:
				abilityActor = GetWorld()->SpawnActor<AFireAOE>(Location, Rotation, SpawnInfo);
 				break;
			case EAbilities::EHaste:
				abilityActor = GetWorld()->SpawnActor<AHaste>(Location, Rotation, SpawnInfo);
				break;
			case EAbilities::EHeal:
				abilityActor = GetWorld()->SpawnActor<AHealSelf>(Location, Rotation, SpawnInfo);
				break;
			case EAbilities::ELeap:
				abilityActor = GetWorld()->SpawnActor<ALeap>(Location, Rotation, SpawnInfo);
				break;
			}
			if (abilityActor != nullptr)
			{
	 
				abilityActor->AttachToComponent(owner->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
				characterAbilities.push_back(abilityActor);
				currentNumberOfAbilities++;
			}
		}
	}

}
 

void UAbilityManagerComponent::RemoveAbility(EAbilities ability)
{
	if (currentNumberOfAbilities > 0)
	{
		
		std::vector<AAbility*>::iterator abilityActor;

		//find the actor that matches the ability being removed
		for (auto itr = characterAbilities.begin(); abilityActor < characterAbilities.end(); ++itr)
		{
 
			if(ability ==  EAbilities::EFireAOE)
			{
				AFireAOE* fireAoe = Cast<AFireAOE>(*itr);
				if (fireAoe)
				{
					abilityActor = itr;
					break;
				}
			}
			else if (ability == EAbilities::EHaste)
			{

				AHaste* haste = Cast<AHaste>(*itr);
				if (haste)
				{
					abilityActor = itr;
					break;
				}
			}
			else if (ability == EAbilities::EHeal)
			{
				AHealSelf* healSelf = Cast<AHealSelf>(*itr);
				if (healSelf)
				{
					abilityActor = itr;
					break;
				}

			}
			else if (ability == EAbilities::ELeap)
			{

				ALeap* leap = Cast<ALeap>(*itr);
				if (leap)
				{
					abilityActor = itr;
					break;
				}
			}
 
		}
		if (abilityActor != characterAbilities.end())
		{
			(*abilityActor)->Destroy();
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
				AFireAOE* fireAoe = Cast<AFireAOE>(*itr);
				if (fireAoe)
				{
					return true;
				}
			}
			else if (ability == EAbilities::EHaste)
			{

				AHaste* haste = Cast<AHaste>(*itr);
				if (haste)
				{
					return true;
				}
			}
			else if (ability == EAbilities::EHeal)
			{
				AHealSelf* healSelf = Cast<AHealSelf>(*itr);
				if (healSelf)
				{
					return true;
				}

			}
			else if (ability == EAbilities::ELeap)
			{

				ALeap* leap = Cast<ALeap>(*itr);
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

AAbility* const UAbilityManagerComponent::GetAbility(EAbilities ability) const
{
	if (currentNumberOfAbilities > 0)
	{

 
		//find the actor that matches the ability being removed
		for (auto itr = characterAbilities.begin(); itr < characterAbilities.end(); ++itr)
		{

			if (ability == EAbilities::EFireAOE)
			{
				AFireAOE* fireAoe = Cast<AFireAOE>(*itr);
				if (fireAoe)
				{
					return *itr;
				}
			}
			else if (ability == EAbilities::EHaste)
			{

				AHaste* haste = Cast<AHaste>(*itr);
				if (haste)
				{
					return *itr;
				}
			}
			else if (ability == EAbilities::EHeal)
			{
				AHealSelf* healSelf = Cast<AHealSelf>(*itr);
				if (healSelf)
				{
					return *itr;
				}

			}
			else if (ability == EAbilities::ELeap)
			{

				ALeap* leap = Cast<ALeap>(*itr);
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

AAbility* const UAbilityManagerComponent::GetAbilityBySlot(int slotNum) const
{
	return characterAbilities[slotNum];
}

