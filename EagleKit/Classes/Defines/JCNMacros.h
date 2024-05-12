//
//  JCNMacros.h
//
//  Created by chenxing on 2017/6/27.
//  Copyright © 2017 chenxing. All rights reserved.
//

#ifndef JCNMacros_h
#define JCNMacros_h


// 定义375x812参考尺寸
#define kReferenceScreenWidth 375.0
#define kReferenceScreenHeight 812.0

// 计算宽度比例
#define kWidthScaleFactor (UIScreen.mainScreen.bounds.size.width / kReferenceScreenWidth)
// 计算高度比例
#define kHeightScaleFactor (UIScreen.mainScreen.bounds.size.height / kReferenceScreenHeight)

// 根据比例调整视图的尺寸
#define AdaptedWidth(x) (ceilf((x) * kWidthScaleFactor))
#define AdaptedHeight(y) (ceilf((y) * kHeightScaleFactor))
#define AdaptedSize(x, y) CGSizeMake(AdaptedWidth(x), AdaptedHeight(y))
// 根据比例调整视图的位置
#define AdaptedOriginX(x) (ceilf((x) * kWidthScaleFactor))
#define AdaptedOriginY(y) (ceilf((y) * kHeightScaleFactor))
#define AdaptedPoint(x, y) CGPointMake(AdaptedOriginX(x), AdaptedOriginY(y))

// Return screen width.
#ifndef JCNScreenWidth
#define JCNScreenWidth  UIScreen.mainScreen.bounds.size.width
#endif

// Return screen height.
#ifndef JCNScreenHeight
#define JCNScreenHeight UIScreen.mainScreen.bounds.size.height
#endif

// Ratio
#ifndef JCNRatioWidth
#define JCNRatioWidth  JCNScreenWidth/375.0
#endif
#ifndef JCNRatioHeight
#define JCNRatioHeight JCNScreenHeight/667.0
#endif

// Judge iPhone.
#ifndef JCNIsPhone
#define JCNIsPhone (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
#endif

// Judge iPad.
#ifndef JCNIsPad
#define JCNIsPad   (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#endif

// Judge iPhone X series.
#ifndef JCNIsPhoneXAll
#define JCNIsPhoneXAll ({BOOL isPhoneXAll = NO; if (@available(iOS 11.0, *)) { isPhoneXAll = UIApplication.sharedApplication.delegate.window.safeAreaInsets.bottom > 0.0; } isPhoneXAll;})
#endif

#ifndef JCNSafeAreaInsets
#define JCNSafeAreaInsets ({UIEdgeInsets insets = UIEdgeInsetsMake(20, 0, 0, 0); if (@available(iOS 11.0, *)) { insets = UIApplication.sharedApplication.delegate.window.safeAreaInsets; } insets;})
#endif

// View safe insets.
#ifndef JCNViewSafeAreaInsets
#define JCNViewSafeAreaInsets(view) ({UIEdgeInsets insets; if(@available(iOS 11.0, *)) {insets = view.safeAreaInsets;} else {insets = UIEdgeInsetsZero;} insets;})
#endif

// Judge iPhoneX，XS
#ifndef JCNIsPhoneX
#define JCNIsPhoneX (!JCNIsPad && ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), UIScreen.mainScreen.currentMode.size): NO))
#endif

// Judge iPhoneXR
#ifndef JCNIsPhoneXR
#define JCNIsPhoneXR (!JCNIsPad && ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(828, 1792), UIScreen.mainScreen.currentMode.size) : NO))
#endif

// Judge iPhoneXS Max
#ifndef JCNIsPhoneXSMax
#define JCNIsPhoneXSMax (!JCNIsPad && ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2688), UIScreen.mainScreen.currentMode.size): NO))
#endif

// Status bar height.
#ifndef JCNStatusBarHeight
#define JCNStatusBarHeight (JCNIsPhoneXAll ? JCNSafeAreaInsets.top : 20.f)
#endif

// Navigation bar height.
#ifndef JCNNavBarHeight
#define JCNNavBarHeight 44.f
#endif

// Status bar & navigation bar height.
#ifndef JCNStatusBarAndNavBarHeight
#define JCNStatusBarAndNavBarHeight (44.f + JCNStatusBarHeight)
#endif

// View safe bottom margin.
#ifndef JCNViewSafeBottomMargin
#define JCNViewSafeBottomMargin (JCNIsPhoneXAll ? 34.f : 0.f)
#endif

// View safe top margin.
#ifndef JCNViewSafeTopMargin
#define JCNViewSafeTopMargin (JCNIsPhoneXAll ? 24.f : 0.f)
#endif

// TabBar height.
#ifndef JCNTabBarHeight
#define JCNTabBarHeight (49.f + JCNViewSafeBottomMargin)
#endif

// Custom tabBar height.
#ifndef JCNCustomTabBarHeight
#define JCNCustomTabBarHeight (116.f + JCNViewSafeBottomMargin)
#endif

// NSFileManager's singleton.
#ifndef JCNFileMgr
#define JCNFileMgr           [NSFileManager defaultManager]
#endif

// UIApplication's singleton.
#ifndef JCNSharedApp
#define JCNSharedApp         [UIApplication sharedApplication]
#endif

// App delegate.
#ifndef JCNAppDelegate
#define JCNAppDelegate       ((AppDelegate *)JCNSharedApp.delegate)
#endif

// NSNotificationCenter's singleton.
#ifndef JCNNotiCenter
#define JCNNotiCenter [NSNotificationCenter defaultCenter]
#endif

// NSUserDefaults's singleton.
#ifndef JCNUserDefaults
#define JCNUserDefaults [NSUserDefaults standardUserDefaults]
#endif

// System Versioning Preprocessor Macros.
#ifndef JCN_SYSTEM_VERSION_EQUAL_TO
#define JCN_SYSTEM_VERSION_EQUAL_TO(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#endif
#ifndef JCN_SYSTEM_VERSION_GREATER_THAN
#define JCN_SYSTEM_VERSION_GREATER_THAN(v)             ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#endif
#ifndef JCN_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO
#define JCN_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#endif
#ifndef JCN_SYSTEM_VERSION_LESS_THAN
#define JCN_SYSTEM_VERSION_LESS_THAN(v)				  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#endif
#ifndef JCN_SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO
#define JCN_SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)    ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)
#endif

// Judge iOS8 or later.
#ifndef JCNIOS8OrLater
#define JCNIOS8OrLater      JCN_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"8.0")
#endif

// App configuration information.
#ifndef JCNInfoDictionary
#define JCNInfoDictionary   [[NSBundle mainBundle] infoDictionary]
#endif

// App version.
#ifndef JCNAppVersion
#define JCNAppVersion       [JCNInfoDictionary objectForKey:@"CFBundleShortVersionString"]
#endif

// App build version.
#ifndef JCNBuildVersion
#define JCNBuildVersion     [JCNInfoDictionary objectForKey:(NSString *)kCFBundleVersionKey]
#endif

// App bundle identifier.
#ifndef JCNBundleIdentifier
#define JCNBundleIdentifier [JCNInfoDictionary objectForKey:@"CFBundleIdentifier"]
#endif

// App name.
#ifndef JCNAppName
#define JCNAppName [JCNInfoDictionary objectForKey:@"CFBundleDisplayName"]
#endif

// App document path in sandbox.
#ifndef JCNDocumentDirectoryPath
#define JCNDocumentDirectoryPath NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0]
#endif
// App caches path in sandbox.
#ifndef JCNCachesDirectoryPath
#define JCNCachesDirectoryPath   NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES)[0]
#endif

// app当前环境key
#ifndef JCNEnvironmentType
#define JCNEnvironmentType @"JCNEnvironmentType"
#endif

// Appending string.
#ifndef JCNAppendingString
#define JCNAppendingString(s1, s2)        [(s1) stringByAppendingString:(s2)]
#endif
// Appending path.
#ifndef JCNAppendingPathComponent
#define JCNAppendingPathComponent(s1, s2) [(s1) stringByAppendingPathComponent:(s2)]
#endif
// Resource path.
#ifndef JCNPathForResource
#define JCNPathForResource(name, ext)     [[NSBundle mainBundle] pathForResource:(name) ofType:(ext)]
#endif

// Get image with contents Of file.
#ifndef JCNLoadImage
#define JCNLoadImage(name)  [UIImage imageWithContentsOfFile:JCNPathForResource(name, nil)]
#endif
// Get image from memory.
#ifndef JCNImageNamed
#define JCNImageNamed(name) [UIImage imageNamed:(name)]
#endif

// RGB and alpha
#ifndef JCNColorFromRGBA
#define JCNColorFromRGBA(r, g, b, a) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:a]
#endif
// RGB
#ifndef JCNColorFromRGB
#define JCNColorFromRGB(r, g, b) JCNColorFromRGBA(r, g, b, 1.0)
#endif
// Sets rgb by hexadecimal value
#ifndef JCNColorFromHex
#define JCNColorFromHex(hex) [UIColor colorWithRed:((float)((hex & 0xFF0000) >> 16))/255.0 green:((float)((hex & 0xFF00) >> 8))/255.0 blue:((float)(hex & 0xFF))/255.0 alpha:1.0]
#endif

#ifndef JCNColorAlphaFromHex
#define JCNColorAlphaFromHex(hex,a) [UIColor colorWithRed:((float)((hex & 0xFF0000) >> 16))/255.0 green:((float)((hex & 0xFF00) >> 8))/255.0 blue:((float)(hex & 0xFF))/255.0 alpha:a]
#endif

#ifndef JCNRespondsToSelector
#define JCNRespondsToSelector(target, selector) [(target) respondsToSelector:selector]
#endif

// 消除执行选择器警告
#ifndef JCNSuppressPerformSelectorLeakWarning
#define JCNSuppressPerformSelectorLeakWarning(Stuff)                    \
do {                                                                    \
    _Pragma("clang diagnostic push")                                    \
    _Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
    Stuff;                                                              \
    _Pragma("clang diagnostic pop")                                     \
} while (0)
#endif

// 消除过期API警告
#ifndef JCNSuppressDeprecatedAPIWarning
#define JCNSuppressDeprecatedAPIWarning(Stuff)                          \
do {                                                                    \
    _Pragma("clang diagnostic push")                                    \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")   \
    Stuff;                                                              \
    _Pragma("clang diagnostic pop")                                     \
} while (0)
#endif

#pragma clang diagnostic pop
// Resolving block circular reference: __weak(arc)/__block
#ifndef JCNWeakify
#if DEBUG
    #if __has_feature(objc_arc)
    #define JCNWeakify(o) autoreleasepool{} __weak __typeof__(o) weak##_##o = o;
    #else
    #define JCNWeakify(o) autoreleasepool{} __block __typeof__(o) weak##_##o = o;
    #endif
#else
    #if __has_feature(objc_arc)
    #define JCNWeakify(o) try{} @finally{} __weak __typeof__(o) weak##_##o = o;
    #else
    #define JCNWeakify(o) try{} @finally{} __block __typeof__(o) weak##_##o = o;
    #endif
#endif
#endif

// Resolving block circular reference: __strong(arc)/-
#ifndef JCNStrongify
#if DEBUG
    #if __has_feature(objc_arc)
    #define JCNStrongify(o) autoreleasepool{} __strong __typeof__(o) strong##_##o = weak##_##o;
    #else
    #define JCNStrongify(o) autoreleasepool{} __typeof__(o) strong##_##o = weak##_##o;
    #endif
#else
    #if __has_feature(objc_arc)
    #define JCNStrongify(o) try{} @finally{} __strong __typeof__(o) strong##_##o = weak##_##o;
    #else
    #define JCNStrongify(o) try{} @finally{} __typeof__(o) strong##_##o = weak##_##o;
    #endif
#endif
#endif

// Logs
#if DEBUG
#define NSLog(fmt, ...) NSLog((@"[L: %d] %s " fmt), __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#else
#define NSLog(...)      while(0){}
#endif

// JCNSendMessage
#define JCNSendMessage(instance, protocolName, func) \
if ([(instance) conformsToProtocol:@protocol(protocolName)]) {\
    [(id<protocolName>)(instance) func]; \
} else {\
    NSLog(@"Don't impl this protocol: %@.", NSStringFromProtocol(@protocol(protocolName)));\
}

// Async run on main thread
#define JCN_ASYNC_RUN_MAIN_THREAD(block)\
if ([NSThread isMainThread]) {\
    block();\
} else {\
    dispatch_async(dispatch_get_main_queue(), block);\
}

// Dispatch after
#define JCN_DISPATCH_AFTER(delayInSeconds, block) \
dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)((delayInSeconds) * NSEC_PER_SEC)), dispatch_get_main_queue(), block)

// Open URL
#define JCN_OPEN_URL(url) [UIApplication.sharedApplication openURL:[NSURL URLWithString:(url)] options:@{} completionHandler:NULL]
#define JCN_OPEN_URL_WITH_BLOCK(url, block) [UIApplication.sharedApplication openURL:[NSURL URLWithString:(url)] options:@{} completionHandler:(block)]

// Internationalization
#define JCNGetI18NString(key) \
        [NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:nil]
#define JCNGetI18NStringFromTable(key, tbl) \
        [NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define JCNGetI18NStringFromTableInBundle(key, tbl, bundle) \
        [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define JCNGetI18NStringWithDefaultValue(key, val, tbl, bundle) \
        [bundle localizedStringForKey:(key) value:(val) table:(tbl)]

#endif /* JCNMacros_h */
