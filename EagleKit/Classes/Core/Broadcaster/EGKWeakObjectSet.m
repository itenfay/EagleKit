//
//  EGKWeakObjectSet.m
//  EagleKit
//
//  Created by Teng Fei on 2023/12/13.
//

#import "EGKWeakObjectSet.h"

@implementation EGKWeakObject

- (instancetype)initWithObject:(NSObject *)object {
    if (self = [super init]) {
        self.object = object;
        self.identifier = [NSString stringWithFormat:@"id_%p", object];
    }
    return self;
}

@end

@interface EGKWeakObjectSet ()
@property (nonatomic, strong) NSMutableArray<EGKWeakObject *> *objects;
@end

@implementation EGKWeakObjectSet

- (instancetype)init {
    self = [super init];
    if (self) {
        self.objects = [NSMutableArray array];
    }
    return self;
}

- (instancetype)initWithObject:(NSObject *)object {
    if (self = [super init]) {
        self.objects = [NSMutableArray arrayWithArray:@[[[EGKWeakObject alloc] initWithObject:object]]];
    }
    return self;
}

- (BOOL)containsObject:(NSObject *)object {
    for (EGKWeakObject *obj in self.objects) {
        if ([obj.object isEqual:object]) {
            return YES;
        }
    }
    return NO;
}

- (NSArray<NSObject *> *)allObjects {
    NSMutableArray<NSObject *> *objs = [NSMutableArray arrayWithCapacity:0];
    NSEnumerator *enumerator = [self.objects objectEnumerator];
    EGKWeakObject *obj;
    while (obj = [enumerator nextObject]) { //obj不为nil时
        if (obj.object) {
            [objs addObject:obj.object];
        }
    }
    return [objs copy];
}

- (NSArray<EGKWeakObject *> *)allWeakObjects {
    NSMutableArray<EGKWeakObject *> *objs = [NSMutableArray arrayWithCapacity:0];
    NSEnumerator *enumerator = [self.objects objectEnumerator];
    EGKWeakObject *obj;
    while (obj = [enumerator nextObject]) { //obj不为nil时
        [objs addObject:obj];
    }
    return [objs copy];
}

- (void)addObject:(NSObject *)object {
    //prevent object.identifier be reused
    if ([self containsObject:object]) {
        [self removeObject:object];
    }
    [self.objects addObject:[[EGKWeakObject alloc] initWithObject:object]];
}

- (void)addObjects:(NSArray<NSObject *> *)objects {
    for (NSObject *object in objects) {
        [self addObject:object];
    }
}

- (void)removeObject:(NSObject *)object {
    NSArray<EGKWeakObject *> *tempArr = [self.objects copy];
    for (EGKWeakObject *obj in tempArr) {
        if ([obj.object isEqual:object]) {
            [self.objects removeObject:obj];
        }
    }
}

- (void)removeObjects:(NSArray<NSObject *> *)objects {
    [objects enumerateObjectsUsingBlock:^(NSObject * _Nonnull object,
                                          NSUInteger idx,
                                          BOOL * _Nonnull stop) {
        [self removeObject:object];
    }];
}

@end
