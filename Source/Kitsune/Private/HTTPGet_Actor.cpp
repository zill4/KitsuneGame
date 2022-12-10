// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/SparseDelegate.h"
#include "HTTPResponseWidget.h"
#include "HTTPGet_Actor.h"



// Sets default values
AHTTPGet_Actor::AHTTPGet_Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Area"));
	SetRootComponent(OverlapComponent);

	ResponseWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Response Widget"));
	ResponseWidgetComponent->SetupAttachment(OverlapComponent);

	Http = &FHttpModule::Get();

}

// Called when the game starts or when spawned
void AHTTPGet_Actor::BeginPlay()
{
	Super::BeginPlay();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

}

void AHTTPGet_Actor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Create loading state for loading circleThrobber before net request
	// After request turn throbber off.
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped from c++"));

	if (ResponseWidgetComponent)
	{

		UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
		SendHTTPGet("");
		if (ResponseWidget)
		{
			ResponseWidget->ShowLoading(true);


		}

	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ResponseWidgetComponent is NOT ok"));
	}
}

// Called every frame
void AHTTPGet_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ResponseWidgetComponent)
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		if (CameraManager)
		{
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraManager->GetCameraLocation(), ResponseWidgetComponent->GetComponentLocation());
			LookAtRotation.Pitch = 0.f;
			LookAtRotation.Roll = 0.f;
			LookAtRotation.Yaw -= 180.f;
			ResponseWidgetComponent->SetWorldRotation(LookAtRotation);
		}
	}
}

void AHTTPGet_Actor::SendHTTPGet(FString Username)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Calling SendHTTPGet"));

	if (Username.IsEmpty())
	{
		// callback after response
		Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnGetUsersResponse);
		Request->SetURL("http://localhost:8080/users");
	}
	else
	{
		Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnGetUserByUsernameResponse);
		Request->SetURL(FString::Printf(TEXT("http://localhost:8080/user/%s")));
	}


	Request->SetVerb("GET");
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void AHTTPGet_Actor::OnGetUsersResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GetUsers response"));
	// Probably don't want to do this here.
	if (ResponseWidgetComponent)
	{
		//UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
		//if (ResponseWidget)
		//{
			//ResponseWidget->ShowLoading(false);

		if (Response->GetResponseCode() == 200)
		{
			const FString ResponseBody = Response->GetContentAsString();
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				// populated JsonObject, start parsing
				// was "users" testing without field name.


				TArray<TSharedPtr<FJsonValue>> UserArray = JsonObject->GetArrayField("");



				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("data received %s"), *ResponseBody));

				for (const TSharedPtr<FJsonValue> UserValue : UserArray)
				{


					const FString Username = UserValue->AsObject()->GetStringField("Username");
					const int32 UserId = UserValue->AsObject()->GetNumberField("ID");
					//ResponseWidget->AddUser(UserId, Username);
				}
			}
		}
		//else
		//{
			// TODO -> Trigger Error
			//ResponseWidget->ShowError(Response->GetResponseCode(), "Error occurred");
		//}
	//}
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ResponseWidget is not ok.."));
	}
}

void AHTTPGet_Actor::OnGetUserByUsernameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> JsonObject;

	// Probably don't want to do this here.
	if (ResponseWidgetComponent)
	{
		UHTTPResponseWidget* ResponseWidget = Cast<UHTTPResponseWidget>(ResponseWidgetComponent->GetWidget());
		if (ResponseWidget)
		{
			ResponseWidget->ShowLoading(false);

			if (Response->GetResponseCode() == 200)
			{
				const FString ResponseBody = Response->GetContentAsString();
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

				if (FJsonSerializer::Deserialize(Reader, JsonObject))
				{

					const FString Username = JsonObject->GetStringField("Username");
					const int32 UserId = JsonObject->GetNumberField("ID");
					ResponseWidget->AddUser(UserId, Username);
				}
			}
			else
			{
				// TODO -> Trigger Error
				ResponseWidget->ShowError(Response->GetResponseCode(), "Error occurred");
			}
		}
	}
}