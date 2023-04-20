// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class SHOOTERGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditAnywhere, Category = "My Pawn")
		class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "My Pawn")
		float Velocity = 450.0f;
	
	UPROPERTY(EditAnywhere, Category = "My Pawn")
		float RunMultiplier = 1.7f;

	UPROPERTY(EditAnywhere, Category = "My Pawn")
		TSubclassOf<class AProjectile> ProjectileBlue;

	UPROPERTY(EditAnywhere, Category = "My Pawn")
		TSubclassOf<class AProjectile> ProjectileRed;

	int32 playerScore = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	float MoveForwardAmount = 0.0;

	float MoveRightAmount = 0.0;

	virtual void MoveForward(float Amount);

	virtual void MoveRight(float Amount);

	virtual void StartRun();

	virtual void StopRun();

	virtual void FireProjectileBlue();

	virtual void FireProjectileRed();

};
