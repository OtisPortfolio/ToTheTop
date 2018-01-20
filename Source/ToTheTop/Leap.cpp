// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "Leap.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


ULeap::ULeap()
{
	cooldown = 10;
	cooldownRemaining = cooldown;
	activatedTime = 2;
	bIsOnCooldown = false;


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
		defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;;

		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability2", IE_Released, this, &ULeap::Execute);
		}
	}
}
 

void ULeap::Execute()
{
	if (!bIsOnCooldown)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			defaultZVelocity = character->GetCharacterMovement()->JumpZVelocity;
			character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity * 1.5;
			GetWorld()->GetTimerManager().SetTimer(activationTimer, this, &ULeap::ResetSuperJump, activatedTime, false);
		}
	}
}

void ULeap::ResetSuperJump()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		bIsOnCooldown = true;
		character->GetCharacterMovement()->JumpZVelocity = defaultZVelocity;
		GetWorld()->GetTimerManager().SetTimer(cooldownTimer, [&]() { cooldownRemaining = cooldown;  bIsOnCooldown = false; }, cooldown, false);
	}
}