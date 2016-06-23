// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class mobileWebView : ModuleRules
{
	public mobileWebView(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
        });

PrivateDependencyModuleNames.AddRange(new string[] {  });

if (Target.Platform == UnrealTargetPlatform.IOS) {
PublicFrameworks.AddRange (
new string[] {
"CoreGraphics",
"QuartzCore",

"Accounts",
"AddressBook",
"AdSupport",
"AssetsLibrary",
"CoreAudio",
"CoreTelephony",
"CoreText",
"CoreData",
"ImageIO",
"MessageUI",
"Security",
"Social",
"StoreKit",
//"libsqlite3.0",
"MediaPlayer",
"CoreLocation",
"CoreMotion",
"SystemConfiguration",
//"libc++",
"MobileCoreServices",
"iAd",

"Photos",
"SafariServices",
"UIKit",
"Foundation",

"EventKit",
"EventKitUI"
}
);

	}
}
}
