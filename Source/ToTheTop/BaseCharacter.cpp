// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
 
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

	defaultZVelocity = this->GetCharacterMovement()->JumpZVelocity;
	defaultWalkSpeed = this->GetCharacterMovement()->MaxWalkSpeed;

	int healIncrement = 10;
	//set default player attributes
	health = 100;
	attackPower = 10;

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


	HealParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	HealParticleSystem->AttachTo(RootComponent);
	HealParticleSystem->SetVisibility(false);

 


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)



}

 

 

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

 
 



void ABaseCharacter::SuperJump()
{
	//if (!bSuperJumpIsOnCooldown)
	//{
	//	bSuperJumpIsOnCooldown = true;
	//	defaultZVelocity = this->GetCharacterMovement()->JumpZVelocity;
	//	this->GetCharacterMovement()->JumpZVelocity = defaultZVelocity * 2;
	//	FTimerHandle UnusedHandle;
	//	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABaseCharacter::ResetSuperJump, SuperJumpTimeLength, false);
	//}


}
void ABaseCharacter::ResetSuperJump()
{
	//FTimerHandle UnusedHandle;
	//this->GetCharacterMovement()->JumpZVelocity = defaultZVelocity;
	//GetWorldTimerManager().SetTimer(UnusedHandle, [&]() {bSuperJumpIsOnCooldown = false; }, AbilityCooldown, false);
}

void ABaseCharacter::Haste()
{
	//if (!bHasteIsOnCooldown)
	//{
	//	bHasteIsOnCooldown = true;
	//	defaultWalkSpeed = this->GetCharacterMovement()->MaxWalkSpeed;
	//	this->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed * 2;
	//	FTimerHandle UnusedHandle;
	//	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABaseCharacter::ResetHaste, HasteTimeLength, false);
	//}

}
void ABaseCharacter::ResetHaste()
{
	//FTimerHandle UnusedHandle;
	//this->GetCharacterMovement()->MaxWalkSpeed = defaultWalkSpeed;
	//GetWorldTimerManager().SetTimer(UnusedHandle, [&]() {bHasteIsOnCooldown = false; }, AbilityCooldown, false);

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ABaseCharacter::GetHealth() const
{
	return health;
}

int32 ABaseCharacter::GetAttackPower() const
{
	return attackPower;
}

void ABaseCharacter::SetHealth(int newHealth)
{
	health = newHealth;
}

void ABaseCharacter::SetAttackPower(int newAttackPower)
{
	attackPower = newAttackPower;
}

void ABaseCharacter::AddHealth(int addedHealth)
{
	health += addedHealth;
	if (addedHealth < 0)
	{
		if (health<=0)
		{
			DeathAnimation();
		}
		else
		{
			InjuredAnimation();

		}

	}
}

void ABaseCharacter::AddAttackPower(int addedAttackPower)
{
	attackPower += addedAttackPower;
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
 

