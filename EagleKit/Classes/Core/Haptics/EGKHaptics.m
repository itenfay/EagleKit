//
//  EGKHaptics.m
//  EagleKit
//
//  Created by Teng Fei on 2023/12/13.
//

#import "EGKHaptics.h"
#import <AudioToolbox/AudioToolbox.h>

@implementation EGKHaptics

/// Actuate `Peek` feedback (weak boom)
+ (void)weakBoom {
    AudioServicesPlaySystemSound(1519);
}

/// Actuate `Pop` feedback (strong boom)
+ (void)strongBoom {
    AudioServicesPlaySystemSound(1520);
}

/// Actuate `Nope` feedback (series of three weak booms)
+ (void)threeWeakBooms {
    AudioServicesPlaySystemSound(1521);
}

@end
