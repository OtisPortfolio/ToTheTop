// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
/**
 * 
 */
class TOTHETOP_API SuperJump : public Ability
{
public:
	SuperJump();
	~SuperJump();
	virtual void Use(ABaseCharacter& character) override {};
private:
	//is SuperJump ability on cooldown for Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", Meta = (BlueprintProtected = "true"))
		bool bSuperJumpIsOnCooldown;

	//length of time haste is active after use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities", Meta = (BlueprintProtected = "true"))
		float SuperJumpTimeLength = 5.0f;
};
