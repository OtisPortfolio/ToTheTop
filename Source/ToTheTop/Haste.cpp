// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "Haste.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AHaste::AHaste()
{
	bIsOnCooldown = false;
	cooldown = 10;
	cooldownRemaining = cooldown;
	activatedTime = 5;


}
void AHaste::BeginPlay()
{
	Super::BeginPlay();

	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;

		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability3", IE_Released, this, &AHaste::Execute);
		}
	}
}

void AHaste::Tick(float deltaTime)
{
	if (bIsOnCooldown)
	{
		cooldownRemaining = GetWorldTimerManager().GetTimerRemaining(cooldownTimer);
	}
}

void AHaste::Execute()
{
	if (!bIsOnCooldown)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;
			character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed * 2;
			
			character->GetWorldTimerManager().SetTimer(activationTimer, this, &AHaste::ResetHaste, activatedTime, false);
		}

	}
}


void AHaste::ResetHaste()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		bIsOnCooldown = true;

 		character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed;
		character->GetWorldTimerManager().SetTimer(cooldownTimer, [&]() {cooldownRemaining = cooldown; bIsOnCooldown = false; }, cooldown, false);
		
	}

}

