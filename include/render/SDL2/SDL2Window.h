#ifndef ENGINE_RENDER_SDL_WINDOW_H_
#define ENGINE_RENDER_SDL_WINDOW_H_

#include <iostream>
#include <SDL2/SDL.h>


/**
 * Render a Window using SDL2.
 */
class SDL2Window {
    private:
        //----------------------------------------------------------------------
        // Constants - Attributes
        //----------------------------------------------------------------------
        SDL_Window*     window; // The famous SDL windows
        SDL_Surface*    screen; // The window surface where to draw
        char*           title;
        int             width;
        int             height;
        int             left;
        int             top;

    public:
        //----------------------------------------------------------------------
        // Constructors - Destructor
        //----------------------------------------------------------------------
        SDL2Window();

    public:
        //----------------------------------------------------------------------
        // Init / Stop functions
        //----------------------------------------------------------------------

        /**
         * Initialize and display the window.
         *
         * \param title Title of the window.
         * \param w Window's width.
         * \param h Window's height.
         * \return True if successfully init, otherwise, return false.
         */
        bool showWindow(const char* title, const int w, const int h);

        /**
         * Initialize and display the window.
         * Window is placed in specific place.
         *
         * \param title Title of the window.
         * \param w Window's width.
         * \param h Window's height.
         * \param l The x position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED (SDL doc)
         * \param t The y position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED (SDL doc)
         * \return True if success, otherwise, return false.
         */
        bool showWindow(const char* title, const int w, const int h, const int l, const int t);

        /**
         * Close this window.
         *
         * \return True if successfully closed, otherwise, return false.
         */
        bool closeWindow();
};


#endif // End header guard



