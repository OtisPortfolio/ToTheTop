// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
/**
 * 
 */
class TOTHETOP_API FireAOE : public Ability
{
public:
	FireAOE();
	~FireAOE();

	//Damages any enemy in the AoeAttack radius sphere the character
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void Use(ABaseCharacter& character) override;

	//Damages any enemy in the AoeAttack radius sphere the character
	UFUNCTION(BlueprintCallable, Category = "Abilities")
		void AoeAttack(ABaseCharacter& character) {};

};
