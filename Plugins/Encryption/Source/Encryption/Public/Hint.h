// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hint.generated.h"

/**
 * 
 */
UCLASS()
class  UHint : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock * Text_ErrorCode;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock * Text_ErrorInfo;

	UPROPERTY(meta = (BindWidget))
		class UButton * Button_Quit;

	void SetHintText(FText ErrorCodeText, FText ErrorInfoText);

	UFUNCTION()
		void Quit();
protected:
	virtual bool Initialize() override;
};
