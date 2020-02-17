#pragma once
#include <string>
#include <array>
#include "AllegroPong.h"
#include "AllegroDisplay.h"
#include "AllegroEventQueue.h"
#include "AllegroKeyboard.h"
#include "AllegroKeyboardState.h"
#include "AllegroMouse.h"
#include "AllegroBitmap.h"
#include "AllegroTimer.h"
#include "AlMainModule.h"
#include "KeyPressHandler.h"
#include "AllegroMouseEvent.h"
#include "GameCharacters.h"

namespace Pong {
    ////////////////////////////////////////////////////////////////////////////
    class Game
    {
    public:
        ////////////////////////////////////////////////////////////////////////////
        Game();

        ////////////////////////////////////////////////////////////////////////////
        ~Game() = default;

        ////////////////////////////////////////////////////////////////////////////
        bool Init();

        ////////////////////////////////////////////////////////////////////////////
        bool Run();
    private:
        ////////////////////////////////////////////////////////////////////////////
        bool GameLoop();

        bool mInitialized = false;
        bool mRunning = false;

        AlMainModule mMainModule;

        static const INT32 sDisplayWidth = 640;
        static const INT32 sDisplayHeight = 480;
        AllegroDisplay mDisplay;

        AllegroEventQueue mEventQueue;

        AllegroKeyboard mKeyboard;
        AllegroMouse mMouse;
        KeyPressHandler mKeyPressHandler;

        static const std::string sImagePath;

        static const FLOAT64 sFps;
        AllegroTimer mTimer;

        Player mPlayer;
        Opponent mOpponent;
        Ball mBall;

        UINT16 mPlayerScore = 0;
        UINT16 mOpponentScore = 0;
    };
}



