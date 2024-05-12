//
//  ViewController.m
//  EagleKit
//
//  Created by Teng Fei on 02/21/2024.
//  Copyright (c) 2024 Teng Fei. All rights reserved.
//

#import "ViewController.h"
//@import EagleKit;
#import "EGKMacros.h"
#import "EGKBroadcaster.h"

@protocol ICall <NSObject>

- (void)call;

@optional
- (void)sendData:(NSData *)data toUser:(NSString *)userId;

@end

@interface ViewController () <ICall>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    EGK_Run_Safely_OnMainThread(^{
        EGKLog(@"Main Thread!!!");
    });
    
    EGK_Dispatch_After(0.4, ^{
        
    });
    
    EGK_Open_URL(@"");
    EGK_Open_URL_WithBlock(@"", ^(BOOL suc){
        
    });
    
    
    NSString *urlString = @"https://baidu.com";
    if (EGK_Can_Open_URL(urlString)) {
    }
    EGK_Register_Observer(ICall, self);
    
    NSArray *observers = EGK_Get_Observers(ICall);
    EGKLog("[I] observers: %@", observers);
    for (NSObject *obj in observers) {
        EGKLog("[I] obj.class: %@", obj.class);
        // 判断obj是否是`ViewController`的实例
        if ([obj isMemberOfClass:self.class]) {
            EGK_Send_Message(obj, ICall, call);
        }
    }
    
    EGK_Dispatch_After(10, ^{
        //EGK_Unregister_Observer(ICall, self);
    });
    
    EGK_Get_I18N_String(@"sss");
}

- (void)call {
    EGKLog("");
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    EGK_Broadcaster_Notify(ICall, @selector(call), call);
    EGK_Broadcaster_Notify(ICall, @selector(sendData:toUser:), sendData:[@"jxff999aerwq" dataUsingEncoding:NSUTF8StringEncoding] toUser:@"1233423");
}

- (void)dealloc {
    EGK_Unregister_Observer(ICall, self);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
