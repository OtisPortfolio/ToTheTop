// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "FireAoeComponent.h"
#include "BaseCharacter.h"
#include "Classes/Components/SphereComponent.h"

// Sets default values for this component's properties
UFireAoeComponent::UFireAoeComponent()
{
 
	abilityCooldown = 0;
	activatedTime = 0;

 	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	AttackSphere->AttachTo(this);
	AttackSphere->SetSphereRadius(50.f);
 
}
void UFireAoeComponent::BeginPlay()
{
	Super::BeginPlay();

	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{	
		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability1", IE_Released, this, &UFireAoeComponent::Execute);
		}
	}
}
void UFireAoeComponent::Execute()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if(character)
	{
		//get all overlapping actors and store in an array
		TArray<AActor*> CollectedActors;
		GetAttackSphere()->GetOverlappingActors(CollectedActors);
		character->SetHealth(character->GetHealth());
		//for each actor collision
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
		{
			//cast the actor to
			ABaseCharacter* const baseCharacter = Cast<ABaseCharacter>(CollectedActors[iCollected]);
			//if the cast is successful
			if (baseCharacter && baseCharacter != character)
			{
				//call set Health
				baseCharacter->AddHealth(-character->GetAttackPower());
			}

		}
	}


}
 


 

