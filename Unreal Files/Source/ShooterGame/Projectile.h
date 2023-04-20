// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SHOOTERGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, Category = "Actor Mesh")
		class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, Category = "Collision Sphere")
		class USphereComponent* CollisionSphere;

	class UPrimitiveComponent* GetPhysicsComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle_DestroyProjectile;

	virtual void DestroyProjectile();
};
