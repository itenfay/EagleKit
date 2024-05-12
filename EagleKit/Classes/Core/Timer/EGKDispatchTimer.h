//
//  EGKDispatchTimer.h
//  EagleKit
//
//  Created by Teng Fei on 2023/12/12.
//

#import <Foundation/Foundation.h>

/// Usage:
//@property (nonatomic, copy) NSString *taskIdetifier; /** The timer identifier. */

/// Create timer and return the timer identifier.
//self.taskIdetifier = [EGKDispatchTimer execTask:^{
//  //code
//} start:0.0 interval:1.0 repeats:YES async:NO];

/// Cancels timer by the timer identifier.
//[EGKDispatchTimer cancelTimerTask:self.timerId];

@interface EGKDispatchTimer : NSObject

/// Executes the task with specified parameters and return a timer identifier.
/// - Parameters:
///   - task: The task to be executed.
///   - start: The start interval time.
///   - interval: The interval time of timer.
///   - repeats: Whether it is repeated or not.
///   - async: Whether it is asynchronous or not.
+ (NSString *)execTask:(void(^)(void))task
                 start:(NSTimeInterval)start
              interval:(NSTimeInterval)interval
               repeats:(BOOL)repeats
                 async:(BOOL)async;

/// Executes the selector of the target with specified parameters and return a timer identifier.
/// - Parameters:
///   - target: The target of the added timer.
///   - selector: The callback method.
///   - start: The start interval time.
///   - interval: The interval time of timer.
///   - repeats: Whether it is repeated or not.
///   - async: Whether it is asynchronous or not.
+ (NSString *)execTarget:(id)target
                selector:(SEL)selector
                   start:(NSTimeInterval)start
                interval:(NSTimeInterval)interval
                 repeats:(BOOL)repeats
                   async:(BOOL)async;

/// Cancels timer with the timer identifier.
/// - Parameter taskIdetifier: The unique identifier of the timer.
+ (void)cancelTimerTask:(NSString *)taskIdetifier;

@end
