// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class MOBILEWEBVIEW_API MyWebView
{
public:
    static void createWebView(FString URL);
    static void closeWebView();
    
    static void createWebViewController(FString URL);
    
#if PLATFORM_IOS
    static UIViewController * getRootViewController();
    static UIViewController * getTopMostViewController();
#endif
};

#if PLATFORM_IOS
@interface MyWebViewController : UIViewController <UIWebViewDelegate, UINavigationControllerDelegate, UIImagePickerControllerDelegate>
@property (nonatomic, strong, readonly) UIWebView* webView;
@property (nonatomic, strong, readonly) UIButton* closeButton;
@property (nonatomic, strong, readonly) UIButton* testButton;
-(void) initSubViews:(NSString *) URL;
@end

@interface MyInputViewController : UIViewController <UITextFieldDelegate>
@property (nonatomic, strong, readonly) UITextField *textField;
@property (nonatomic, strong, readonly) UITextView *textView;
@property (nonatomic, strong, readonly) UIButton* closeButton;
@property (nonatomic, strong, readonly) UIButton* testButton;
-(void) initView;
@end
#endif