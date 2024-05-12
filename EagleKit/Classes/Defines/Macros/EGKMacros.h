//
//  EGKMacros.h
//  EagleKit
//
//  Created by Teng Fei on 2017/6/27.
//  Copyright © 2017 Teng Fei. All rights reserved.
//

#import "EGKUIMacros.h"

#ifndef EGKMacros_h
#define EGKMacros_h

#pragma mark - Logs

// Logs
#ifndef EGKLog
#if DEBUG
    #define EGKLog(fmt, ...) NSLog((@"[L: %d] %s " fmt), __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#else
    #define EGKLog(...)      while(0){}
#endif
#endif

#pragma mark - Send Message

// Send message.
#ifndef EGK_Send_Message
#define EGK_Send_Message(instance, protocolName, func) \
if ([(instance) conformsToProtocol:@protocol(protocolName)]) { \
    [(id<protocolName>)(instance) func]; \
} else { \
    EGKLog(@"%@ didn't impl this protocol: %@.", instance, NSStringFromProtocol(@protocol(protocolName))); \
}
#endif

#pragma mark - Dispatch

// Async run on main thread.
// if ([NSThread isMainThread])
#ifndef EGK_Run_Safely_OnMainThread
#define EGK_Run_Safely_OnMainThread(block) \
if (dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL) == dispatch_queue_get_label(dispatch_get_main_queue())) { \
    block(); \
} else { \
    dispatch_async(dispatch_get_main_queue(), block); \
}
#endif

// Dispatch after
#ifndef EGK_Dispatch_After
#define EGK_Dispatch_After(delayInSeconds, block) \
dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)((delayInSeconds) * NSEC_PER_SEC)), dispatch_get_main_queue(), block)
#endif

#pragma mark - Perform Selector After Delay

#ifndef EGK_Perform_AfterDelay
#define EGK_Perform_AfterDelay(target, selector, delay) [target performSelector:selector withObject:nil afterDelay:delay]
#endif
#ifndef EGK_Perform_AfterDelay_WithObject
#define EGK_Perform_AfterDelay_WithObject(target, selector, obj, delay) [target performSelector:selector withObject:obj afterDelay:delay]
#endif

#pragma mark - Responds To Selector

// Responds to selector.
#ifndef EGK_Responds_To_Selector
#define EGK_Responds_To_Selector(target, selector) ((target) && [(target) respondsToSelector:selector])
#endif

#pragma mark - Open URL

// Open URL
#ifndef EGK_Can_Open_URL
#define EGK_Can_Open_URL(url) [UIApplication.sharedApplication canOpenURL:[NSURL URLWithString:(url)]]
#endif
#ifndef EGK_Open_URL
#define EGK_Open_URL(url) [UIApplication.sharedApplication openURL:[NSURL URLWithString:(url)] options:@{} completionHandler:NULL]
#endif
#ifndef EGK_Open_URL_WithBlock
#define EGK_Open_URL_WithBlock(url, block) [UIApplication.sharedApplication openURL:[NSURL URLWithString:(url)] options:@{} completionHandler:block]
#endif

#pragma mark - I18N

// Internationalization(i18n)
#define EGK_Get_I18N_String(key) \
        [NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:nil]
#define EGK_Get_I18N_StringFromTable(key, tbl) \
        [NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define EGK_Get_I18N_StringFromTableInBundle(key, tbl, bundle) \
        [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define EGK_Get_I18N_StringWithDefaultValue(key, val, tbl, bundle) \
        [bundle localizedStringForKey:(key) value:(val) table:(tbl)]

#pragma mark - Suppress Warnings

// Suppress perform selector leak warning.
#ifndef EGK_Suppress_PerformSelector_LeakWarning
#define EGK_Suppress_PerformSelector_LeakWarning(Stuff)                 \
do {                                                                    \
    _Pragma("clang diagnostic push")                                    \
    _Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
    Stuff;                                                              \
    _Pragma("clang diagnostic pop")                                     \
} while (0)
#endif

// Suppress deprecated API Warning.
#ifndef EGK_Suppress_DeprecatedAPIWarning
#define EGK_Suppress_DeprecatedAPIWarning(Stuff)                        \
do {                                                                    \
    _Pragma("clang diagnostic push")                                    \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")   \
    Stuff;                                                              \
    _Pragma("clang diagnostic pop")                                     \
} while (0)
#endif

#pragma mark - Resolving Block Circular Reference

// Resolving block circular reference: __weak(arc)/__block
#ifndef EGKWeakify
#if DEBUG
#if __has_feature(objc_arc)
    #define EGKWeakify(o) autoreleasepool{} __weak __typeof__(o) weak##_##o = o;
#else
    #define EGKWeakify(o) autoreleasepool{} __block __typeof__(o) weak##_##o = o;
#endif
#else
#if __has_feature(objc_arc)
    #define EGKWeakify(o) try{} @finally{} __weak __typeof__(o) weak##_##o = o;
#else
    #define EGKWeakify(o) try{} @finally{} __block __typeof__(o) weak##_##o = o;
#endif
#endif
#endif

// Resolving block circular reference: __strong(arc)/-
#ifndef EGKStrongify
#if DEBUG
#if __has_feature(objc_arc)
    #define EGKStrongify(o) autoreleasepool{} __strong __typeof__(o) strong##_##o = weak##_##o;
#else
    #define EGKStrongify(o) autoreleasepool{} __typeof__(o) strong##_##o = weak##_##o;
#endif
#else
#if __has_feature(objc_arc)
    #define EGKStrongify(o) try{} @finally{} __strong __typeof__(o) strong##_##o = weak##_##o;
#else
    #define EGKStrongify(o) try{} @finally{} __typeof__(o) strong##_##o = weak##_##o;
#endif
#endif
#endif

#pragma mark - Other

// FileManager's singleton.
#ifndef EGKFileMgr
#define EGKFileMgr [NSFileManager defaultManager]
#endif

// Application's singleton.
#ifndef EGKSharedApp
#define EGKSharedApp [UIApplication sharedApplication]
#endif

// App's delegate.
#ifndef EGKAppDelegate
#define EGKAppDelegate EGKSharedApp.delegate
#endif

// NotificationCenter's singleton.
#ifndef EGKNotifiCenter
#define EGKNotifiCenter [NSNotificationCenter defaultCenter]
#endif

// UserDefaults's singleton.
#ifndef EGKUserDefaults
#define EGKUserDefaults [NSUserDefaults standardUserDefaults]
#endif

// App's configuration information.
#ifndef EGKInfoDictionary
#define EGKInfoDictionary [[NSBundle mainBundle] infoDictionary]
#endif

// App's version.
#ifndef EGKAppVersion
#define EGKAppVersion [EGKInfoDictionary objectForKey:@"CFBundleShortVersionString"]
#endif

// App's build version.
#ifndef EGKBuildVersion
#define EGKBuildVersion [EGKInfoDictionary objectForKey:(NSString *)kCFBundleVersionKey]
#endif

// App's bundle identifier.
#ifndef EGKBundleIdentifier
#define EGKBundleIdentifier [EGKInfoDictionary objectForKey:@"CFBundleIdentifier"]
#endif

// App's name.
#ifndef EGKAppName
#define EGKAppName [EGKInfoDictionary objectForKey:@"CFBundleDisplayName"]
#endif

// App document path in sandbox.
#ifndef EGKDocumentDirectoryPath
#define EGKDocumentDirectoryPath NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0]
#endif

// App caches path in sandbox.
#ifndef EGKCachesDirectoryPath
#define EGKCachesDirectoryPath NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES)[0]
#endif

// Appending string.
#ifndef EGKAppendingString
#define EGKAppendingString(s1, s2) [(s1) stringByAppendingString:(s2)]
#endif
// Appending path.
#ifndef EGKAppendingPathComponent
#define EGKAppendingPathComponent(s1, s2) [(s1) stringByAppendingPathComponent:(s2)]
#endif
// Resource path.
#ifndef EGKPathForResource
#define EGKPathForResource(name, ext) [[NSBundle mainBundle] pathForResource:(name) ofType:(ext)]
#endif

#endif /* EGKMacros_h */
