// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KitsuneGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KITSUNE_API UKitsuneGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UKitsuneGameInstance(const FObjectInitializer& ObjectInitializer);
	
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
		void LoadMenu();

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& Address);

private:
	TSubclassOf<class UUserWidget> MenuClass;
}; 
