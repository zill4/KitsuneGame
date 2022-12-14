// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "Http.h"
#include "Components/WidgetComponent.h"

#include "HTTPGet_Actor.generated.h"


UCLASS()
class KITSUNE_API AHTTPGet_Actor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHTTPGet_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnGetUsersResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnGetUserByUsernameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION()
		void SendHTTPGet(FString Username);



public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "HTTP")
		UBoxComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "HTTP")
		UWidgetComponent* ResponseWidgetComponent;

private:
	FHttpModule* Http;
};