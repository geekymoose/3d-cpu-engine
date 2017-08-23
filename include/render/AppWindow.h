#pragma once

#include <iostream>


/**
 * Define a generic interface of a window.
 * Any engine rendering element is displayed inside a window.
 *
 * \author  Constantin Masson
 * \date    July 2017
 */
class AppWindow {
    public:
        AppWindow();

    public:
        //----------------------------------------------------------------------
        // General functions
        //----------------------------------------------------------------------

        /**
         * Initialize all data for this window.
         * Window is ready to be displayed.
         *
         * \param name  Title of the window.
         * \param w     Window's width.
         * \param h     Window's height.
         */
        virtual void initialize(const char* name, const int w, const int h) = 0;

        /**
         * Initialize all data for this window.
         * Window is ready to be displayed.
         *
         * \param name  Title of the window.
         * \param w     Window's width.
         * \param h     Window's height.
         * \param l     The x position of the window.
         * \param t     The y position of the window.
         */
        virtual void initialize(const char* name, const int w, const int h, const int l, const int t) = 0;

        /** Show this Window. */
        virtual void show() = 0;

        /** Hide this Window */
        virtual void hide() = 0;

        /** Hide and destroy this Window. */
        virtual void destroy() = 0;

        /** Maximize the Window to use the maximum possible size. */
        virtual void maximize() = 0;

        /** Minimize the Window to an iconic representation. */
        virtual void minimize() = 0;

    public:
        //----------------------------------------------------------------------
        // Getter / Setters / Data
        //----------------------------------------------------------------------

        /**
         * Get Window current title.
         *
         * \return The name (Constant pointer).
         */
        virtual const char* getName() const = 0;

        /**
         * Set Window title.
         *
         * \param value New title to place.
         */
        virtual void setName(const char* value) = 0;

        /**
         * Get the window used size.
         * Place width in w and height in h.
         *
         * \param w     Where width value is placed.
         * \param h     Where height value is placed.
         */
        virtual void getSize(int* w, int* h) const = 0;

        /**
         * Get top left corner position of the Window.
         * Place x position in left and y position in top.
         *
         * \param left      X position of the Window.
         * \param top       Y position of the Window.
         */
        virtual void getPosition(int* left, int* top) const = 0;
};

