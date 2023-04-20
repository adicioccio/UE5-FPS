// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));

	StaticMesh->SetCollisionProfileName("OverlapAll");

	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCharacter::StaticClass(), FoundCharacters);
	if (FoundCharacters.Num() > 0) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "FOUND!");
		PlayerPoint = Cast<AMainCharacter>(FoundCharacters[0]);
	}
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerPoint == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "You forgot to set the player point!");
		return;
	}
	FVector ActorLocation = FMath::VInterpConstantTo(GetActorLocation(), PlayerPoint->GetActorLocation(), DeltaTime, 300);
	SetActorLocation(ActorLocation);
}

