//
//  EGKBroadcaster.m
//  EagleKit
//
//  Created by Teng Fei on 2023/12/13.
//

#import "EGKBroadcaster.h"
#import "EGKWeakObjectSet.h"

static NSMutableDictionary *_observersDic;
static dispatch_queue_t _notificationQueue;
static dispatch_semaphore_t _sema;

@interface EGKBroadcaster ()

@end

@implementation EGKBroadcaster

+ (void)initialize {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _observersDic = [NSMutableDictionary dictionaryWithCapacity:0];
        _notificationQueue = dispatch_queue_create("com.egk.broadcaster.dispatch.queue", DISPATCH_QUEUE_CONCURRENT);
        _sema = dispatch_semaphore_create(1);
    });
}

+ (void)register:(Protocol *)protocol observer:(NSObject *)observer {
    NSString *key = NSStringFromProtocol(protocol);
    if (![observer conformsToProtocol:protocol]) {
        NSString *desc = [NSString stringWithFormat:@"The observer doesn't conforms to this protocol: %@", key];
        NSAssert(0, desc);
        return;
    }
    [self safeSaveForKey:key object:observer];
}

+ (void)unregister:(Protocol *)protocol observer:(NSObject *)observer {
    NSString *key = NSStringFromProtocol(protocol);
    [self safeRemoveForKey:key object:observer];
}

+ (NSArray<NSObject *> *)observersForProtocol:(Protocol *)protocol {
    NSMutableArray<NSObject *> *objArray = [NSMutableArray array];
    NSString *key = NSStringFromProtocol(protocol);
    EGKWeakObjectSet *objectSet = [self safeGetObjectSetForKey:key];
    if (!objectSet) return [objArray copy];
    for (NSObject *observer in objectSet.allObjects) {
        [objArray addObject:observer];
    }
    return [objArray copy];
}

+ (void)notify:(Protocol *)protocol block:(void (^)(NSObject *observer))block {
    NSString *key = NSStringFromProtocol(protocol);
    EGKWeakObjectSet *objectSet = [self safeGetObjectSetForKey:key];
    if (!objectSet) return;
    for (NSObject *observer in objectSet.allObjects) {
        if (observer) {
            !block ?: block(observer);
        }
    }
}

+ (void)safeSaveForKey:(NSString *)key object:(NSObject *)object {
    dispatch_semaphore_wait(_sema, DISPATCH_TIME_FOREVER);
    dispatch_barrier_async(_notificationQueue, ^{
        EGKWeakObjectSet *set = (EGKWeakObjectSet *)[_observersDic objectForKey:key];
        if (set) {
            [set addObject:object];
            [_observersDic setValue:set forKey:key];
        } else {
            EGKWeakObjectSet *objectSet = [[EGKWeakObjectSet alloc] initWithObject:object];
            [_observersDic setValue:objectSet forKey:key];
        }
        dispatch_semaphore_signal(_sema);
    });
}

+ (void)safeRemoveForKey:(NSString *)key object:(NSObject *)object {
    dispatch_semaphore_wait(_sema, DISPATCH_TIME_FOREVER);
    dispatch_barrier_async(_notificationQueue, ^{
        EGKWeakObjectSet *set = (EGKWeakObjectSet *)[_observersDic objectForKey:key];
        if (set) {
            [set removeObject:object];
            [_observersDic setValue:set forKey:key];
        }
        // Check and handle cases where the object is nil.
        for (EGKWeakObjectSet *weakObjSet in _observersDic.allValues) {
            for (EGKWeakObject *weakObj in weakObjSet.allWeakObjects) {
                if (weakObj && weakObj.object == nil) {
                    [weakObjSet removeObject:weakObj];
                }
            }
        }
        dispatch_semaphore_signal(_sema);
    });
}

+ (EGKWeakObjectSet *)safeGetObjectSetForKey:(NSString *)key {
    __block EGKWeakObjectSet *objectSet = nil;
    dispatch_sync(_notificationQueue, ^{
        objectSet = (EGKWeakObjectSet *)[_observersDic objectForKey:key];
    });
    return objectSet;
}

+ (void)destroy {
    [_observersDic removeAllObjects];
    _observersDic = nil;
    _notificationQueue = nil;
    _sema = nil;
}

@end
