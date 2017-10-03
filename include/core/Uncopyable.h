#pragma once


/**
 * Any class that inherits from Uncopyable cannot be copied anymore.
 *
 * \remark
 * In order to disable totally object copy,
 * Copy constructor and copy operator are disabled.
 */
template<class T>
class Uncopyable {
    public:
        Uncopyable() = default;
        Uncopyable(Uncopyable<T> const& other) = delete;
        Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};
