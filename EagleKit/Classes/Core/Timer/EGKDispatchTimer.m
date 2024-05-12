//
//  EGKDispatchTimer.m
//  EagleKit
//
//  Created by Teng Fei on 2023/12/12.
//

#import "EGKDispatchTimer.h"

@interface EGKDispatchTimer ()

@end

@implementation EGKDispatchTimer

static NSMutableDictionary *_timers;
static dispatch_semaphore_t _semaphore;

+ (void)initialize {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _timers = [NSMutableDictionary dictionary];
        _semaphore = dispatch_semaphore_create(1);
    });
}

+ (NSString *)execTask:(void (^)(void))task start:(NSTimeInterval)start interval:(NSTimeInterval)interval repeats:(BOOL)repeats async:(BOOL)async {
    if (!task || start < 0 || (interval <= 0 && repeats)) return nil;
    
    //Gets a queue.
    dispatch_queue_t queue = async ? dispatch_get_global_queue(0, 0) : dispatch_get_main_queue();
    //Creates a timer.
    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    //Sets up time.
    dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, start*NSEC_PER_SEC), interval*NSEC_PER_SEC, 0);
    
    //Lock
    dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
    //The unique identifier of the timer.
    NSString *name = [NSString stringWithFormat:@"%zd", _timers.count];
    _timers[name] = timer;
    //Sends signal (unlock).
    dispatch_semaphore_signal(_semaphore);
    
    //Sets up callback.
    dispatch_source_set_event_handler(timer, ^{
        task();
        if (!repeats) { //Non repetitive task.
            [self cancelTimerTask:name];
        }
    });
    
    //Starts the timer.
    dispatch_resume(timer);
    
    return name;
}

+ (NSString *)execTarget:(id)target selector:(SEL)selector start:(NSTimeInterval)start interval:(NSTimeInterval)interval repeats:(BOOL)repeats async:(BOOL)async {
    if (!target || !selector) return nil;
    
    return [self execTask:^{
        if ([target respondsToSelector:selector]) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
            [target performSelector:selector];
#pragma clang diagnostic pop
        }
    } start:start interval:interval repeats:repeats async:async];
}

+ (void)cancelTimerTask:(NSString *)taskIdetifier {
    if (taskIdetifier.length == 0) {
        return;
    }
    //Lock
    dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
    dispatch_source_t timer = _timers[taskIdetifier];
    if (timer) {
        dispatch_source_cancel(_timers[taskIdetifier]);
        [_timers removeObjectForKey:taskIdetifier];
    }
    //Sends signal (unlock).
    dispatch_semaphore_signal(_semaphore);
}

@end
