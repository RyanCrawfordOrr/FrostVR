// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance_Modified.h"
#include "MoviePlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameViewportClient_Modified.h"

void UGameInstance_Modified::Init() {
    Super::Init();

    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UGameInstance_Modified::BeginLoadingScreen);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGameInstance_Modified::EndLoadingScreen);
}

void UGameInstance_Modified::SetupLoadingScreen() {
    if (!IsRunningDedicatedServer())
    {
        FLoadingScreenAttributes LoadingScreen;
        LoadingScreen.bAllowInEarlyStartup = this->bAllowInEarlyStartup;
        LoadingScreen.bAllowEngineTick = this->bAllowEngineTick;
        LoadingScreen.bAutoCompleteWhenLoadingCompletes = this->bAutoCompleteWhenLoadingCompletes;
        LoadingScreen.bMoviesAreSkippable = this->bMoviesAreSkippable;
        LoadingScreen.bWaitForManualStop = this->bWaitForManualStop;
        LoadingScreen.MinimumLoadingScreenDisplayTime = this->MinimumLoadingScreenDisplayTime;
        LoadingScreen.MoviePaths = this->MoviePaths;
        switch(this->PlaybackType) {
            case ELoadingScreenMoviePlaybackType::LoadingScreenMoviePlaybackType_Normal:
                LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Normal;
                break;
            case ELoadingScreenMoviePlaybackType::LoadingScreenMoviePlaybackType_Looped:
                LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Looped;
                break;
            case ELoadingScreenMoviePlaybackType::LoadingScreenMoviePlaybackType_LoadingLoop:
                LoadingScreen.PlaybackType = EMoviePlaybackType::MT_LoadingLoop;
                break;
            default:
                LoadingScreen.PlaybackType = EMoviePlaybackType::MT_MAX;
                break;
        }
        if (UKismetSystemLibrary::IsValidClass(WidgetClass)) {
            WidgetObject = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        }
        LoadingScreen.WidgetLoadingScreen = WidgetObject == NULL ? FLoadingScreenAttributes::NewTestLoadingScreenWidget() : WidgetObject->TakeWidget();

        GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
    }
}

void UGameInstance_Modified::EndupLoadingScreen(bool force) {
    if (force) {
        GetMoviePlayer()->ForceCompletion();
    } else {
        GetMoviePlayer()->StopMovie();
    }
}

void UGameInstance_Modified::BeginLoadingScreen_Implementation(const FString& MapName)
{
    if (bFadeIn) {
        const UWorld* World = GetWorld();
        if (World) {
            if (!IsRunningDedicatedServer()) {
                UGameViewportClient_Modified *GameViewportClient = Cast<UGameViewportClient_Modified>(
                        World->GetGameViewport());
                if (GameViewportClient) {
                    GameViewportClient->Fade(this->fadeInDuration, true, this->fadeColor);
                }
            }
        }
    }
}

void UGameInstance_Modified::EndLoadingScreen_Implementation(UWorld* world)
{
    if (bFadeOut) {
        const UWorld *World = GetWorld();
        if (World) {
            if (!IsRunningDedicatedServer()) {
                UGameViewportClient_Modified *GameViewportClient = Cast<UGameViewportClient_Modified>(
                        World->GetGameViewport());
                if (GameViewportClient) {
                    GameViewportClient->Fade(this->fadeOutDuration, false, this->fadeColor);
                }
            }
        }
    }
}


