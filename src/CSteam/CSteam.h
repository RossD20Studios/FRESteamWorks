/*
 *  CSteam.h
 *  This file is part of FRESteamWorks.
 *
 *  Created by David ´Oldes´ Oliva on 3/29/12.
 *  Contributors: Ventero <http://github.com/Ventero>
 *  Copyright (c) 2012 Amanita Design. All rights reserved.
 *  Copyright (c) 2012-2013 Level Up Labs, LLC. All rights reserved.
 */

#ifndef CSTEAM_H
#define CSTEAM_H

#if (defined(_MSC_VER) && (_MSC_VER < 1900))
	#define snprintf _snprintf
#endif

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <queue>

#include <steam/steam_api.h>

#include "CTypes.h"

class CSteam {
public:
	CSteam();
	virtual ~CSteam();
	bool Initialize();
	bool Initialized() const { return m_bInitialized; }
	void SetWarningMessageHook(SteamAPIWarningMessageHook_t hook);

	// general stuff
	CSteamID GetUserID();
	uint32 GetAppID();
	std::string GetAvailableGameLanguages();
	std::string GetCurrentGameLanguage();
	std::string GetPersonaName();
	std::string GetIPCountry();

	uint32 GetEarliestPurchaseUnixTime(AppId_t appId);
	uint32 GetSecondsSinceAppActive();
	uint32 GetServerRealTime();

	bool IsSteamInBigPictureMode();
	bool IsSteamRunningOnSteamDeck();


	// stats/achievements
	// bool RequestStats(); No Longer Required and Removed from SteamWorks
	bool SetAchievement(std::string name);
	bool ClearAchievement(std::string name);
	bool IsAchievement(std::string name);

	bool IsAchievementEarned(std::string name);
	bool GetAchievementAchievedPercent(std::string name, float* value);
	std::string GetAchievementDisplayAttribute(std::string name, std::string atribute);
	std::string GetAchievementName(uint32 index);
	Image GetAchievementIcon(std::string name);
	uint32 GetNumAchievements();

	bool IndicateAchievementProgress(std::string name, uint32 currentProgress,
		uint32 maxProgress);
	bool GetStat(std::string name, int32 *value);
	bool GetStat(std::string name, float *value);
	bool SetStat(std::string name, int32 value);
	bool SetStat(std::string name, float value);
	bool StoreStats();
	bool ResetAllStats(bool bAchievementsToo);
	bool RequestGlobalStats(int days);
	bool GetGlobalStat(std::string name, int64 *value);
	bool GetGlobalStat(std::string name, double *value);
	std::vector<int64> GetGlobalStatHistoryInt(std::string name, uint32 days);
	std::vector<double> GetGlobalStatHistoryFloat(std::string name, uint32 days);

	// leaderboards
	bool FindLeaderboard(std::string name);
	bool FindOrCreateLeaderboard(std::string name, ELeaderboardSortMethod sort,
		ELeaderboardDisplayType display);
	SteamLeaderboard_t FindLeaderboardResult();
	std::string GetLeaderboardName(SteamLeaderboard_t handle);
	int GetLeaderboardEntryCount(SteamLeaderboard_t handle);
	ELeaderboardSortMethod GetLeaderboardSortMethod(SteamLeaderboard_t handle);
	ELeaderboardDisplayType GetLeaderboardDisplayType(SteamLeaderboard_t handle);
	bool UploadLeaderboardScore(SteamLeaderboard_t handle,
		ELeaderboardUploadScoreMethod method, int32 score,
		const int32* scoreDetails, int detailscount);
	LeaderboardScoreUploaded_t* UploadLeaderboardScoreResult();
	bool DownloadLeaderboardEntries(SteamLeaderboard_t handle,
		ELeaderboardDataRequest request,
		int rangeStart, int rangeEnd);
	std::vector<LeaderboardEntry> DownloadLeaderboardEntriesResult(int maxDetails);

	// remote storage
	int32 GetFileCount();
	int32 GetFileSize(std::string name);
	bool FileExists(std::string name);
	bool FileWrite(std::string name, const void* data, int32 length);
	int32 FileRead(std::string name, char** data);
	bool FileDelete(std::string name);
	bool FileShare(std::string name);
	UGCHandle_t FileShareResult();
	bool IsCloudEnabledForApp();
	bool SetCloudEnabledForApp(bool enabled);
	bool GetQuota(uint64 *total, uint64 *available);

	// workshop/ugc
	bool UGCDownload(UGCHandle_t handle, uint32 priority);
	int32 UGCRead(UGCHandle_t handle, int32 size, uint32 offset, char **content);
	bool GetUGCDownloadProgress(UGCHandle_t handle, int32 *downloaded, int32 *expected);
	RemoteStorageDownloadUGCResult_t* GetUGCDownloadResult(UGCHandle_t handle);

	bool PublishWorkshopFile(std::string name, std::string preview, AppId_t nConsumerAppId,
		std::string title, std::string description, ERemoteStoragePublishedFileVisibility visibility,
		SteamParamStringArray_t *tags, EWorkshopFileType fileType);
	PublishedFileId_t PublishWorkshopFileResult();
	bool DeletePublishedFile(PublishedFileId_t file);

	bool GetPublishedFileDetails(PublishedFileId_t file, uint32 maxAge);
	RemoteStorageGetPublishedFileDetailsResult_t* GetPublishedFileDetailsResult(PublishedFileId_t file);

	bool EnumerateUserPublishedFiles(uint32 startIndex);
	RemoteStorageEnumerateUserPublishedFilesResult_t* EnumerateUserPublishedFilesResult();
	bool EnumeratePublishedWorkshopFiles(EWorkshopEnumerationType type, uint32 start, uint32 count,
		uint32 days, SteamParamStringArray_t *tags, SteamParamStringArray_t *userTags);
	RemoteStorageEnumerateWorkshopFilesResult_t* EnumeratePublishedWorkshopFilesResult();

	bool EnumerateUserSubscribedFiles(uint32 startIndex);
	RemoteStorageEnumerateUserSubscribedFilesResult_t* EnumerateUserSubscribedFilesResult();

	bool EnumerateUserSharedWorkshopFiles(CSteamID steamId, uint32 startIndex,
		SteamParamStringArray_t *requiredTags, SteamParamStringArray_t *excludedTags);
	RemoteStorageEnumerateUserSharedWorkshopFilesResult_t* EnumerateUserSharedWorkshopFilesResult();

	bool EnumeratePublishedFilesByUserAction(EWorkshopFileAction action, uint32 startIndex);
	RemoteStorageEnumeratePublishedFilesByUserActionResult_t* EnumeratePublishedFilesByUserActionResult();

	bool SubscribePublishedFile(PublishedFileId_t file);
	bool UnsubscribePublishedFile(PublishedFileId_t file);

	PublishedFileUpdateHandle_t CreatePublishedFileUpdateRequest(PublishedFileId_t file);
	bool UpdatePublishedFileFile(PublishedFileUpdateHandle_t handle, std::string file);
	bool UpdatePublishedFilePreviewFile(PublishedFileUpdateHandle_t handle, std::string preview);
	bool UpdatePublishedFileTitle(PublishedFileUpdateHandle_t handle, std::string title);
	bool UpdatePublishedFileDescription(PublishedFileUpdateHandle_t handle, std::string description);
	bool UpdatePublishedFileSetChangeDescription(PublishedFileUpdateHandle_t handle, std::string changeDesc);
	bool UpdatePublishedFileVisibility(PublishedFileUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility visibility);
	bool UpdatePublishedFileTags(PublishedFileUpdateHandle_t handle, SteamParamStringArray_t *tags);
	bool CommitPublishedFileUpdate(PublishedFileUpdateHandle_t handle);

	bool GetPublishedItemVoteDetails(PublishedFileId_t file);
	RemoteStorageGetPublishedItemVoteDetailsResult_t* GetPublishedItemVoteDetailsResult();
	bool GetUserPublishedItemVoteDetails(PublishedFileId_t file);
	RemoteStorageUserVoteDetails_t* GetUserPublishedItemVoteDetailsResult();
	bool UpdateUserPublishedItemVote(PublishedFileId_t file, bool upvote);

	bool SetUserPublishedFileAction(PublishedFileId_t file, EWorkshopFileAction action);

	// friends
	int GetFriendCount(int flags);
	CSteamID GetFriendByIndex(int index, int flags);
	std::string GetFriendPersonaName(CSteamID steamId);
	Image GetSmallFriendAvatar(CSteamID steamId);
	Image GetMediumFriendAvatar(CSteamID steamId);
	Image GetLargeFriendAvatar(CSteamID steamId);

	int GetCoplayFriendCount();
	CSteamID GetCoplayFriend(int index);

	// rich presence
	bool SetRichPresence(std::string key, std::string value);
	bool ClearRichPresence();
	//

	bool SetPlayedWith(CSteamID steamId);
	
	// authentication & ownership
	HAuthTicket GetAuthSessionTicket(char** data, uint32* length, CSteamID steamID);
	HAuthTicket GetAuthSessionTicketResult();
	EBeginAuthSessionResult BeginAuthSession(const void* data, int length, CSteamID steamId);
	bool EndAuthSession(CSteamID steamId);
	bool CancelAuthTicket(HAuthTicket handle);
	EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamId, AppId_t appId);
	bool RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude);
	bool GetEncryptedAppTicket(char** data, uint32* length);

	// overlay
	bool ActivateGameOverlay(std::string dialog);
	bool ActivateGameOverlayToUser(std::string dialog, CSteamID steamId);
	bool ActivateGameOverlayToWebPage(std::string url);
	bool ActivateGameOverlayToStore(AppId_t appId, EOverlayToStoreFlag flag);
	bool ActivateGameOverlayInviteDialog(CSteamID lobbyId);
	bool IsOverlayEnabled();
	bool OverlayNeedsPresent();
	bool SetOverlayNotificationPosition(ENotificationPosition pos);
	bool SetOverlayNotificationInset(int hInset, int vInset);	

	// DLC / subscriptions
	bool IsSubscribedApp(AppId_t appId);
	bool IsDLCInstalled(AppId_t appId);
	int32 GetDLCCount();
	bool InstallDLC(AppId_t appId);
	bool UninstallDLC(AppId_t appId);
	AppId_t DLCInstalledResult();

	// Microtransaction
	bool MicroTxnResult(MicroTxnAuthorizationResponse_t* out);
    
    // input
    bool InitInput();
    uint64_t GetControllerForGamepadIndex(int index);
    bool ShowBindingPanel(uint64 inputHandle);
    uint64_t GetActionSetHandle(std::string actionSetName);
    uint64_t GetDigitalActionHandle(std::string actionName);
    uint64_t GetAnalogActionHandle(std::string actionName);
    InputDigitalActionData_t GetDigitalActionData(uint64 inputHandle, uint64 digitalActionHandle);
    InputAnalogActionData_t GetAnalogActionData(uint64 inputHandle, uint64 analogActionHandle);
    bool RunFrame();
	int GetConnectedControllers(InputHandle_t *handlesOut);
    void ActivateActionSet(uint64 inputHandle, uint64 actionSetHandle);
    uint64_t GetHandleAllControllers();
    int GetDigitalActionOrigins(InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputDigitalActionHandle_t digitalActionHandle, EInputActionOrigin *originsOut);
    int GetAnalogActionOrigins(InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputAnalogActionHandle_t analogActionHandle, EInputActionOrigin *originsOut);
    const char * GetGlyphSVGForActionOrigin(EInputActionOrigin eOrigin, uint32 unFlags);
    const char * GetGlyphPNGForActionOrigin(EInputActionOrigin eOrigin, ESteamInputGlyphSize eSize, uint32 unFlags);
    const char *GetStringForActionOrigin(EInputActionOrigin eOrigin);
    bool ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32 unCharMax, const char *pchExistingText);
    bool ShowFloatingGamepadTextInput(EFloatingGamepadTextInputMode eKeyboardMode, int nTextFieldXPosition, int nTextFieldYPosition, int nTextFieldWidth, int nTextFieldHeight);
    bool SteamInputShutdown();
    bool DismissFloatingGamepadTextInput();
	void SetLEDColor(InputHandle_t inputHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags);
	void TriggerVibration(InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed);
	ESteamInputType GetInputTypeForHandle(InputHandle_t inputHandle);
	EInputActionOrigin TranslateActionOrigin(ESteamInputType eDestinationInputType, EInputActionOrigin eSourceOrigin);
    

protected:
	virtual void DispatchEvent(char* code, char* level) = 0;

private:
	// 	CSteamAPIContext m_ctx; // there is no longer a CSteamAPIContext
	// Our current appId
	uint32 m_iAppID;
	bool m_bInitialized;

	// the most recently received *Result
	SteamLeaderboard_t m_CurrentLeaderboard;
	UGCHandle_t m_FileHandle;
	PublishedFileId_t m_PublishedFileId;
	HAuthTicket m_ActualAuthTicket;
	AppId_t m_DLCInstalled;

	std::map<UGCHandle_t, RemoteStorageDownloadUGCResult_t> m_DownloadResults;
	std::map<PublishedFileId_t, RemoteStorageGetPublishedFileDetailsResult_t> m_PublishedFileDetails;
	std::queue<MicroTxnAuthorizationResponse_t> m_MicroTxnResponses;

	Image GetImageData(int image_handle);

	// can't use unique_ptr because we need to target OS X 10.6 ...
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	std::auto_ptr<LeaderboardScoreUploaded_t> m_ScoreUpload;
	std::auto_ptr<LeaderboardScoresDownloaded_t> m_ScoreDownloaded;
	std::auto_ptr<RemoteStorageEnumerateUserPublishedFilesResult_t> m_UserPublishedFiles;
	std::auto_ptr<RemoteStorageEnumerateWorkshopFilesResult_t> m_WorkshopFiles;
	std::auto_ptr<RemoteStorageEnumerateUserSubscribedFilesResult_t> m_SubscribedFiles;
	std::auto_ptr<RemoteStorageEnumerateUserSharedWorkshopFilesResult_t> m_UserSharedFiles;
	std::auto_ptr<RemoteStorageEnumeratePublishedFilesByUserActionResult_t> m_PublishedFilesByAction;
	std::auto_ptr<RemoteStorageGetPublishedItemVoteDetailsResult_t> m_PublishedItemVoteDetails;
	std::auto_ptr<RemoteStorageUserVoteDetails_t> m_UserPublishedItemVoteDetails;
#pragma GCC diagnostic pop

	void DispatchEvent(const int req_type, const int response);

	/*
	 * callbacks / call results
	 */

#define STEAM_CALLRESULT(thisclass, func, param, var) \
		CCallResult<thisclass, param> var; \
		void func(param*, bool)

	// stats/achievements
	STEAM_CALLBACK(CSteam, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteam, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteam, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);
	STEAM_CALLBACK(CSteam, OnUserAchievementIconFetched, UserAchievementIconFetched_t, m_CallbackAchievementIconFetched);
	STEAM_CALLRESULT(CSteam, OnRequestGlobalStats, GlobalStatsReceived_t, m_CallbackRequestGlobalStats);
	
	// friends
	STEAM_CALLBACK(CSteam, OnAvatarImageLoaded, AvatarImageLoaded_t, m_CallbackAvatarImageLoaded);
	
	// leaderboards
	STEAM_CALLRESULT(CSteam, OnFindLeaderboard,
	                 LeaderboardFindResult_t,
	                 m_CallbackFindLeaderboard);
	STEAM_CALLRESULT(CSteam, OnUploadLeaderboardScore,
	                 LeaderboardScoreUploaded_t,
	                 m_CallbackUploadLeaderboardScore);
	STEAM_CALLRESULT(CSteam, OnDownloadLeaderboardEntries,
	                 LeaderboardScoresDownloaded_t,
	                 m_CallbackDownloadLeaderboardEntries);

	// workshop
	STEAM_CALLRESULT(CSteam, OnFileShare,
	                 RemoteStorageFileShareResult_t,
	                 m_CallbackFileShare);
	STEAM_CALLRESULT(CSteam, OnUGCDownload,
	                 RemoteStorageDownloadUGCResult_t,
	                 m_CallbackUGCDownload);
	STEAM_CALLRESULT(CSteam, OnPublishWorkshopFile,
	                 RemoteStoragePublishFileResult_t,
	                 m_CallbackPublishWorkshopFile);
	STEAM_CALLRESULT(CSteam, OnDeletePublishedFile,
	                 RemoteStorageDeletePublishedFileResult_t,
	                 m_CallbackDeletePublishedFile);
	STEAM_CALLRESULT(CSteam, OnGetPublishedFileDetails,
	                 RemoteStorageGetPublishedFileDetailsResult_t,
	                 m_CallbackGetPublishedFileDetails);
	STEAM_CALLRESULT(CSteam, OnEnumerateUserPublishedFiles,
	                 RemoteStorageEnumerateUserPublishedFilesResult_t,
	                 m_CallbackEnumerateUserPublishedFiles);
	STEAM_CALLRESULT(CSteam, OnEnumeratePublishedWorkshopFiles,
	                 RemoteStorageEnumerateWorkshopFilesResult_t,
	                 m_CallbackEnumeratePublishedWorkshopFiles);
	STEAM_CALLRESULT(CSteam, OnEnumerateUserSubscribedFiles,
	                 RemoteStorageEnumerateUserSubscribedFilesResult_t,
	                 m_CallbackEnumerateUserSubscribedFiles);
	STEAM_CALLRESULT(CSteam, OnEnumerateUserSharedWorkshopFiles,
	                 RemoteStorageEnumerateUserSharedWorkshopFilesResult_t,
	                 m_CallbackEnumerateUserSharedWorkshopFiles);
	STEAM_CALLRESULT(CSteam, OnEnumeratePublishedFilesByUserAction,
	                 RemoteStorageEnumeratePublishedFilesByUserActionResult_t,
	                 m_CallbackEnumeratePublishedFilesByUserAction);
	STEAM_CALLRESULT(CSteam, OnCommitPublishedFileUpdate,
	                 RemoteStorageUpdatePublishedFileResult_t,
	                 m_CallbackCommitPublishedFileUpdate);
	STEAM_CALLRESULT(CSteam, OnSubscribePublishedFile,
	                 RemoteStorageSubscribePublishedFileResult_t,
	                 m_CallbackSubscribePublishedFile);
	STEAM_CALLRESULT(CSteam, OnUnsubscribePublishedFile,
	                 RemoteStorageUnsubscribePublishedFileResult_t,
	                 m_CallbackUnsubscribePublishedFile);
	STEAM_CALLRESULT(CSteam, OnGetPublishedItemVoteDetails,
	                 RemoteStorageGetPublishedItemVoteDetailsResult_t,
	                 m_CallbackGetPublishedItemVoteDetails);
	STEAM_CALLRESULT(CSteam, OnGetUserPublishedItemVoteDetails,
	                 RemoteStorageUserVoteDetails_t,
	                 m_CallbackGetUserPublishedItemVoteDetails);
	STEAM_CALLRESULT(CSteam, OnUpdateUserPublishedItemVote,
	                 RemoteStorageUpdateUserPublishedItemVoteResult_t,
	                 m_CallbackUpdateUserPublishedItemVote);
	STEAM_CALLRESULT(CSteam, OnSetUserPublishedFileAction,
	                 RemoteStorageSetUserPublishedFileActionResult_t,
	                 m_CallbackSetUserPublishedFileAction);

	// authentication & ownership
	STEAM_CALLBACK(CSteam, OnGetAuthSessionTicketResponse, GetAuthSessionTicketResponse_t,
	               m_CallbackGetAuthSessionTicketResponse);
	STEAM_CALLBACK(CSteam, OnValidateAuthTicketResponse, ValidateAuthTicketResponse_t,
	               m_OnValidateAuthTicketResponse);
	STEAM_CALLRESULT(CSteam, OnEncryptedAppTicketResponse, EncryptedAppTicketResponse_t,
		m_CallbackEncryptedAppTicketResponse);


	// overlay
	STEAM_CALLBACK(CSteam, OnGameOverlayActivated, GameOverlayActivated_t,
	               m_CallbackGameOverlayActivated);

	// DLC / subscription
	STEAM_CALLBACK(CSteam, OnDLCInstalled, DlcInstalled_t,
	               m_CallbackDLCInstalled);

	// Microtransaction
	STEAM_CALLBACK(CSteam, OnMicroTxnAuthorizationResponse, MicroTxnAuthorizationResponse_t,
	               m_CallbackMicroTxnAuthorizationResponse);

#undef STEAM_CALLRESULT

};

// utility functions
void createParamStringArray(std::vector<std::string> tags,
	SteamParamStringArray_t* tagArray);

#endif
