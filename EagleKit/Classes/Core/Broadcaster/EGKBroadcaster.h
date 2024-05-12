//
//  EGKBroadcaster.h
//  EagleKit
//
//  Created by Teng Fei on 2023/12/13.
//

#import <Foundation/Foundation.h>

#define EGK_FORCE_INLINE __inline__ __attribute__((always_inline))

static EGK_FORCE_INLINE void EGKPrint(NSString * _Nullable logString) {
#if DEBUG
    NSLog(@"[EGK] %@", logString);
#endif
}

@class EGKBroadcaster;

/// The macro for registering an observer.
#ifndef EGK_Register_Observer
#define EGK_Register_Observer(protocolName, instance) [EGKBroadcaster register:@protocol(protocolName) observer:instance]
#endif
/// The macro for unregistering an observer.
#ifndef macroEGK_Unregister_Observer
#define EGK_Unregister_Observer(protocolName, instance) [EGKBroadcaster unregister:@protocol(protocolName) observer:instance]
#endif

/// The macro for getting all observers implementing this protocol.
#ifndef EGK_Get_Observers
#define EGK_Get_Observers(protocolName) [EGKBroadcaster observersForProtocol:@protocol(protocolName)]
#endif

/// The macro for notifying all observers to execute the action.
#ifndef EGK_Broadcaster_Notify
#define EGK_Broadcaster_Notify(protocolName, selector, func)                           \
[EGKBroadcaster notify:@protocol(protocolName) block:^(NSObject * _Nonnull observer) { \
    if ([observer respondsToSelector:selector]) {                                      \
        EGKPrint([NSString stringWithFormat:@"%@ impl the method: %@", observer, NSStringFromSelector(selector)]);\
        id<protocolName> _observer = (id<protocolName>)observer;                       \
        [_observer func];                                                              \
    } else {                                                                           \
        EGKPrint([NSString stringWithFormat:@"%@ didn't impl the method: %@", observer, NSStringFromSelector(selector)]);\
    }                                                                                  \
}]
#endif

NS_ASSUME_NONNULL_BEGIN

@interface EGKBroadcaster : NSObject

/// Register an observer.
+ (void)register:(Protocol *)protocol observer:(NSObject *)observer;
/// Unregister an observer.
+ (void)unregister:(Protocol *)protocol observer:(NSObject *)observer;
/// Get all observers implementing this protocol.
+ (NSArray<NSObject *> *)observersForProtocol:(Protocol *)protocol;
/// Notify all observers implementing this protocol.
+ (void)notify:(Protocol *)protocol block:(void (^)(NSObject *observer))block;

/// Call this  when the application is about to terminate.
+ (void)destroy;

@end

NS_ASSUME_NONNULL_END
