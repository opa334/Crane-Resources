// You can make a class that conforms to this protocol and add it to CraneManager using the addObserver: method
// Then you will get notified when some setting has changed
@protocol CraneManagerObserver

@optional
- (void)didChangeRootSettings;
- (void)didChangeSettingsForApplicationWithIdentifier:(NSString*)applicationID;
- (void)didChangeContainersOfApplicationWithIdentifier:(NSString*)applicationID;
- (void)didChangeContainerSettingsForContainerWithIdentifier:(NSString*)containerID onApplicationWithIdentifier:(NSString*)applicationID;

@end

typedef NS_ENUM(NSInteger, ContainerPathType) {
    ContainerPathTypeApp,
    ContainerPathTypeGroup,
	ContainerPathTypePlugin
};

@interface CraneManager : NSObject

+ (instancetype)sharedManager;

// prefs
- (NSDictionary*)preferencesCopy;
- (void)setPreferenceValue:(id)value forKey:(NSString*)key;
- (void)removePreferenceValueForKey:(NSString*)key;
- (id)preferenceValueForKey:(NSString*)key;

// observers
- (void)addObserver:(NSObject<CraneManagerObserver>*)observer;
- (void)removeObserver:(NSObject<CraneManagerObserver>*)observer;

// app settings
- (BOOL)isApplicationSupportedByCrane:(NSString*)applicationID;
- (NSArray*)identfiersOfApplicationsThatHaveNonDefaultContainers;
- (NSArray*)identifiersOfAllSupportedApplications;
- (NSString*)displayNameForApplicationWithIdentifier:(NSString*)applicationID;
- (NSDictionary*)applicationSettingsForApplicationWithIdentifier:(NSString*)applicationID;
- (void)setApplicationSettings:(NSDictionary*)appSettings forApplicationWithIdentifier:(NSString*)applicationID;
- (NSString*)activeContainerIdentifierForApplicationWithIdentifier:(NSString*)applicationID;
- (void)setActiveContainerIdentifier:(NSString*)containerID forApplicationWithIdentifier:(NSString*)applicationID; // does not respect biometric protection setting
- (void)setActiveContainerIdentifier:(NSString*)containerID forApplicationWithIdentifier:(NSString*)applicationID usingBiometricsIfNeededWithSuccessHandler:(void (^)(BOOL))successHandler; //respects biometric protection setting and does authentication if neccessary
- (NSArray*)containerIdentifiersOfApplicationWithIdentifier:(NSString*)applicationID;

// container management
- (void)createNewContainerWithName:(NSString*)containerName andIdentifier:(NSString*)containerID forApplicationWithIdentifier:(NSString*)applicationID;
- (NSString*)createNewContainerWithName:(NSString*)containerName forApplicationWithIdentifier:(NSString*)applicationID; // returns containerIdentifier
- (void)deleteContentOfContainerWithIdentifier:(NSString *)containerID forApplicationWithIdentifier:(NSString *)applicationID;
- (void)deleteContainerWithIdentifier:(NSString*)containerID forApplicationWithIdentifier:(NSString*)applicationID;
- (void)wipeContainerWithIdentifier:(NSString*)containerIdD forApplicationWithIdentifier:(NSString*)applicationID shouldRepopulate:(BOOL)repopulate;
- (NSString*)makeDefaultForContainerWithIdentifier:(NSString*)containerID forApplicationWithIdentifier:(NSString*)applicationID;

// containers settings
- (NSDictionary*)containerSettingsForContainerWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID;
- (void)setContainerSettings:(NSDictionary*)containerSettings forContainerWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID;
- (void)enumerate:(void (^)(ContainerPathType type, NSString* identifier, NSString* path))block pathsAssociatedToContainerWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID;
- (NSDictionary*)pathsAssociatedToContainerWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID;
- (void)sizeOccupiedByContainerWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID completionHandler:(void (^)(uint64_t))completionHandler;
- (NSString*)displayNameForContainerWithName:(NSString*)containerName isDefaultContainer:(BOOL)isDefault shouldUseShortVersion:(BOOL)shortVersion;
- (NSString*)displayNameForContainerWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID shouldUseShortVersion:(BOOL)shortVersion;

// name to display in notifications
- (NSString*)displayNameForContainerInNotificationWithIdentifier:(NSString*)containerID ofApplicationWithIdentifier:(NSString*)applicationID;
- (NSString*)containerNameToDisplayInNotificationWithUserInfoOrContext:(NSDictionary*)userInfoOrContext ofApplicationWithIdentifier:(NSString*)applicationID;

// SpringBoard
- (void)flushCFPrefsdCacheForApplicationWithIdentifier:(NSString*)applicationID;
- (void)reloadApplicationWithIdentifier:(NSString*)applicationID;

@end