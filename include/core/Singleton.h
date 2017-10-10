#pragma once

#include "Uncopyable.h"


/**
 * Any class that inherits from Singleton become itself a singleton.
 *
 * \remark
 * Singleton can't be copied and can't be instanciated (new).
 *
 * \author  Constantin Masson
 */
template<class T>
class Singleton : virtual private Uncopyable<Singleton<T>> {
    private:
        friend T;

    private:
        Singleton() = default; // Can't be instanciated
        virtual ~Singleton() = default;

    public:

        /**
         * Returns the singleton instance.
         *
         * \return Singleton instance.
         */
        static T& getInstance() {
            static T m;
            return m;
        }

        /**
         * Returns the pointer to the singleton instance.
         *
         * \return Pointer to the singleton instance.
         */
        static T* getInstancePtr() {
            return &Singleton<T>::getSingleton();
        }
};
