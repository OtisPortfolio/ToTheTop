// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <list>
#include <memory>
#include "Ability.h"
#include "AbilityManagerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOTHETOP_API UAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityManagerComponent();

	//void AddAbility(std::unique_ptr<Ability> ability);
	//void RemoveAbility(std::unique_ptr<Ability> ability);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	//std::list<std::unique_ptr<Ability>> CharacterAbilities;
};
