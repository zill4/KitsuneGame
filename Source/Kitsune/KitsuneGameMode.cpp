// Copyright Epic Games, Inc. All Rights Reserved.

#include "KitsuneGameMode.h"
#include "KitsuneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKitsuneGameMode::AKitsuneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
