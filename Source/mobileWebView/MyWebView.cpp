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

        webView1 = [[UIWebView alloc]initWithFrame:CGRectMake(0, 0, 500, 320)];
        NSString *urlString = [NSString stringWithUTF8String:(TCHAR_TO_ANSI(*URL))];
        NSURL *url = [NSURL URLWithString:urlString];
        NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
        [webView1 loadRequest:urlRequest];
        [[[IOSAppDelegate GetDelegate] RootView] addSubview:webView1];
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
    myVC1 = [[MyWebViewController alloc] init];
    
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [myVC1 initSubViews:nsStrURL];
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
    
    CGRect rect = [[UIScreen mainScreen] applicationFrame];
    
    //Setting ViewController's root view.
    myVC1.view	= [[UIView alloc] initWithFrame:rect];
    myVC1.view.backgroundColor		= [UIColor clearColor];
    myVC1.view.autoresizesSubviews	= YES;
    myVC1.view.autoresizingMask		= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    myVC1.view.contentMode			= UIViewContentModeRedraw;

    //Make topBar.
//    UIView* topBar	= [[UIView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(rect), kTopBarHeight)];
//    topBar.autoresizingMask	= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleBottomMargin;
//    topBar.backgroundColor	= [UIColor blackColor];
//    [myVC1.view addSubview:topBar];
    
    [myVC1.view addSubview:_webView];
    
    //Make Top-Right Button
    UIImage* buttonImage	= [UIImage imageNamed:kCloseButtonImageName];
    CGRect buttonRect		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _closeButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _closeButton.frame		= buttonRect;
    _closeButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_closeButton setImage:buttonImage forState:UIControlStateNormal];
    [_closeButton addTarget:myVC1 action:@selector(_onClose:) forControlEvents:UIControlEventTouchUpInside];
    [myVC1.view addSubview:_closeButton];

    
    CGRect buttonRect2		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, (2.0 * buttonImage.size.height) +  kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _testButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _testButton.frame		= buttonRect2;
    _testButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_testButton setImage:buttonImage forState:UIControlStateNormal];
    [_testButton addTarget:myVC1 action:@selector(_testFunction:) forControlEvents:UIControlEventTouchUpInside];
    [myVC1.view addSubview:_testButton];
}
- (void)_testFunction:(id)sender
{
    switch ([PHPhotoLibrary authorizationStatus]) {
        case PHAuthorizationStatusNotDetermined:
        {
            [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
             NSLog(@"repeat This 1!.");
////             [[IOSAppDelegate GetDelegate] ToggleSuspend:false];
//             dispatch_async(dispatch_get_main_queue(), ^{             // can't running this block when using [.. ToggleSuspend:true]; .
//                NSLog(@"repeat This 2!.");
//                [self _testFunction:nil];
////                [[IOSAppDelegate GetDelegate] ToggleSuspend:true];
//            });
             [self _testFunction:nil];
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
    [_webView stopLoading];
    [self dismissViewControllerAnimated:YES completion:^{
     }];

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
#endif
