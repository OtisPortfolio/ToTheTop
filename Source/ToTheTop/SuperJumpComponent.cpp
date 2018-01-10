// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "SuperJumpComponent.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


USuperJumpComponent::USuperJumpComponent()
{
	abilityCooldown = 10;
	activatedTime = 2;
	bisOnCooldown = false;

 
}

void USuperJumpComponent::BeginPlay()
{
	Super::BeginPlay();
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;;

		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability2", IE_Released, this, &USuperJumpComponent::Execute);
		}
	}
}

void USuperJumpComponent::Execute()
{
	if (!bisOnCooldown)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			bisOnCooldown = true;
			defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;
			character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity * 1.5;
			FTimerHandle UnusedHandle;
			character->GetWorldTimerManager().SetTimer(UnusedHandle, this, &USuperJumpComponent::ResetSuperJump, activatedTime, false);
		}
	}
}
 
void USuperJumpComponent::ResetSuperJump()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		FTimerHandle UnusedHandle;
		character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity;
		character->GetWorldTimerManager().SetTimer(UnusedHandle, [&]() { bisOnCooldown = false; }, abilityCooldown, false);
	}
}