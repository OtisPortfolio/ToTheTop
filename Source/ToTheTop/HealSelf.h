// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
/**
 * 
 */
class TOTHETOP_API HealSelf : public Ability
{
public:
	HealSelf();
	~HealSelf();
	virtual void Use(ABaseCharacter& character) override;

private:
	//how much the healing spell will heal character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities", Meta = (BlueprintProtected = "true"))
		int healIncrement;
};
