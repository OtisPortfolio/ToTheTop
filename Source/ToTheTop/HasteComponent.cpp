// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "HasteComponent.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

UHasteComponent::UHasteComponent()
{
	bisOnCooldown = false;
	abilityCooldown = 10;
	activatedTime = 5;


}
void UHasteComponent::BeginPlay()
{
	Super::BeginPlay();

	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;

		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability3", IE_Released, this, &UHasteComponent::Execute);
		}
	}
}
void UHasteComponent::Execute()
{
	if (!bisOnCooldown)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

		if (character)
		{
			bisOnCooldown = true;
			defaultWalkSpeed = character->GetCharacterMovement()->MaxWalkSpeed;
			character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed * 2;
			FTimerHandle UnusedHandle;
			character->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UHasteComponent::ResetHaste, activatedTime, false);
		}

	}
}

 
void UHasteComponent::ResetHaste()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
		FTimerHandle UnusedHandle;
		character->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed;
		character->GetWorldTimerManager().SetTimer(UnusedHandle, [&]() {bisOnCooldown = false; }, abilityCooldown, false);
	}

}