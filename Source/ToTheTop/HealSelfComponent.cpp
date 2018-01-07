// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "HealSelfComponent.h"
#include "BaseCharacter.h"



UHealSelfComponent::UHealSelfComponent(): healIncrement(10.0f)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
 
		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability2", IE_Released, this, &UHealSelfComponent::Execute);
		}
	}
}

void UHealSelfComponent::Execute()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	character->AddHealth(healIncrement);
}

 

 
