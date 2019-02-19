// Fill out your copyright notice in the Description page of Project Settings.
#include "PostOrderActor.h"
#include "Paths.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StringConv.h"
#include "string"
#include "UserWidget.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Hint.h"
#include "Kismet/KismetTextLibrary.h"

UWorld * WorldContextObject;

void  CallBackA(int CallBackNum, char* ResultMessage);

void CallBackA(int CallBackNum, char* ResultMessage)
{
	switch (CallBackNum)
	{
	case 1000:return;

	default:UE_LOG(LogTemp, Warning, TEXT("%s£¬%i"), ResultMessage, CallBackNum);
		TArray<AActor*> PostOrderActors;
		UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APostOrderActor::StaticClass(), PostOrderActors);
		if (PostOrderActors.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("PostOrderActors is NULL"));
			return;
		}
		APostOrderActor * PostOrderActor = Cast<APostOrderActor>(PostOrderActors[0]);
		if (!PostOrderActor)
		{
			UE_LOG(LogTemp, Error, TEXT("PostOrderActor is NULL"));
			return;
		}
		PostOrderActor->ShowHint(CallBackNum, ResultMessage);
		break;
	}

}

APostOrderActor::APostOrderActor()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>  HintWidget(TEXT("/Encryption/Hint"));
	WBP_HintWidget = HintWidget.Class;
}

bool APostOrderActor::GetDLLLoadResult()
{
	FString filePath1 = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Encryption/ThirdParty/"), TEXT("libeay32.dll")); // Concatenate the plugins folder and the DLL file.  
	FString filePath2 = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("Encryption/ThirdParty/"), TEXT("ZCVerifySDK.dll")); // Concatenate the plugins folder and the DLL file.  
	if (FPaths::FileExists(filePath1) && FPaths::FileExists(filePath2))
	{
		void  * DLLHandle1;
		DLLHandle1 = FPlatformProcess::GetDllHandle(*filePath1);
		if (DLLHandle1 != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("libeay32 is Load"));
			void *DLLHandle2;
			DLLHandle2 = FPlatformProcess::GetDllHandle(*filePath2);
			if (DLLHandle2 != NULL)
			{
				FUN 	DLLPostOrder = (FUN)FPlatformProcess::GetDllExport(DLLHandle2, *FString("PostOrder"));
				if (DLLPostOrder != NULL)
				{
					//DLLPostOrder((char*)"02ZKGC070D", CallBackA);

					APPID = TCHAR_TO_UTF8(*APPIDString);
					DLLPostOrder((char*)APPID, CallBackA);
					return true;
				}
			}
		}
	}


	return false;
}



void APostOrderActor::ShowHint(int CallBackNum, char* ResultMessage)
{

	UHint* HintWidget = CreateWidget<UHint>(GetWorld()->GetFirstPlayerController(), WBP_HintWidget);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	FText callBackNum = UKismetTextLibrary::Conv_IntToText(CallBackNum);
	std::string str = ResultMessage;
	FText resultMessage = FText::AsCultureInvariant(str.c_str());
	HintWidget->SetHintText(callBackNum, resultMessage);
	HintWidget->AddToViewport();
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(true);
	}
}

void APostOrderActor::BeginPlay()
{
	Super::BeginPlay();
	WorldContextObject = GetWorld();
	GetDLLLoadResult();
}
