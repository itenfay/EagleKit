//
//  EGKTimer.h
//  EagleKit
//
//  Created by Teng Fei on 2023/12/12.
//

#import <Foundation/Foundation.h>

@class EGKTimer;

typedef void (^EGKTimerInvocationHandler)(EGKTimer *timer);

@interface EGKTimer : NSObject

/// The repeating time interval.
@property (nonatomic, assign, readonly) NSTimeInterval repeatingInterval;
/// The remaining count for the countdown.
@property (nonatomic, assign, readonly) NSInteger remainingFireCount;
/// Represents the timer whether you want to fire.
@property (nonatomic, assign, readonly) BOOL isFiring;

/// "fireCount" is used to the countdown.
- (instancetype)initWithFireCount:(NSInteger)fireCount;

/// Set the count of you want the timer to fire, it can be used to the countdown.
- (void)setFireCount:(NSInteger)fireCount;

/// The receiver's userInfo object.
- (id)userInfo;

- (void)schedule:(NSTimeInterval)interval invocation:(EGKTimerInvocationHandler)invocationHandler;
- (void)schedule:(NSTimeInterval)interval userInfo:(id)userInfo invocation:(EGKTimerInvocationHandler)invocationHandler;

- (void)resume;
- (void)pause;
- (void)invalidate;

@end
