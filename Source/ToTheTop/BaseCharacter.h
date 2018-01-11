// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(config=Game)
class TOTHETOP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
 
 
public:
	// Sets default values for this character's properties
	ABaseCharacter();
 
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	//what happens when character hits Z kill zone
	void FellOutOfWorld(const class UDamageType& dmgType) override;
	
	//Animation implemented in BP
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
		void Death();
		void Death_Implementation();

	//Getter for health of the player character 
	UPROPERTY(BlueprintReadOnly, Category = "Character")
		int32 maxHealth = 100;


	//Getter for health of the player character 
	UFUNCTION(BlueprintPure, Category = "Character")
	int32 GetHealth() const;

	//Getter for Attack power of the player character 
	UFUNCTION(BlueprintPure, Category = "Character")
	int32 GetAttackPower() const;

	//Setter for health of the player character 
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetHealth(int newHealth);

	//Setter for Attack power of the player character 
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetAttackPower(int newAttackPower);

	//Setter for health of the player character 
	UFUNCTION(BlueprintCallable, Category = "Character")
		void AddHealth(int addedHealth);

	//Setter for Attack power of the player character 
	UFUNCTION(BlueprintCallable, Category = "Character")
		void AddAttackPower(int addedAttackPower);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);
 
	//Animation implemented in BP
	UFUNCTION(BlueprintImplementableEvent, Category = "Animations")
		void InjuredAnimation();
 
	//Animation implemented in BP
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Animations")
		void DeathAnimation();
 

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
 
    //health of the player character 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", Meta = (BlueprintProtected = "true"))
	int32 health;

	//how much the player will damage other characters 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (BlueprintProtected = "true"))
	int32 attackPower;

 
};
