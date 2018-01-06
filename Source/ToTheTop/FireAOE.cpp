// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "FireAOE.h"

FireAOE::FireAOE()
{
}

FireAOE::~FireAOE()
{
}

void FireAOE::Use(ABaseCharacter& character)
{
	AoeAttack(character);
}

//void FireAOE::AoeAttack(ABaseCharacter& character)
//{
//	//get all overlapping actors and store in an array
//	TArray<AActor*> CollectedActors;
//	character.;
//	SetHealth(GetHealth());
//	//for each actor collision
//	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
//	{
//		//cast the actor to
//		ABaseCharacter* const baseCharacter = Cast<ABaseCharacter>(CollectedActors[iCollected]);
//		//if the cast is successful
//		if (baseCharacter && baseCharacter != this)
//		{
//			//call set Health
//			baseCharacter->AddHealth(-GetAttackPower());
//		}
//
//	}
//}
