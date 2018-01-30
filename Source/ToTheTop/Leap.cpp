// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "Leap.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


ULeap::ULeap()
{
	cooldown = 10;
	cooldownRemaining = cooldown;
	activationLength = 2;
	bIsOnCooldown = false;
	bIsActivated = false;

}

void ULeap::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{

	if (bIsOnCooldown)
	{
		cooldownRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(cooldownTimer);
	}
}

void ULeap::BeginPlay()
{
 	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;
		
	}
}
 

void ULeap::Execute()
{
	if (!bIsOnCooldown && !bIsActivated)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			bIsActivated = true;
			defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;
			character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity * 1.5;
			GetWorld()->GetTimerManager().SetTimer(activationTimer, this, &ULeap::ResetSuperJump, activationLength, false);
		}
	}
}

void ULeap::ResetSuperJump()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		bIsActivated = false;
		bIsOnCooldown = true;
		character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity;
		GetWorld()->GetTimerManager().SetTimer(cooldownTimer, [&]() { cooldownRemaining = cooldown;  bIsOnCooldown = false; }, cooldown, false);
	}
}