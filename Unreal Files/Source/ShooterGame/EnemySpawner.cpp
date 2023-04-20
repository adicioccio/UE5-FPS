// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "TimerManager.h"
#include "Enemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnParams.Owner = this;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	AEnemySpawner::SpawnEnemy();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy() 
{
	if (SpawnSpeed > 0.0) {
		AActor* NewActor = GetWorld()->SpawnActor<AEnemy>(EnemyType, GetActorLocation(), GetActorRotation(), SpawnParams);
		GetWorldTimerManager().SetTimer(TimerHandle_SpawnEnemy, this, &AEnemySpawner::SpawnEnemy, SpawnSpeed, false);
	}
}

