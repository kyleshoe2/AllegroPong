#include <iostream>
#include "Game.h"

const std::string Pong::Game::sImagePath = "image.png";
const FLOAT64 Pong::Game::sFps = 60.0;

////////////////////////////////////////////////////////////////////////////////
Pong::Game::Game()
    :mBall(sDisplayWidth, sDisplayHeight),
     mPlayer(mKeyPressHandler),
     mOpponent(mBall),
     mPlayerScoreboard(mAllegroFont, sDisplayWidth / 2.0F, sDisplayHeight / 2.0F)
{
}

////////////////////////////////////////////////////////////////////////////////
bool Pong::Game::Init()
{
    if (!mInitialized && !mRunning)
    {
        const bool mainModuleInit = mMainModule.Create();
        if (mainModuleInit == false)
        {
            std::cerr << "Could not initialize main module" << std::endl;
            return false;
        }

        const bool fontModuleInit = mFontModule.Init();
        if (!fontModuleInit)
        {
            std::cerr << "Could not initialize font module" << std::endl;
            return false;
        }

        const bool ttfModuleInit = mTtfModule.Init();
        if (!ttfModuleInit)
        {
            std::cerr << "Could not initialize ttf module" << std::endl;
            return false;
        }

        const bool imageAddonInit = al_init_image_addon();
        if (imageAddonInit == false)
        {
            std::cerr << "Could not intialize image addon" << std::endl;
            return false;
        }

        const bool displayCreated = mDisplay.Create(sDisplayWidth, sDisplayHeight);
        if(displayCreated == false)
        {
            std::cerr << "Could not create display" << std::endl;
        }

        mKeyboard.Create();
        mTimer.Create(1.0 / sFps);
        mMouse.Create();

        mEventQueue.Create();
        mEventQueue.RegisterEventSource(mKeyboard);
        mEventQueue.RegisterEventSource(mDisplay);
        mEventQueue.RegisterEventSource(mMouse);
        mEventQueue.RegisterEventSource(mTimer);

        mPlayer.Init();
        mOpponent.Init();
        mBall.Init();

        mAllegroFont.Create();

        mInitialized = true;
    }

    return mInitialized;
}

////////////////////////////////////////////////////////////////////////////////
bool Pong::Game::Run()
{
    bool success = false;
    if (mInitialized)
    {
        success = GameLoop();
    }
    return success;
}

////////////////////////////////////////////////////////////////////////////////
bool Pong::Game::GameLoop()
{
    mRunning = true;

    mTimer.Start();

    bool redraw = false;

    while (mRunning)
    {
        ALLEGRO_EVENT event;

        mEventQueue.Wait(&event);
        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
            {
                mPlayer.Move();
                mOpponent.Move();
                mBall.Move();

                mPlayer.HandleCollisionWithDisplay(mDisplay);
                mOpponent.HandleCollisionWithDisplay(mDisplay);

                mBall.HandleCollisionWithDisplay(mDisplay);
                mBall.HandleCollisionWithCharacter(mPlayer);
                mBall.HandleCollisionWithCharacter(mOpponent);

                if (mBall.HandleCharacterMiss(mPlayer))
                {
                    mOpponentScore++;
                }
                else if (mBall.HandleCharacterMiss(mOpponent))
                {
                    mPlayerScore++;
                    mPlayerScoreboard.Update(mPlayerScore);
                }

                mKeyPressHandler.ClearPresses();
                redraw = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN:
            {
                mKeyPressHandler.KeyDown(event.keyboard.keycode);
                break;
            }
            case ALLEGRO_EVENT_KEY_UP:
            {
                mKeyPressHandler.KeyUp(event.keyboard.keycode);
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
            {
                mRunning = false;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES:
            {
                AllegroMouseEvent mouseEvent(event);
                mPlayer.DoMouseEvent(mouseEvent);
                break;
            }
            default:
            {
                break;
            }
        }

        if (redraw && mEventQueue.IsEmpty())
        {
            mDisplay.SetColor(0, 0, 0);
            mPlayer.Draw();
            mOpponent.Draw();
            mBall.Draw();

            mPlayerScoreboard.Draw();

            mDisplay.Update();
            redraw = false;
        }
    }

    return true;
}
