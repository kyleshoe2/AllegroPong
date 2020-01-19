#include <allegro5/allegro.h>
#include "AlMainModule.h"

////////////////////////////////////////////////////////////////////////////////
Pong::AlMainModule::~AlMainModule()
{
    Destroy();
}

////////////////////////////////////////////////////////////////////////////////
bool Pong::AlMainModule::Create()
{
    return al_init();
}

////////////////////////////////////////////////////////////////////////////////
bool Pong::AlMainModule::IsInitialized() const
{
    return al_is_system_installed();
}

////////////////////////////////////////////////////////////////////////////////
bool Pong::AlMainModule::Destroy()
{
    if (IsInitialized())
    {
        al_uninstall_system();
        return true;
    }
    return false;
}
