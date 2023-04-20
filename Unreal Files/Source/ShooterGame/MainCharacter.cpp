// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Projectile.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	CameraComponent->bUsePawnControlRotation = true;

	CameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UCharacterMovementComponent* moveComp = FindComponentByClass< UCharacterMovementComponent>();
	moveComp->MaxWalkSpeed = Velocity;

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::StopRun);

	PlayerInputComponent->BindAction("FireBlue", IE_Pressed, this, &AMainCharacter::FireProjectileBlue);
	PlayerInputComponent->BindAction("FireRed", IE_Pressed, this, &AMainCharacter::FireProjectileRed);
}

void AMainCharacter::MoveForward(float Amount)
{
	if (Amount != 0.0f) {
		AddMovementInput(GetActorForwardVector(), Amount);
	}
}

void AMainCharacter::MoveRight(float Amount)
{
	if (Amount != 0.0f) {
		AddMovementInput(GetActorRightVector(), Amount);
	}
}

void AMainCharacter::StartRun() 
{
	Velocity = Velocity * RunMultiplier;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("START RUN! %f"), Velocity));
}

void AMainCharacter::StopRun()
{
	Velocity = Velocity / RunMultiplier;
}

void AMainCharacter::FireProjectileBlue()
{
	if (ProjectileBlue != nullptr) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FActorSpawnParameters asp;
			asp.Owner = this;
			asp.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform SpawnTransform = CameraComponent->GetComponentTransform();
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileBlue, SpawnTransform, asp);
			if (Projectile != nullptr) {
				FVector LaunchDirection = CameraComponent->GetForwardVector().GetSafeNormal();
				UPrimitiveComponent* PhysicsComponent = Projectile->GetPhysicsComponent();
				PhysicsComponent->AddForce(LaunchDirection * 600000);
			}

		}
	}
}

void AMainCharacter::FireProjectileRed()
{
	if (ProjectileRed != nullptr) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FActorSpawnParameters asp;
			asp.Owner = this;
			asp.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform SpawnTransform = CameraComponent->GetComponentTransform();
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileRed, SpawnTransform, asp);
			if (Projectile != nullptr) {
				FVector LaunchDirection = CameraComponent->GetForwardVector().GetSafeNormal();
				UPrimitiveComponent* PhysicsComponent = Projectile->GetPhysicsComponent();
				PhysicsComponent->AddForce(LaunchDirection * 600000);
			}

		}
	}
}
