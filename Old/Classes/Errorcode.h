#pragma once

typedef union Errorcode
{
    const static int VALUE_INVALID = 0x000000;
    const static int TYPE_ERROR = 0x000001;
    const static int NULL_EXCEPTION = 0x000002;
    const static int OVERFLOW_EXCEPTION = 0x000003;

}ErrorCode;
