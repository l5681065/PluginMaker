// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PostOrderActor.generated.h"

class UUserWidget;

UCLASS()
class  APostOrderActor : public AActor
{
	GENERATED_BODY()
public:
	APostOrderActor();
	char * APPID;
	typedef void(*CallBack)(int callBackNum, char* ResultMessage);
	typedef int(*FUN)(char* s, CallBack c);
	bool GetDLLLoadResult();

	UPROPERTY(BlueprintReadOnly)
		TSubclassOf< UUserWidget>  WBP_HintWidget;
	UPROPERTY(EditAnywhere)
		FString  APPIDString = "02ZKGC070D";
	UPROPERTY(EditAnywhere)
		FName MainLevelName;

	void OpenMainLevel();
	void ShowHint(int CallBackNum, char* ResultMessage);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
