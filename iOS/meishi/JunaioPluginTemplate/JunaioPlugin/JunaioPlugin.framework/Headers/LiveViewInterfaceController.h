//
// LiveViewInterfaceController.h
// Junaio
//
//  Created by Stefan Misslinger on 10/2/09.
//  Copyright 2011 metaio, Inc. All rights reserved.
//

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import <CoreMotion/CoreMotion.h>
#import "AS_JunaioLocationManagerDelegate.h"
#import "WebViewViewController.h"
#import "LiveViewObjectContextView.h"


@class MetaioWorldPOIWrapper;
@class MetaioWorldChannelWrapper;
@class ARELAudioPlayer;

namespace metaio
{    
	class ByteBuffer;
	class GestureHandler;
	
    namespace world
    {
		class MetaioWorldPOI;
        class MetaioWorldPOIManager;
        class IMetaioWorldPOIManagerDelegate;
        class IARELDatasourceDelegate;
        class JunaioDataSource;
    }
}

// forward declarations
@class EAGLView;
@class AVAudioPlayer;


@interface LiveViewInterfaceController : UIViewController
 <UINavigationControllerDelegate, UIWebViewDelegate, UIGestureRecognizerDelegate, LiveViewObjectContextViewDelegate>
{	
    metaio::world::MetaioWorldPOIManager*               m_pPoiManager;       //!< Reference to our poi manager
    metaio::world::IMetaioWorldPOIManagerDelegate*      m_pPoiManagerDelegate;     //!< The PoiManager delegate
    metaio::world::JunaioDataSource*					m_pJunaioDataSource;
	metaio::world::IARELDatasourceDelegate*				m_pDatasourceDelegate;     //!< The Datasource delegate
	metaio::GestureHandler*								m_pGestureHandler;	//! the gesture handler
    
	
    __block   bool      m_cancelSearchRequest;
    dispatch_queue_t    m_requestQueue;
	NSMutableArray*		m_activeDownloadRequests;
	
	
    
    // OpenGL related members (directly taken from XCode4 OpenGL example)
    EAGLContext *context;               // our OpenGL Context
    BOOL animating;                     // are we currently animating
    NSInteger animationFrameInterval;   // refresh interval
    CADisplayLink *displayLink;         // pointer to our displayLink
    
    
    // other objects
	ARELAudioPlayer*					m_arelAudioPlayer;
    AVAudioPlayer*                      m_alertPlayer;
    
	NSMutableDictionary*				m_billboardImageCache;	// temporary cache to speed up billboard loading

    int                                 m_defaultCameraFormat;
	
	
	int		m_channelIDToLoadWhenlocationIsPresent;	//!< Used during startup to postpone loading a channel until a location is present
	
	bool	m_ignoreCancellingRequest;	//!< Should we ignore cancelling all request when leaving the view?
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;


@property (nonatomic, retain) IBOutlet UILabel*                         messageActivityLabel;
@property (nonatomic, retain) IBOutlet LiveViewObjectContextView*		objectContextView;
@property (nonatomic, retain) IBOutlet EAGLView*                        glView;
@property (nonatomic, retain) IBOutlet UIView*							interfaceView;
@property (nonatomic, retain) IBOutlet UIWebView*                       arelWebView;
@property (nonatomic, retain) IBOutlet UIProgressView*                  progressView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView*			activityIndicator;

/** Removes all content and triggers a new pois search */
- (void) reloadCurrentChannel;

/** Override this method if you want to display your webviewcontroller in a different way */
- (void) presentContentViewController: (UIViewController<JunaioContentViewController>*) contentViewController;


/** Implementation to get a billboard image for a poi
 * \param poi the poi
 * \param image the thumbnail of the poi
 * \return the image
 */
- (UIImage*) getBillboardImageForPOI: (const metaio::world::MetaioWorldPOI*) poi withThumbnail: (UIImage*) image;


/** Overwrite this method to provide your own viewcontroller for displaying URLs
 * \param url the URL that should be openend
 * \return autoreleased viewcontroller
 *
 * You can use this method to provide your own WebviewController if desired
 */
- (UIViewController<JunaioContentViewController>*) getContentViewControllerForURL:(NSString*) url;


/** This method allows you to (re)set a channel ID that the plugin will use. Calling this method will cause a complete refresh (i.e. remove all objects and load POIs from the given channel ID again.
 *  Note, this Method will not query the delegate
 *
 * \param channelID the channel ID to set
 * \param filters the filter paramters that should be sent to your channel
 */
- (void) openChannelID:(int) channelID withFilterValues:(NSDictionary*) filters;


/** Returns the currenlty loaded channel ID
 * \return the currenlty loaded channel ID
 */
- (int) getCurrentChannelID;


/** Show an info message on the screen
 * \param message the message
 */
- (void) showInfoMessage: (NSString*) message;


/** Overwrite this method if you want to be able to handle custom URL schemes that are launched
 * from your channel
 * \param request the request that is being sent
 *
 * You can use it like this:
 * NSURL* theURL = [request mainDocumentURL];
 * NSString* absoluteString = [theURL absoluteString];
 * if( [[absoluteString lowercaseString] hasPrefix:@"yourapp://"] )
 * {
 *   // do something
 *   return NO;
 * }
 * return YES;
 */
- (BOOL) shouldStartLoadWithRequest:(NSURLRequest *) request;

/** Define the offset of the radar relative to the upper right corner
 * \param offset the offset in x/y
 * \param scale the relative scale of the radar
 * \param the anchor to set. (default: top-right: 10)
 */
- (void) setRadarOffset:(CGPoint) offset scale:(float) scale anchor:(int) anchor;

@end


@interface LiveViewInterfaceController (OpenGL)
- (void)startAnimation;
- (void)stopAnimation;
@end

