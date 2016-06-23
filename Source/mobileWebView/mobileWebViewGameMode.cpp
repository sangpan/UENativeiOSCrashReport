// Fill out your copyright notice in the Description page of Project Settings.

#include "mobileWebView.h"
#include "mobileWebViewGameMode.h"

#include "MyWebView.h"

void AmobileWebViewGameMode::openMyWebView(FString URL)
{
    MyWebView::createWebView(URL);
}

void AmobileWebViewGameMode::openMyWebViewController(FString URL)
{
    MyWebView::createWebViewController(URL);
}