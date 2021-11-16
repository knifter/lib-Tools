#pragma once

class NonCopyable {
public:
    NonCopyable() {};

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status

    // disable copy constructor
    NonCopyable(NonCopyable const&) = delete;

    // disable assignment operator
    NonCopyable& operator=(NonCopyable const&) = delete;
};

class Singleton
{
    public:
        static Singleton& getInstance()
        {
            static Singleton instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        };

    private:
        Singleton() {};                    // Constructor? (the {} brackets) are needed here.

    public:
        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
        Singleton(Singleton const&)         = delete;
        void operator=(Singleton const&)    = delete;
};
