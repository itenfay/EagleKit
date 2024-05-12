//
//  EGKTimer.m
//  EagleKit
//
//  Created by Teng Fei on 2023/12/12.
//

#import "EGKTimer.h"

@interface EGKTimer ()
@property (nonatomic, strong) NSTimer *timer;
@property (nonatomic, copy) EGKTimerInvocationHandler invocationHandler;
@end

@implementation EGKTimer

- (instancetype)initWithFireCount:(NSInteger)fireCount {
    self = [super init];
    if (self) {
        [self setFireCount:fireCount];
    }
    return self;
}

- (void)setFireCount:(NSInteger)fireCount {
    _remainingFireCount = fireCount;
    _isFiring = YES;
}

- (id)userInfo {
    return self.timer.userInfo;
}

- (void)schedule:(NSTimeInterval)interval invocation:(EGKTimerInvocationHandler)invocationHandler {
    [self schedule:interval userInfo:nil invocation:invocationHandler];
}

- (void)schedule:(NSTimeInterval)interval userInfo:(id)userInfo invocation:(EGKTimerInvocationHandler)invocationHandler {
    NSAssert(interval >= 0, @"The repeat time interval for the timer can not less than or equal to zero.");
    if (_timer) return;
    _repeatingInterval = interval;
    _invocationHandler = invocationHandler;
    NSTimer *timer = [NSTimer timerWithTimeInterval:interval
                                             target:self
                                           selector:@selector(_handleTimerAciton)
                                           userInfo:userInfo
                                            repeats:interval > 0];
    _timer = timer;
    [NSRunLoop.currentRunLoop addTimer:timer forMode:NSRunLoopCommonModes];
}

- (void)_handleTimerAciton {
    if (_repeatingInterval <= 0) {
        return;
    }
    if (_isFiring) {
        [self _handleFireAction];
    } else {
        [self _onCallback];
    }
}

- (void)_handleFireAction {
    if (_remainingFireCount <= 0) {
        _remainingFireCount = 0;
        _isFiring = NO;
        [self invalidate];
        return;
    }
    _remainingFireCount--;
    [self _onCallback];
}

- (void)_onCallback {
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        !weakSelf.invocationHandler ?: weakSelf.invocationHandler(weakSelf);
    });
}

- (void)resume {
    if (_timer) _timer.fireDate = NSDate.distantPast;
}

- (void)pause {
    if (_timer) _timer.fireDate = NSDate.distantFuture;
}

- (void)invalidate {
    if (_timer) {
        [self.timer invalidate];
        self.timer = nil;
    }
}

@end
