// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "Haste.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

UHaste::UHaste()
{
	bIsOnCooldown = false;
	cooldown = 10;
	cooldownRemaining = cooldown;
	activationLength = 5;
	bIsActivated = false;
}
void UHaste::BeginPlay()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;
	}
}

void UHaste::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (bIsOnCooldown)
	{
		cooldownRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(cooldownTimer);
	}
}

void UHaste::Execute()
{
	if (!bIsOnCooldown && !bIsActivated)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			bIsActivated = true;
			defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;
			character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed * 2;
			GetWorld()->GetTimerManager().SetTimer(activationTimer, this, &UHaste::ResetHaste, activationLength, false);
		}

	}
}


void UHaste::ResetHaste()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		bIsActivated = false;
		bIsOnCooldown = true;
 		character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed;
		GetWorld()->GetTimerManager().SetTimer(cooldownTimer, [&]() {cooldownRemaining = cooldown; bIsOnCooldown = false; }, cooldown, false);
	}

}

