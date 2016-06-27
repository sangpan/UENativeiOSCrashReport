// Normal WebViewStyle.
// Fill out your copyright notice in the Description page of Project Settings.

#include "mobileWebView.h"
#include "MyWebView.h"

#if PLATFORM_IOS

//#import <UIKit/UIKit.h>
#include "Runtime/Core/Public/iOS/IOSAppDelegate.h"
#import <Photos/Photos.h>

MyWebViewController * myVC1;        //  this is UIViewController.
UIWebView *webView1;

static NSString* kCloseButtonImageName = @"Icon50.png";
static CGFloat kTopBarHeight    = 5.0f;
#endif

void MyWebView::createWebView(FString URL)
{
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{

//        webView1 = [[UIWebView alloc]initWithFrame:CGRectMake(0, 0, 500, 320)];
//        NSString *urlString = [NSString stringWithUTF8String:(TCHAR_TO_ANSI(*URL))];
//        NSURL *url = [NSURL URLWithString:urlString];
//        NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
//        [webView1 loadRequest:urlRequest];
//        [[[IOSAppDelegate GetDelegate] RootView] addSubview:webView1];
       MyInputViewController * myVCInput = [[MyInputViewController alloc] init];
        
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [myVCInput initView];
        });
    });
#endif
}


void MyWebView::closeWebView()
{
#if PLATFORM_IOS
    [webView1 removeFromSuperview];
    [[[IOSAppDelegate GetDelegate] RootView] setNeedsDisplay];
#endif
}

void MyWebView::createWebViewController(FString URL)
{
#if PLATFORM_IOS

    NSString * nsStrURL = [NSString stringWithUTF8String:(TCHAR_TO_ANSI(*URL))];
    MyWebViewController * myVC = [[MyWebViewController alloc] init];
    
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [myVC initSubViews:nsStrURL];
    });
#endif

}
#if PLATFORM_IOS
UIViewController * MyWebView::getRootViewController()
{
    NSArray* windows = [[UIApplication sharedApplication] windows];
    
    for (UIWindow* window in windows) {
        if (window.rootViewController) {
            return window.rootViewController;
        }
    }
    
    return nil;
}

UIViewController * MyWebView::getTopMostViewController()
{
    UIViewController* rootViewController = MyWebView::getRootViewController();
    
    if (!rootViewController)
        return nil;
    
    UIViewController* topMostViewController = rootViewController;
    if ([topMostViewController respondsToSelector:@selector(presentedViewController)]) {
        while (topMostViewController.presentedViewController) {
            topMostViewController	= topMostViewController.presentedViewController;
        }
    }
    
    return topMostViewController;
}
#endif

#pragma mark - MyWebViewController (New UIViewController)
#if PLATFORM_IOS

@implementation MyWebViewController
-(void) initSubViews:(NSString *) URL
{
    //Make UIWebView
    _webView = [[UIWebView alloc]initWithFrame:CGRectMake(0, 0, 500, 320)];
    _webView.delegate			= self;
    NSString *urlString = URL;
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
    [_webView loadRequest:urlRequest];
    
    UIViewController* topMostViewController = MyWebView::getTopMostViewController();
    
    if (!topMostViewController) {
        [[NSException exceptionWithName:@"My ............. InvalidOperationException" reason:@" Not found TopMostViewController" userInfo:nil] raise];
    }
    

    [topMostViewController presentViewController:myVC1 animated:YES completion:^{
//        [[IOSAppDelegate GetDelegate] ToggleSuspend:true];    //Engine Pause after ViewController present. // this can help avoid Crash When Using Webview... But
     }];
    
    /*
    //Second Way
    [topMostViewController addChildViewController:self];        //self = New ViewController
    [topMostViewController.view addSubview:self.view];
    [self beginAppearanceTransition:YES animated:YES];    //???? below code run when setting NO.
    [UIView
     animateWithDuration:0.3
     delay:0.0
     options:UIViewAnimationOptionCurveEaseOut
     animations:^(void){
     //     self.view.alpha = 1.0;
     CGRect rectScreen = [[UIScreen mainScreen] applicationFrame];
     self.view.frame = rectScreen;
     }
     completion:^(BOOL finished) {
     [self endAppearanceTransition];
     [self didMoveToParentViewController:topMostViewController];
     }
     ];
    */
    
    CGRect rect = [[UIScreen mainScreen] applicationFrame];
    rect.origin.y = rect.size.height;
    
    //Setting ViewController's root view.
    self.view	= [[UIView alloc] initWithFrame:rect];
    self.view.backgroundColor		= [UIColor clearColor];
    self.view.autoresizesSubviews	= YES;
    self.view.autoresizingMask		= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.view.contentMode			= UIViewContentModeRedraw;

    //Make topBar.
//    UIView* topBar	= [[UIView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(rect), kTopBarHeight)];
//    topBar.autoresizingMask	= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleBottomMargin;
//    topBar.backgroundColor	= [UIColor blackColor];
//    [myVC1.view addSubview:topBar];
    
    [self.view addSubview:_webView];

    //Make Top-Right Button
    UIImage* buttonImage	= [UIImage imageNamed:kCloseButtonImageName];
    CGRect buttonRect		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _closeButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _closeButton.frame		= buttonRect;
    _closeButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_closeButton setImage:buttonImage forState:UIControlStateNormal];
    [_closeButton addTarget:self action:@selector(_onClose:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_closeButton];

    
    CGRect buttonRect2		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, (2.0 * buttonImage.size.height) +  kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _testButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _testButton.frame		= buttonRect2;
    _testButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_testButton setImage:buttonImage forState:UIControlStateNormal];
    [_testButton addTarget:self action:@selector(_testFunction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_testButton];
}
- (void)_testFunction:(id)sender
{
    switch ([PHPhotoLibrary authorizationStatus]) {
        case PHAuthorizationStatusNotDetermined:
        {
            [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
             NSLog(@"repeat This 1!.");
////             [[IOSAppDelegate GetDelegate] ToggleSuspend:false];
             dispatch_async(dispatch_get_main_queue(), ^{             // can't running this block when using [.. ToggleSuspend:true];
                NSLog(@"repeat This 2!.");
                [self _testFunction:nil];
////                [[IOSAppDelegate GetDelegate] ToggleSuspend:true];
            });
//             [self _testFunction:nil];
             return;
             }];
            return;
        }
            break;
        case PHAuthorizationStatusAuthorized:
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"PHAuthorizationStatusAuthorized");
            });
        }
            break;
        case PHAuthorizationStatusDenied:
        case PHAuthorizationStatusRestricted:
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"PHAuthorizationStatusDenied, PHAuthorizationStatusRestricted");
            });
        }
            break;
    }
}

#pragma mark - Close button function.
- (void)_onClose:(id)sender
{
    [self _dismiss];
}
- (void)_dismiss
{
    NSLog(@"run _dismiss");

    [_webView stopLoading];
    [self dismissViewControllerAnimated:YES completion:^{
     }];

    /*
    [self willMoveToParentViewController:nil];
    [self beginAppearanceTransition:NO animated:YES];
    [UIView
     animateWithDuration:0.3
     delay:0.0
     options:UIViewAnimationOptionCurveEaseOut
     animations:^(void){
//     self.view.alpha = 0.0;
     }
     completion:^(BOOL finished) {
     [self endAppearanceTransition];
     [self.view removeFromSuperview];
     [self removeFromParentViewController];
     }
     ];
     */
}

#pragma mark - UIViewController Delegate Code
- (void)viewWillDisappear:(BOOL)animated// Called when the view is dismissed, covered or otherwise hidden. Default does nothing
{
    NSLog(@"viewWillDisappear");
    [[IOSAppDelegate GetDelegate] ToggleSuspend:false];
}

#pragma mark - UIWebViewDelegate Code
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSURL* url			= [request URL];
    NSString* urlScheme = [url scheme];
    NSString* urlString	= [url absoluteString];
    
    if ([urlScheme isEqualToString:@"http"] || [urlScheme isEqualToString:@"https"]) {
    }
    NSLog(@"url : %@", url);
    NSLog(@"urlScheme : %@", urlScheme);
    NSLog(@"urlString : %@", urlString);

    return YES;
}

@end


@implementation MyInputViewController
-(void) initView
{
    
    UIViewController* topMostViewController = MyWebView::getTopMostViewController();
    
    if (!topMostViewController) {
        [[NSException exceptionWithName:@"My ............. InvalidOperationException" reason:@" Not found TopMostViewController" userInfo:nil] raise];
    }
    
    [topMostViewController presentViewController:self animated:YES completion:^{
     }];

    
    CGRect rect = [[UIScreen mainScreen] applicationFrame];
    rect.origin.y = rect.size.height;
    
    //Setting ViewController's root view.
    self.view	= [[UIView alloc] initWithFrame:rect];
    self.view.backgroundColor		= [UIColor clearColor];
    self.view.autoresizesSubviews	= YES;
    self.view.autoresizingMask		= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.view.contentMode			= UIViewContentModeRedraw;
    
    //This TextField cause Crash by Virtual Keyboard Appear <-> Disappear Repeat 
    _textField = [[UITextField alloc] initWithFrame:CGRectMake(0, 0, rect.size.width-100, 100)];
    _textField.backgroundColor = [UIColor whiteColor];
    [_textField setReturnKeyType:UIReturnKeyDone];
    _textField.delegate = self;
    [self.view addSubview:_textField];
    //Make Top-Right Button
    UIImage* buttonImage	= [UIImage imageNamed:kCloseButtonImageName];
    CGRect buttonRect		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _closeButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _closeButton.frame		= buttonRect;
    _closeButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_closeButton setImage:buttonImage forState:UIControlStateNormal];
    [_closeButton addTarget:self action:@selector(_onClose:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_closeButton];
    
    
    CGRect buttonRect2		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, (2.0 * buttonImage.size.height) +  kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _testButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _testButton.frame		= buttonRect2;
    _testButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_testButton setImage:buttonImage forState:UIControlStateNormal];
    [_testButton addTarget:self action:@selector(_testFunction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_testButton];
}
- (void)_testFunction:(id)sender
{

}

#pragma mark - Close button function.
- (void)_onClose:(id)sender
{
    [self _dismiss];
}
- (void)_dismiss
{
    NSLog(@"run _dismiss");
    [self dismissViewControllerAnimated:YES completion:^{
     }];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

@end
#endif
