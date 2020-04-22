#pragma once

class NonCopyable {
public:
    // disable copy constructor
    NonCopyable(NonCopyable const&) = delete;

    // disable assignment operator
    NonCopyable& operator=(NonCopyable const&) = delete;

    NonCopyable() {}
};
