//
//  EGKUIMacros.h
//  EagleKit
//
//  Created by Teng Fei on 2017/6/27.
//  Copyright © 2017 Teng Fei. All rights reserved.
//

#ifndef EGKUIMacros_h
#define EGKUIMacros_h

#pragma mark - UI

// The screen width.
#ifndef EGKScreenWidth
#define EGKScreenWidth [UIScreen mainScreen].bounds.size.width
#endif

// The screen height.
#ifndef EGKScreenHeight
#define EGKScreenHeight [UIScreen mainScreen].bounds.size.height
#endif

// Indicates whether it is an iPhone or an iPod touch.
#ifndef EGKIsPhone
#define EGKIsPhone ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
#endif
// Indicates whether it is an iPad.
#ifndef EGKIsPad
#define EGKIsPad ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
#endif

// The window safe insets.
#ifndef EGKSafeAreaInsets
#define EGKSafeAreaInsets ({UIEdgeInsets insets = UIEdgeInsetsMake(20, 0, 0, 0); if (@available(iOS 11.0, *)) { insets = UIApplication.sharedApplication.delegate.window.safeAreaInsets; } insets;})
#endif
// The view safe insets.
#ifndef EGKViewSafeAreaInsets
#define EGKViewSafeAreaInsets(view) ({UIEdgeInsets insets; if(@available(iOS 11.0, *)) {insets = view.safeAreaInsets;} else {insets = UIEdgeInsetsZero;} insets;})
#endif

// The iPhone X series.
#ifndef EGKIsPhoneXAll
#define EGKIsPhoneXAll ({BOOL isPhoneXAll = NO; if (@available(iOS 11.0, *)) { isPhoneXAll = UIApplication.sharedApplication.delegate.window.safeAreaInsets.bottom > 0.0; } isPhoneXAll;})
#endif
// The iPhoneX，XS.
#ifndef EGKIsPhoneX
#define EGKIsPhoneX (!EGKIsPad && ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), UIScreen.mainScreen.currentMode.size): NO))
#endif
// The iPhoneXR.
#ifndef EGKIsPhoneXR
#define EGKIsPhoneXR (!EGKIsPad && ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(828, 1792), UIScreen.mainScreen.currentMode.size) : NO))
#endif
// The iPhoneXS Max.
#ifndef EGKIsPhoneXSMax
#define EGKIsPhoneXSMax (!EGKIsPad && ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2688), UIScreen.mainScreen.currentMode.size): NO))
#endif

// The status bar height.
#ifndef EGKStatusBarHeight
#define EGKStatusBarHeight EGKSafeAreaInsets.top
#endif

// The navigation bar height.
#ifndef EGKNavBarHeight
#define EGKNavBarHeight 44.f
#endif

// The status bar & navigation bar height.
#ifndef EGKStatusBarAndNavBarHeight
#define EGKStatusBarAndNavBarHeight (EGKStatusBarHeight + EGKNavBarHeight)
#endif

// The view safe bottom margin. (EGKIsPhoneXAll ? 34.f : 0.f)
#ifndef EGKViewSafeBottomMargin
#define EGKViewSafeBottomMargin EGKSafeAreaInsets.bottom
#endif

// The tabBar height.
#ifndef EGKTabBarHeight
#define EGKTabBarHeight (49.f + EGKViewSafeBottomMargin)
#endif

// Calculates width ratio, rd: reference dimension.
#define EGKWidthRatio(rd) ([UIScreen mainScreen].bounds.size.width / rd)
// Calculates height ratio, rd: reference dimension.
#define EGKHeightRatio(rd) ([UIScreen mainScreen].bounds.size.height / rd)

// Adjusts the size of the view according to the scale.
#define EGKAdaptedWidth(w, rd) (ceilf((w) * EGKWidthRatio(rd)))
#define EGKAdaptedHeight(h, rd) (ceilf((h) * EGKHeightRatio(rd)))
#define EGKAdaptedSize(w, h, rd) CGSizeMake(EGKAdaptedWidth(w, rd), EGKAdaptedHeight(w, rd))
// Adjusts the position of the view according to the scale.
#define EGKAdaptedOriginX(x, rd) (ceilf((x) * EGKWidthRatio(rd)))
#define EGKAdaptedOriginY(y, rd) (ceilf((y) * EGKHeightRatio(rd)))
#define EGKAdaptedPoint(x, y, rd) CGPointMake(EGKAdaptedOriginX(x, rd), EGKAdaptedOriginY(y, rd))

#pragma mark - Version

// System Versioning Preprocessor Macros.
#ifndef EGK_SYSTEM_VERSION_EQUAL_TO
#define EGK_SYSTEM_VERSION_EQUAL_TO(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#endif
#ifndef EGK_SYSTEM_VERSION_GREATER_THAN
#define EGK_SYSTEM_VERSION_GREATER_THAN(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#endif
#ifndef EGK_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO
#define EGK_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#endif
#ifndef EGK_SYSTEM_VERSION_LESS_THAN
#define EGK_SYSTEM_VERSION_LESS_THAN(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#endif
#ifndef EGK_SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO
#define EGK_SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v) ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)
#endif

// iOS 10.0 or later.
#ifndef EGKIOS10OrLater
#define EGKIOS10OrLater EGK_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"10.0")
#endif

// iOS 11.0 or later.
#ifndef EGKIOS11OrLater
#define EGKIOS11OrLater EGK_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"11.0")
#endif

#pragma mark - Image

// Gets an image from the specified named asset.
#ifndef EGKImageNamed
#define EGKImageNamed(name) [UIImage imageNamed:(name)]
#endif
// Gets an image by loading the image data from the file at the specified path.
#ifndef EGKImageByLoading()
#define EGKLoadImage(name) [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(name) ofType:nil]]
#endif

#pragma mark - Color

// RGB color and alpha.
#ifndef EGKColorFromRGBA
#define EGKColorFromRGBA(r, g, b, a) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:a]
#endif
// RGB color.
#ifndef EGKColorFromRGB
#define EGKColorFromRGB(r, g, b) EGKColorFromRGBA(r, g, b, 1.0)
#endif

// Sets rgb by hexadecimal value and alpha.
#ifndef EGKColorFromHexAlpha
#define EGKColorFromHexAlpha(hex, a) [UIColor colorWithRed:((float)((hex & 0xFF0000) >> 16))/255.0 green:((float)((hex & 0xFF00) >> 8))/255.0 blue:((float)(hex & 0xFF))/255.0 alpha:a]
#endif
// Sets rgb by hexadecimal value.
#ifndef EGKColorFromHex
#define EGKColorFromHex(hex) EGKColorFromHexAlpha(hex, 1.0)
#endif

#endif /* EGKUIMacros_h */
