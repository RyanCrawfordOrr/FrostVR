// Fill out your copyright notice in the Description page of Project Settings.

#include "GameViewportClient_Modified.h"
#include "Engine/Texture2D.h"
#include "Engine/Canvas.h"

void UGameViewportClient_Modified::PostRender(UCanvas* Canvas)
{
	Super::PostRender(Canvas);

	// Fade if requested, you could use the same DrawScreenFade method from any canvas such as the HUD
	if (bFading)
	{
		DrawScreenFade(Canvas);
	}
}

void UGameViewportClient_Modified::ClearFade()
{
	bFading = false;
}

void UGameViewportClient_Modified::Fade(const float Duration, const bool ToFade,  const FLinearColor ToColor)
{
	if (World)
	{
		bFading = true;
		this->bToFade = ToFade;
		this->fadeColor = ToColor;
		FadeDuration = Duration;
		FadeStartTime = World->GetTimeSeconds();
	}
}

void UGameViewportClient_Modified::DrawScreenFade(UCanvas* Canvas)
{
	if (bFading)
	{
		if (World)
		{
			const float Time = World->GetTimeSeconds();
			const float Alpha = FMath::Clamp((Time - FadeStartTime) / FadeDuration, 0.f, 1.f);

			// Make sure that we stay black in a fade to black
			if (Alpha == 1.f && !bToFade)
			{
				bFading = false;
			}
			else
			{
				FColor OldColor = Canvas->DrawColor;
				FLinearColor FadeColor = this->fadeColor;
				FadeColor.A = bToFade ? Alpha : 1 - Alpha;
				Canvas->DrawColor = FadeColor.ToFColor(true); // TheJamsh: "4.10 cannot convert directly to FColor, so need to use FLinearColor::ToFColor() :)
				Canvas->DrawTile(Canvas->DefaultTexture, 0, 0, Canvas->ClipX, Canvas->ClipY, 0, 0, Canvas->DefaultTexture->GetSizeX(), Canvas->DefaultTexture->GetSizeY());
				Canvas->DrawColor = OldColor;
			}
		}
	}
}



