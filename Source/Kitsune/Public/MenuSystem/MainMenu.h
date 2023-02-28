// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class KITSUNE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetMenuInterface(IMenuInterface* menuInterface);
	
	void Setup();

	void Teardown();

protected:
	virtual bool Initialize() override;


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UFUNCTION()
	void HostServer();

	IMenuInterface* MenuInterface;
};
