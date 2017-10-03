#pragma once

#include "Uncopyable.h"


/**
 * Any class that inherits from Singleton become itself a singleton.
 *
 * \remark
 * Singleton can't be copied and can't be instanciated (new).
 */
template<class T>
class Singleton : virtual public Uncopyable<Singleton<T>> {
    private:
        static T* instance; // TODO Tmp

    protected:
        Singleton() = default; // Can't be instanciated

    public:

        /**
         * Returns the singleton instance.
         *
         * \return Singleton instance.
         */
        static T& getInstance() {
            static T m;
            return m;
            //return *Singleton<T>::instance;
        }

        /**
         * Returns the pointer to the singleton instance.
         *
         * \return Pointer to the singleton instance.
         */
        static T* getInstancePtr() {
            return &Singleton<T>::getSingleton();
            //return Singleton<T>::instance;
        }
};

template<class T> T* Singleton<T>::instance = nullptr;
