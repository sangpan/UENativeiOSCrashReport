// Normal WebViewStyle.
// Fill out your copyright notice in the Description page of Project Settings.

#include "mobileWebView.h"
#include "MyWebView.h"

#if PLATFORM_IOS

//#import <UIKit/UIKit.h>
#include "Runtime/Core/Public/iOS/IOSAppDelegate.h"

MyWebViewController * myVC1;
UIWebView *webView1;

static NSString* kCloseButtonImageName = @"Icon50.png";
static CGFloat kTopBarHeight    = 5.0f;
#endif
MyWebView::MyWebView()
{
}

MyWebView::~MyWebView()
{
}
void MyWebView::createWebView(FString URL)
{
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{

    webView1 = [[UIWebView alloc]initWithFrame:CGRectMake(0, 0, 500, 320)];
    NSString *urlString = URL;
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
    [webView1 loadRequest:urlRequest];
//    [self.view addSubview:webView];
    
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

#if PLATFORM_IOS

@implementation MyWebViewController
-(void) initSubViews:(NSString *) URL
{
    _webView = [[UIWebView alloc]initWithFrame:CGRectMake(0, 0, 500, 320)];
    NSString *urlString = URL;
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
    [_webView loadRequest:urlRequest];
    
    UIViewController* topMostViewController = MyWebView::getTopMostViewController();
    
    if (!topMostViewController) {
        [[NSException exceptionWithName:@"My ............. InvalidOperationException" reason:@" Not found TopMostViewController" userInfo:nil] raise];
    }
    [topMostViewController presentViewController:myVC1 animated:YES completion:^{
     }];
    
    CGRect rect = [[UIScreen mainScreen] applicationFrame];
    
    myVC1.view	= [[UIView alloc] initWithFrame:rect];
    myVC1.view.backgroundColor		= [UIColor clearColor];
    myVC1.view.autoresizesSubviews	= YES;
    myVC1.view.autoresizingMask		= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    myVC1.view.contentMode			= UIViewContentModeRedraw;
    
    UIView* topBar	= [[UIView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(rect), kTopBarHeight)];
    topBar.autoresizingMask	= UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleBottomMargin;
    topBar.backgroundColor	= [UIColor blackColor];
    [myVC1.view addSubview:topBar];
    
    [myVC1.view addSubview:_webView];
    
    
    UIImage* buttonImage	= [UIImage imageNamed:kCloseButtonImageName];
    CGRect buttonRect		= CGRectMake(CGRectGetWidth(rect) - buttonImage.size.width, kTopBarHeight, buttonImage.size.width, buttonImage.size.height);
    _closeButton			= [UIButton buttonWithType:UIButtonTypeCustom];
    _closeButton.frame		= buttonRect;
    _closeButton.autoresizingMask	= UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin;
    [_closeButton setImage:buttonImage forState:UIControlStateNormal];
    [_closeButton addTarget:myVC1 action:@selector(_onClose:) forControlEvents:UIControlEventTouchUpInside];
    [myVC1.view addSubview:_closeButton];

}
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

@end
#endif
