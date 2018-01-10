// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "HealSelfComponent.h"
#include "BaseCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

UHealSelfComponent::UHealSelfComponent(): healIncrement(10.0f)
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_AOE_CircleHeal.P_AOE_CircleHeal"));
	HealParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HealParticleSystem"));
	if (particleAsset.Succeeded())
	{
		HealParticleSystem->SetTemplate(particleAsset.Object);
	}
	HealParticleSystem->AttachTo(this);
	HealParticleSystem->SetVisibility(false);
}
void UHealSelfComponent::BeginPlay()
{
	Super::BeginPlay();

	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());

	if (character)
	{
 
		if (character->InputComponent)
		{
			character->InputComponent->BindAction("Ability1", IE_Released, this, &UHealSelfComponent::Execute);
		}
	}
}
void UHealSelfComponent::Execute()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());
	if (character)
	{
		character->AddHealth(healIncrement);

	}

}

 

 
