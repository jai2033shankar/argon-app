//
//  VuforiaDataSet.h
//  Pods
//
//  Created by Gheric Speiginer on 4/1/16.
//
//

#if !(TARGET_IPHONE_SIMULATOR)

#import <Foundation/Foundation.h>
#import "VuforiaSession.h"

@class VuforiaFrame;
@class VuforiaTrackable;
@class VuforiaTrackableResult;
@class VuforiaTrackableSource;
@class VuforiaMultiTarget;

@interface VuforiaDataSet : NSObject

@property (nonatomic, assign) void* cpp;

-(id)initWithCpp:(void*)cpp;

/// Checks if the dataset exists at the specified path and storage location
/**
 *  Returns true if both the dataset XML and DAT file exist at the
 *  given storage location. The relative path to the dataset XML must be
 *  passed to this function for all storage locations other than
 *  STORAGE_ABSOLUTE.
 */
-(BOOL)exists:(NSString*)path storageType:(VuforiaStorageType)storageType;

/// Loads the dataset at the specified path and storage location
/**
 *  Returns true if the dataset was loaded successfully. After loading,
 *  individual Trackables can be accessed using getNumTrackables() and
 *  getTrackable(). The relative path to the dataset XML must be passed to
 *  this function for all storage locations other than STORAGE_ABSOLUTE.
 *  Note that loading a dataset may take significant time and therefore
 *  it is recommended to load datasets in the background.
 */
-(BOOL)load:(NSString*)path storageType:(VuforiaStorageType)storageType;

/// Returns the overall number of 3D trackable objects in this data set.
/**
 *  Trackables that are part of other trackables (e.g. an ImageTarget that
 *  is part of a MultiTarget) is not counted here and not delivered
 *  by DataSet::getTrackable().
 */
-(NSInteger)getNumTrackables;

/// Returns a pointer to a trackable object.
/**
 *  Trackables that are part of other trackables (e.g. an ImageTarget that
 *  is part of a MultiTarget) is not delivered by this method.
 *  Such trackables can be accesses via the trackable they are part of.
 *  E.g. use MultiTarget::getPart() to access the respective ImageTargets.
 */
-(VuforiaTrackable*)getTrackable:(int)idx;

/// Creates a new Trackable from the given TrackableSource and registers
/// it with the dataset
/**
 *  Use DataSet::destroy() to destroy the returned Trackable
 *  if it is no longer required.
 *  This method must not be called while the dataset is active or it will
 *  return NULL.
 */
-(VuforiaTrackable*)createTrackable:(VuforiaTrackableSource*)source;

/// Creates a new MultiTarget and registers it with the dataset
/**
 *  Use DataSet::destroy() to destroy the returned MultiTarget
 *  if it is no longer required.
 *  This method must not be called while the dataset is active or it will
 *  return NULL.
 */
-(VuforiaMultiTarget*)createMultiTarget:(NSString*)name;

/// Destroys a Trackable
/**
 *  This method must not be called while the dataset is active or it will
 *  return false.
 */
-(BOOL)destroy:(VuforiaTrackable*)trackable;

/// Checks if this DataSet's Trackable capacity is reached.
/**
 *  Returns true if the number of Trackables created in this DataSet
 *  has reached the maximum capacity, false otherwise.
 */
-(BOOL)hasReachedTrackableLimit;

/// Checks if this dataset is active
/**
 * Returns true if the dataset is active
 */
-(BOOL)isActive;
@end




#endif
