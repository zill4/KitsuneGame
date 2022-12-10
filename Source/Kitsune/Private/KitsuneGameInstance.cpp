// Fill out your copyright notice in the Description page of Project Settings.


#include "KitsuneGameInstance.h"

UKitsuneGameInstance::UKitsuneGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"))
}

void UKitsuneGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"))
}