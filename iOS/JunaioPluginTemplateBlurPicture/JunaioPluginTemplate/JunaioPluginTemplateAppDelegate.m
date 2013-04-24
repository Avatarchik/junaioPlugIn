//
//  JunaioPluginTemplateAppDelegate.m
//  Junaio Plugin
//
//  Created by Stefan Misslinger on 3/15/11.
//  Copyright 2011 metaio, Inc. All rights reserved.
//

#import "JunaioPluginTemplateAppDelegate.h"

@implementation JunaioPluginTemplateAppDelegate

@synthesize window=_window;
@synthesize viewController=_viewController;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    self.window.rootViewController = self.viewController;
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application
{

}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{

}

- (void)applicationWillTerminate:(UIApplication *)application
{

}

- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}

@end
