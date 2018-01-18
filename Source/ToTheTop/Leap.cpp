// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "Leap.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


ALeap::ALeap()
{
	cooldown = 10;
	cooldownRemaining = cooldown;
	activatedTime = 2;
	bIsOnCooldown = false;


}

void ALeap::Tick(float DeltaTime)
{
	if (bIsOnCooldown)
	{
		cooldownRemaining = GetWorldTimerManager().GetTimerRemaining(cooldownTimer);
	}
}

void ALeap::BeginPlay()
{
	Super::BeginPlay();
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;;

		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability2", IE_Released, this, &ALeap::Execute);
		}
	}
}
 

void ALeap::Execute()
{
	if (!bIsOnCooldown)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;
			character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity * 1.5;
			character->GetWorldTimerManager().SetTimer(activationTimer, this, &ALeap::ResetSuperJump, activatedTime, false);
		}
	}
}

void ALeap::ResetSuperJump()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		bIsOnCooldown = true;
		character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity;
		character->GetWorldTimerManager().SetTimer(cooldownTimer, [&]() { cooldownRemaining = cooldown;  bIsOnCooldown = false; }, cooldown, false);
	}
}