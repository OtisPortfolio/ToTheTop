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
	activatedTime = 5;


}
void UHaste::BeginPlay()
{

	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;

		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability3", IE_Released, this, &UHaste::Execute);
		}
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
	if (!bIsOnCooldown)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;
			character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed * 2;
			
			GetWorld()->GetTimerManager().SetTimer(activationTimer, this, &UHaste::ResetHaste, activatedTime, false);
		}

	}
}


void UHaste::ResetHaste()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		bIsOnCooldown = true;

 		character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed;
		GetWorld()->GetTimerManager().SetTimer(cooldownTimer, [&]() {cooldownRemaining = cooldown; bIsOnCooldown = false; }, cooldown, false);
		
	}

}

