#pragma once
#include "UIElement.h"
#include "UIButton.h"
#include "LawnApp.h"
#include "Lawn.h"
class ChosenSeed {
    int mX;
    int mY;
    int mTimeStartMotion;
    int mTimeEndMotion;
    int mStartX;
    int mStartY;
    int mEndX;
    int mEndY;
    SeedType msSeedType;
    int ChosenSeedState;
    int SeedIndexInBank;
    bool mRefreshing;
    int mRefreshCounter;
    SeedType mImitaterType;
    bool mCrazyDavePicked;
};

class SeedChooserScreen : public Sexy::UIElement {
public:
     Sexy::UIButton* mStartButton;
     Sexy::UIButton* mRandomButton;
     Sexy::UIButton* mViewLawnButton;
     Sexy::UIButton* mStoreButton;
     Sexy::UIButton* mAlmanacButton;
     Sexy::UIButton * mMenuButton;
     Sexy::UIButton* mImitaterButton;
     ChosenSeed mChosenSeeds[53];
    LawnApp* mApp;
    Lawn* mBoard;
    int mNumSeedsToChoose;
    int mSeedChooserAge;
    int mSeedsInFlight;
    int mSeedsInBank;   
    int* mToolTip;
    int mToolTipSeed;
    int mLastMouseX;
    int mLastMouseY;
    int mChooseState;
    int mViewLawnTime;
};

class SeedPacket : public GameObject {
public:
    int mRefreshCounter;
    int mRefreshTime;
    int mIndex;
    int mOffsetX;
    SeedType mPacketType;
    SeedType mImitaterType;
    int mSlotMachineCountDown;
    SeedType mSlotMachiningNextSeed;
    float mSlotMachiningPosition;
    bool Active;
    bool Refreshing;
    int mTimesUsed;
};

class SeedBank : public GameObject {
public:
    int mNumPackets;
    SeedPacket mPackets[10];
    int mCutsceneDarken;
    int mConveyorBeltCounter;
};