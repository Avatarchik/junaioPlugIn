//
//  JunaioContentViewController.h
//  Junaio
//
//  Created by Stefan Misslinger.
//  Copyright 2012 metaio, Inc.. All rights reserved.
//

#import <UIKit/UIKit.h>

// Block that will perform an action
typedef void (^JunaioContentViewControllerActionBlock)(void);

@protocol JunaioContentViewController
/** Set the block that will be executed on viewDidDisappear
 * In Junaio this is used to provide callbacks to the Junaio engine, that a webview or videoview has been closed.
 */
-(void) setViewDidDisappearBlock:(JunaioContentViewControllerActionBlock) block;

@end
