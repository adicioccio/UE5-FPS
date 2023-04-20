// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "MainCharacter.h"
#include "MyPlayerController.h"
#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));

	StaticMesh->SetSimulatePhysics(true);

	SetRootComponent(CollisionSphere);
	StaticMesh->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnActorOverlapBegin);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DestroyProjectile, this, &AProjectile::DestroyProjectile, 5.0f, false);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* AProjectile::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(StaticMesh);
}

void AProjectile::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	Destroy();
	FString Target = OtherActor->GetName();
	FString Projectile = OverlappedActor->GetName();
	
	AEnemy* EnemyClass = Cast<AEnemy>(OtherActor);
	AMainCharacter* PlayerClass = nullptr;
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainCharacter::StaticClass(), FoundCharacters);
	if (FoundCharacters.Num() > 0) {
		PlayerClass = Cast<AMainCharacter>(FoundCharacters[0]);
	}

	if (Target.Contains("BP_Blue") && Projectile.Contains("BP_Blue")) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Target);
		EnemyClass->hitpoints = EnemyClass->hitpoints - 1;
		PlayerClass->playerScore = PlayerClass->playerScore + 10;
	}

	if (Target.Contains("BP_Red") && Projectile.Contains("BP_Red")) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Target);
		EnemyClass->hitpoints = EnemyClass->hitpoints - 1;
		PlayerClass->playerScore = PlayerClass->playerScore + 10;
	}

	if (EnemyClass->hitpoints <= 0) {
		OtherActor->Destroy();
		PlayerClass->playerScore = PlayerClass->playerScore + 50;
	}
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	FText newscore = FText::FromString(FString::FromInt(PlayerClass->playerScore));
	MyPC->MyHud->Score->SetText(newscore);
}

void AProjectile::DestroyProjectile()
{
	if (this) {
		Destroy();
	}
}

