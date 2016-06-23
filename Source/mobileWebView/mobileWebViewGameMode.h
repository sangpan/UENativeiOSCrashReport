// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "mobileWebViewGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEWEBVIEW_API AmobileWebViewGameMode : public AGameMode
{
	GENERATED_BODY()
public:
//    UFUNCTION(BlueprintCallable,Category="test")
//    static void open();
//    UFUNCTION(BlueprintCallable,Category="test")
//    static void openOldversion();
    
    UFUNCTION(BlueprintCallable,Category="test")
    static void openMyWebView(FString URL);
    
    UFUNCTION(BlueprintCallable,Category="test")
    static void openMyWebViewController(FString URL);
    
};
