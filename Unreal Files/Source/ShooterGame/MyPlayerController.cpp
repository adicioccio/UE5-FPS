// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PlayerHUD.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (WBP_PlayerHUD) {
		MyHud = CreateWidget<UPlayerHUD>(GetWorld(), WBP_PlayerHUD);
		MyHud->AddToViewport();
	}
}
