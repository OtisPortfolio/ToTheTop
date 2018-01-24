// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilityManagerComponent.h"
#include "Ability.h"
#include "Leap.h"
#include "Haste.h"
#include "FireAOE.h"
#include "HealSelf.h"


 
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
 
	//set default player attributes
	health = maxHealth;
 

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;




	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
 
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset namedd MyCharacter (to avoid direct content references in C++)
 
}

 

 

UAbilityManagerComponent* const ABaseCharacter::GetAbilityManager() const
{
	return AbilityManager;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
 
	AbilityManager = NewObject<UAbilityManagerComponent>(RootComponent);
	AbilityManager->AttachTo(RootComponent);
	if (AbilityManager)
	{
		AbilityManager->AddAbility<UHealSelf>(this);
		AbilityManager->AddAbility<UHaste>(this);
		AbilityManager->AddAbility<ULeap>(this);
		AssignInput<UHealSelf>(1);
		AssignInput<UHaste>(2);
		AssignInput<ULeap>(3);

	}
 
	
}

float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	health -= Damage;

	if (health <= 0)
	{
		Death();
	}
	else
	{
		InjuredAnimation();
	}

	//damage applied
	return Damage;
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}

}
 

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	Death();
}

int32 ABaseCharacter::GetHealth() const
{
	return health;
}


void ABaseCharacter::SetHealth(int newHealth)
{
	health = newHealth;
}



void ABaseCharacter::AddHealth(int addedHealth)
{

	if (health+addedHealth > maxHealth)
	{
		health = maxHealth; 
	}
	else if(addedHealth > 0)
	{
		health += addedHealth;
	}

}

void ABaseCharacter::AddAttackPower(int addedAttackPower)
{
	attackPower += addedAttackPower;
}

int32 ABaseCharacter::GetAttackPower() const
{
	return attackPower;
}
void ABaseCharacter::SetAttackPower(int newAttackPower)
{
	attackPower = newAttackPower;
}

 
void ABaseCharacter::Death_Implementation()
{
	Destroy(this);
}
// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
 	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
 	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);





  
}

 

