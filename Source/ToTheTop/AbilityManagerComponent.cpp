// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "AbilityManagerComponent.h"


// Sets default values for this component's properties
UAbilityManagerComponent::UAbilityManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAbilityManagerComponent::AddAbility(std::unique_ptr<Ability> ability)
{
	CharacterAbilities.push_back(ability);
}

void UAbilityManagerComponent::RemoveAbility(std::unique_ptr<Ability> ability)
{
	CharacterAbilities.remove(ability);
}

// Called when the game starts
void UAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

