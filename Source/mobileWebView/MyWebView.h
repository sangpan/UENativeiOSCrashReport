// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class MOBILEWEBVIEW_API MyWebView
{
public:
	MyWebView();
	~MyWebView();
    
    static void createWebView(FString URL);
    static void closeWebView();
    
    static void createWebViewController(FString URL);
    
#if PLATFORM_IOS
    static UIViewController * getRootViewController();
    static UIViewController * getTopMostViewController();
#endif
};

#if PLATFORM_IOS
@interface MyWebViewController : UIViewController
@property (nonatomic, strong, readonly) UIWebView* webView;
@property (nonatomic, strong, readonly) UIButton* closeButton;
-(void) initSubViews:(NSString *) URL;
@end
#endif