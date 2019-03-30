// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UMGExtensionLibraryBPLibrary.h"
#include "UMG/Public/Slate/WidgetRenderer.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "Engine/TextureRenderTarget2D.h"


UUMGExtensionLibraryBPLibrary::UUMGExtensionLibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UTextureRenderTarget2D * UUMGExtensionLibraryBPLibrary::CreateRenderTarget(bool UseGamma, TextureFilter Filter, FVector2D DrawSize)
{
	return FWidgetRenderer::CreateTargetFor(DrawSize, Filter, UseGamma);
}

void UUMGExtensionLibraryBPLibrary::RenderWidgetToTarget(bool UseGamma, TextureFilter Filter, UUserWidget * WidgetToRender, FVector2D DrawSize, float DeltaTime, UTextureRenderTarget2D * Target)
{
	if (!WidgetToRender) return;
	if (DrawSize == FVector2D(0, 0)) return;
	if (!Target) return;
	FWidgetRenderer * r = new FWidgetRenderer(UseGamma);
	TSharedRef<SWidget> ref = WidgetToRender->TakeWidget();
	r->DrawWidget(Target, ref, DrawSize, DeltaTime);
	BeginCleanup(r);
}

UTextureRenderTarget2D* UUMGExtensionLibraryBPLibrary::RenderWidgetToTexture(bool UseGamma, TextureFilter Filter, UUserWidget * WidgetToRender, FVector2D DrawSize, float DeltaTime)
{
	if (!WidgetToRender) return nullptr;
	if (DrawSize == FVector2D(0, 0)) return nullptr;

	FWidgetRenderer *r = new FWidgetRenderer(UseGamma);
	UTextureRenderTarget2D *rt = r->CreateTargetFor(DrawSize, Filter, UseGamma);
	TSharedRef<SWidget> ref = WidgetToRender->TakeWidget();
	r->DrawWidget(rt, ref, DrawSize, DeltaTime);

	BeginCleanup(r);

	return rt;
}

