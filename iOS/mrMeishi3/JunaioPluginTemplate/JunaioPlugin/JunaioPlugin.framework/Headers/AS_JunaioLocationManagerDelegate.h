//
//  AS_JunaioLocationManagerDelegate.h
//  Junaio
//
//  Created by Stefan Misslinger on 09/04/09.
//  Copyright 2009 metaio. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

namespace metaio {
	class SensorsComponentIOS;
}


/** @brief This class is the delegate for the iPhone's core location framework
 * 
 */
@interface JunaioLocationManagerDelegate : NSObject
{
	metaio::SensorsComponentIOS*			m_pSensorsComponent;
	
}

/** Get a pointer to the SensorsComponent
 * \return sensorsComponent
 */
- (metaio::SensorsComponentIOS* ) getSensorComponent;


/** Access the Singleton instance
 * \return the sharedInstance
 */
+ (JunaioLocationManagerDelegate *)sharedInstance;


/** Get the distance from the current location */
+ (CLLocationDistance) getDistanceFromCurrentLocationForLocation: (CLLocation* ) location;

/** Get the distance as a string for the current location 
 * It will use the respective units depending on the current locale
 */
+ (NSString*) getDistanceStringForDistance: (double) distanceInM withAwayStringHidden: (BOOL) awayStringHidden;


@end

