#pragma once

#include <iostream>
#include <SDL2/SDL.h>


/**
 * SDL2 Window.
 */
class SDLApp {
    private:
        //----------------------------------------------------------------------
        // Constants - Attributes
        //----------------------------------------------------------------------
        bool isRunning;
        SDL_Window* window; //SDL main windows
        SDL_Surface* screen; //Surface from the windows

    public:
        //----------------------------------------------------------------------
        // Constructors - Destructor
        //----------------------------------------------------------------------
        SDLApp();
        ~SDLApp();

    public:
        //----------------------------------------------------------------------
        // Init / Stop functions
        //----------------------------------------------------------------------

        /**
         * Run the application if not already running.
         * Continue till SDL is closed.
         * App must be init
         *
         * \return True if start running successfully, otherwise, return false.
         */
        bool runApp();

        /**
         * Initialize SDL components.
         * Do nothing if already running (And return false).
         *
         * \return True if successfully init, otherwise, return false.
         */
        bool initApp();

        /**
         * Close the application.
         * Cleanup all loaded SDL memory and quit SDL.
         *
         * \return True if successfully closed, otherwise, return false.
         */
        bool closeApp();

        //----------------------------------------------------------------------
        // Execution functions
        //----------------------------------------------------------------------
        void doEvent(SDL_Event* sdlevent);
        void doLoop();
        void doRender();
};
