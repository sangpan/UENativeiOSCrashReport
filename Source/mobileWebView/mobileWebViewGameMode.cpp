// Fill out your copyright notice in the Description page of Project Settings.

#include "mobileWebView.h"
#include "mobileWebViewGameMode.h"

#include "MyWebView.h"

//void AmobileWebViewGameMode::open()
//{
//#if PLATFORM_IOS
//    dispatch_async(dispatch_get_main_queue(), ^{
//
//    WebViewSocialDialog* dialog = [WebViewSocialDialog dialog:@"http://www.naver.com/"];
//    if (!dialog) NSLog(@"Fail...");
//    [dialog show];
//        
//    });
//
//#endif
//}
//
//void AmobileWebViewGameMode::openOldversion()
//{
//#if PLATFORM_IOS
//    dispatch_async(dispatch_get_main_queue(), ^{
//
//        OldWebViewDialog* dialog = [OldWebViewDialog dialog:@"http://www.naver.com/"];
//        
//        if (!dialog) NSLog(@"Fail...");
//        [dialog show];
//    });
//
//#endif
//}
void AmobileWebViewGameMode::openMyWebView(FString URL)
{
    MyWebView::createWebView(URL);
}

void AmobileWebViewGameMode::openMyWebViewController(FString URL)
{
//    MyWebView::closeWebView();
//    MyWebView::createWebView();
    MyWebView::createWebViewController(URL);
}