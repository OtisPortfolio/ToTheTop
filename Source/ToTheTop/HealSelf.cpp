// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017
#include "HealSelf.h"
#include "BaseCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

UHealSelf::UHealSelf() : healIncrement(10.0f)
{
	cooldown = -1;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_AOE_CircleHeal.P_AOE_CircleHeal"));
	ps = particleAsset.Object;
}
void UHealSelf::BeginPlay()
{
	Super::BeginPlay();
	HealParticleSystem = NewObject<UParticleSystemComponent>(GetOwner());
	if (ps)
	{
		HealParticleSystem->SetTemplate(ps);
	}
	HealParticleSystem->SetVisibility(false);
	HealParticleSystem->RegisterComponent();
	HealParticleSystem->AttachTo(GetOwner()->GetRootComponent());

 
}
void UHealSelf::Execute()
{
	ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());
	if (character)
	{
		character->AddHealth(healIncrement);

	}

}
