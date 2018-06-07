/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/hal/OSWrappers.hpp>
#include <SDL2/SDL.h>

namespace touchgfx
{

static SDL_mutex* s_FrameBufferLock;

void OSWrappers::initialize()
{
    // Setup framebuffer lock
    s_FrameBufferLock = SDL_CreateMutex();
}

void OSWrappers::takeFrameBufferSemaphore()
{
    SDL_LockMutex(s_FrameBufferLock);
}

void OSWrappers::giveFrameBufferSemaphore()
{
    SDL_UnlockMutex(s_FrameBufferLock);
}

void OSWrappers::waitForVSync()
{}

void OSWrappers::tryTakeFrameBufferSemaphore()
{}

void OSWrappers::giveFrameBufferSemaphoreFromISR()
{}

} // namespace touchgfx
