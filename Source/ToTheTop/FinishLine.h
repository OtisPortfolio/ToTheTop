// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLine.generated.h"

UCLASS()
class TOTHETOP_API AFinishLine : public AActor
{
	GENERATED_BODY()


private:
	/** Attack Sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FinishLine", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;

	/** Particle System */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FinishLine", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* finishLinePS;

	UFUNCTION()
		void CompleteLevel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Sets default values for this actor's properties
	AFinishLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
