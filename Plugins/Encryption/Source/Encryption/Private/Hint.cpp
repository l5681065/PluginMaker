// Fill out your copyright notice in the Description page of Project Settings.

#include "Hint.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/TextBlock.h"

void UHint::SetHintText(FText ErrorCodeText, FText ErrorInfoText)
{
	Text_ErrorCode->SetText(ErrorCodeText);
	Text_ErrorInfo->SetText(ErrorInfoText);
}

void UHint::Quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

bool UHint::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}
	Button_Quit->OnClicked.AddDynamic(this, &UHint::Quit);

	return true;
}


