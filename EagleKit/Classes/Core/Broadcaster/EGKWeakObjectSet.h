//
//  EGKWeakObjectSet.h
//  EagleKit
//
//  Created by Teng Fei on 2023/12/13.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface EGKWeakObject : NSObject

@property (nonatomic, weak) NSObject *object;
@property (nonatomic, copy) NSString *identifier;

- (instancetype)initWithObject:(NSObject *)object;

@end

@interface EGKWeakObjectSet : NSObject

- (instancetype)initWithObject:(NSObject *)object;

- (BOOL)containsObject:(NSObject *)object;
- (NSArray<NSObject *> *)allObjects;
- (NSArray<EGKWeakObject *> *)allWeakObjects;

- (void)addObject:(NSObject *)object;
- (void)addObjects:(NSArray<NSObject *> *)objects;

- (void)removeObject:(NSObject *)object;
- (void)removeObjects:(NSArray<NSObject *> *)objects;

@end

NS_ASSUME_NONNULL_END
