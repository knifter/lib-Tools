#pragma once

#define DELETE_ASSIGNMENT_OPERATOR(class)   class& operator=(const class&) = delete
#define DELETE_COPY_CONSTRUCTOR(class)      class(const class&) = delete
#define DELETE_MOVE_ASSIGNMENT_OPERATOR(class)  class& operator=(class&&) = delete
#define DELETE_MOVE_CONSTRUCTOR(class)          class(class&&) = delete

class noncopyable
{
    protected:
        noncopyable()   = default;      // need to declare a default as the delete prevents it from being auto-created
        ~noncopyable()  = default;      // prevent deletion via base pointer

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
    public:
        DELETE_ASSIGNMENT_OPERATOR(noncopyable);
        DELETE_COPY_CONSTRUCTOR(noncopyable);

        // These two are implicit anyway(!) but setting them hear for documentation purposes.
        DELETE_MOVE_ASSIGNMENT_OPERATOR(noncopyable);
        DELETE_MOVE_CONSTRUCTOR(noncopyable);
};

template <typename T>
class singleton
{
    public:
        static T& getInstance()
        {
            // Make sure the FIRST getInstance is never run from an ISR
            static T instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        };

        DELETE_ASSIGNMENT_OPERATOR(singleton);
        DELETE_COPY_CONSTRUCTOR(singleton);

        // These two are implicit anyway(!)
        DELETE_MOVE_ASSIGNMENT_OPERATOR(singleton);
        DELETE_MOVE_CONSTRUCTOR(singleton);

    protected:
        singleton() = default;          // hide the default constructor
        ~singleton() = default;         // prevent deletion via base pointer
};

// singleton example:
// class Amp : public singleton<Amp>
// {
//     friend class singleton<Amp>;    // let getInstance() reach the private ctor

//     private:
//         Amp() {};

//     public:
//         void setVolume(uint8_t vol);
// };

// // use:
// Amp::getInstance().setVolume(10);
// It's questionable whether this pattern is actually usefull:
//  Declaring public: Amp() {}; defeats the whole meganism while declaring an extern Amp a; in a .h with 
//  one Amp a; in a .cpp achives the same goal without the caveats.