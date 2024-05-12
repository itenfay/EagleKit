//
//  EGKHaptics.h
//  EagleKit
//
//  Created by Teng Fei on 2023/12/13.
//

#import <Foundation/Foundation.h>

/// Some haptic feedback that works on iPhone 6 and up.
@interface EGKHaptics : NSObject

/// Actuate `Peek` feedback (weak boom)
+ (void)weakBoom;

/// Actuate `Pop` feedback (strong boom)
+ (void)strongBoom;

/// Actuate `Nope` feedback (series of three weak booms)
+ (void)threeWeakBooms;

@end
