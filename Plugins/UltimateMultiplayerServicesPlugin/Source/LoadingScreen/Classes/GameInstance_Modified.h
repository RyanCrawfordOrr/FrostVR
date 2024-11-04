// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/IDelegateInstance.h"
#include "GameInstance_Modified.generated.h"

UENUM(BlueprintType)
enum class ELoadingScreenMoviePlaybackType : uint8 {
    /** Normal playback mode.  Play each movie in the play list a single time */
    LoadingScreenMoviePlaybackType_Normal UMETA(DisplayName="Normal Playback"),
    /** Looped playback mode.  Play all movies in the play list in order then start over until manually canceled */
    LoadingScreenMoviePlaybackType_Looped UMETA(DisplayName = "Looped Playback"),
    /** Alternate Looped mode.  Play all of the movies in the play list and loop just the last movie until loading is finished. */
    LoadingScreenMoviePlaybackType_LoadingLoop UMETA(DisplayName = "Looped Last Playback"),
    LoadingScreenMoviePlaybackType_MAX UMETA(Hidden)
};

/**
 * 
 */
UCLASS()
class LOADINGSCREEN_API UGameInstance_Modified : public UGameInstance {
    GENERATED_BODY()

public:
    /** The widget to be displayed on top of the movie or simply standalone if there is no movie. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    TSubclassOf<UUserWidget> WidgetClass;

    /** The movie paths local to the game's Content/Movies/ directory we will play. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    TArray<FString> MoviePaths;

    /** Should we just play back, loop, etc.  NOTE: if the playback type is MT_LoopLast, then bAutoCompleteWhenLoadingCompletes will be togged on when the last movie is hit*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    ELoadingScreenMoviePlaybackType PlaybackType = ELoadingScreenMoviePlaybackType::LoadingScreenMoviePlaybackType_Normal;

    /** If true, this will call the engine tick while the game thread is stalled waiting for a loading movie to finish. This only works for post-startup load screens and is potentially unsafe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bAllowEngineTick = true;

    /** If true loading screens here cannot have any uobjects of any kind or use any engine features at all. This will start the movies very early as a result on platforms that support it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bAllowInEarlyStartup = false;

    /** If true, the loading screen will disappear as soon as all movies are played and loading is done. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bAutoCompleteWhenLoadingCompletes = true;

    /** If true, movies can be skipped by clicking the loading screen as long as loading is done. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bMoviesAreSkippable = false;

    /** If true, movie playback continues until Stop is called. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bWaitForManualStop = false;

    /** The minimum time that a loading screen should be opened for. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    float MinimumLoadingScreenDisplayTime = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    float fadeInDuration = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    float fadeOutDuration = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bFadeIn = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    bool bFadeOut = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LoadingScreen")
    FLinearColor fadeColor = FLinearColor::Black;

    UUserWidget *WidgetObject;

    virtual void Init() override;

    UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
    void SetupLoadingScreen();

    // bAutoCompleteWhenLoadingCompletes if false, call to finish LoadingScreen
    UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
    void EndupLoadingScreen(bool force);

    UFUNCTION(BlueprintNativeEvent, Category = "LoadingScreen", meta = (AdvancedDisplay = "MapName"))
    void BeginLoadingScreen(const FString& MapName);
    virtual void BeginLoadingScreen_Implementation(const FString& MapName);

    UFUNCTION(BlueprintNativeEvent, Category = "LoadingScreen", meta = (AdvancedDisplay = "world"))
    void EndLoadingScreen(UWorld *world);
    virtual void EndLoadingScreen_Implementation(UWorld *world);
};
