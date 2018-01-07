// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "AbilityComponent.h"
#include "HasteComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOTHETOP_API UHasteComponent : public UAbilityComponent
{
	GENERATED_BODY()

public:
	UHasteComponent();
	//Heals the character
	UFUNCTION(BlueprintCallable, Category = "Ability|Haste")
	void Execute() override;

	virtual void BeginPlay() override;
 	void ResetHaste();
	
protected:

	//default walk speed for character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability|Haste", Meta = (BlueprintProtected = "true"))
		float defaultWalkSpeed;
};
