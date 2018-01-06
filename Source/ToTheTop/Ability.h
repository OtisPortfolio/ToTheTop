// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"

/**
 * 
 */
class TOTHETOP_API Ability
{
public:
	friend class ABaseCharacter;
	Ability() : abilityCooldown{0}, activationLength{0} {};
	virtual ~Ability() {};
	virtual void Use(ABaseCharacter& character) = 0;
	virtual void Update()=0;
	virtual float GetCooldown() const { return abilityCooldown; };
	virtual float GetActivationLength() const { return activationLength; };

protected:
	//ability cooldowns for Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", Meta = (BlueprintProtected = "true"))
		float abilityCooldown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", Meta = (BlueprintProtected = "true"))
		float activationLength;
	
};
