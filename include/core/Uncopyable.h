#pragma once


/**
 * Any class that inherits from Uncopyable cannot be copied anymore.
 *
 * \remark
 * In order to disable totally object copy,
 * Copy constructor and copy operator are disabled.
 *
 * \author  Constantin Masson
 */
template<class T>
class Uncopyable {
    public:
        Uncopyable() = default;
        virtual ~Uncopyable() = default;

    private:
        Uncopyable(Uncopyable<T> const& other) = delete;
        Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};
