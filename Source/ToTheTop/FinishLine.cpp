// This project was created by John R. Otis Jr. and may not be used by anyone without explicit written consent by the author. Dec 2017

#include "FinishLine.h"
#include "Classes/Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToTheTopGameModeBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	finishLinePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("finishLinePS"));
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));


	CollisionSphere->AttachTo(RootComponent);
	CollisionSphere->SetSphereRadius(50.0f);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::CompleteLevel);

	finishLinePS->AttachTo(RootComponent);
	finishLinePS->SetWorldScale3D(FVector(.5f, .5f, .5f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/P_AuraCircle_Temp.P_AuraCircle_Temp"));
	if (particleAsset.Succeeded())
	{
		finishLinePS->SetTemplate(particleAsset.Object);
	}


}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 

void AFinishLine::CompleteLevel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* playerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (playerActor)
	{
		if (OtherActor == playerActor)
		{
			AToTheTopGameModeBase* gameMode = Cast<AToTheTopGameModeBase>(UGameplayStatics::GetGameMode(this));
			if (gameMode)
			{
				gameMode->LevelCompleted();
			}
		}

	}
}