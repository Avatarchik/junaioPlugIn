//
//  JunaioPluginViewController.h
//  Junaio 4.6.2
//
//  Created by Stefan Misslinger on 8/04/11.
//  Copyright 2012 metaio, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <JunaioPlugin/LiveViewInterfaceController.h>
#import <JunaioPlugin/JunaioPluginDelegate.h>


static const int ANCHOR_NONE =			0<<0;			///< No anchor, i.e. not relative-to-screen (0)
static const int ANCHOR_LEFT =			1<<0;			///< Anchor to the left edge (1)
static const int ANCHOR_RIGHT =			1<<1;			///< Anchor to the right edge (2)
static const int ANCHOR_BOTTOM =		1<<2;			///< Anchor to the bottom edge (4)
static const int ANCHOR_TOP =			1<<3;			///< Anchor to the top edge (8)
static const int ANCHOR_CENTER_H =		1<<4;			///< Anchor to the horizontal center (16)
static const int ANCHOR_CENTER_V =		1<<5;			///< Anchor to the vertical center (32)

static const int ANCHOR_TL = ANCHOR_LEFT|ANCHOR_TOP;				///< Anchor to the Top-Left (9)
static const int ANCHOR_TC = ANCHOR_TOP|ANCHOR_CENTER_H;			///< Anchor to the Top-Center (24)
static const int ANCHOR_TR = ANCHOR_TOP|ANCHOR_RIGHT;				///< Anchor to the Top-Right (10)
static const int ANCHOR_CL = ANCHOR_CENTER_V|ANCHOR_LEFT;			///< Anchor to the Center-Left (33)
static const int ANCHOR_CC = ANCHOR_CENTER_H|ANCHOR_CENTER_V;		///< Anchor to the Center (48)
static const int ANCHOR_CR = ANCHOR_CENTER_V|ANCHOR_RIGHT;			///< Anchor to the Center-Right (34)
static const int ANCHOR_BL = ANCHOR_BOTTOM|ANCHOR_LEFT;				///< Anchor to the Bottom-Left (5)
static const int ANCHOR_BC = ANCHOR_BOTTOM|ANCHOR_CENTER_H;			///< Anchor to the Bottom-Center (20)
static const int ANCHOR_BR = ANCHOR_BOTTOM|ANCHOR_RIGHT;			///< Anchor to the Bottom-Right (6)


@interface JunaioPluginViewController : LiveViewInterfaceController<JunaioPluginDelegate>

/** Informs the application when loading has been completed
 * Note: make sure to call [super onSceneReady] when overwriting this method
 */
- (void)  onSceneReady;


@end
