#pragma once

// TODO : Futher expand this to allow more operations.f

// Tags the package with this type.
typedef enum RequestType {
    REQUEST_AUDIO = 0,
    REQUEST_GRAPHICS = 1,
    REQUEST_INPUT = 2,
    REQUEST_PHYSICS = 3,
    REQUEST_NETWORK = 4,
    REQUEST_MISC = 5,

    PUSH_AUDIO = 6,
    PUSH_GRAPHICS = 7,
    PUSH_INPUT = 8,
    PUSH_PHYSICS = 9,
    PUSH_NETWORK = 10,
    PUSH_MISC = 11
};

