#pragma once
#include "ConfigRegistry.h"
#include <stdlib.h>

class ConfigTypeConverter {
    public:

        static int CharToInt(const char *value) {
            return TextToInteger(value);
        }

        
        // converts string into C readable const char *, then passes it to a function.
        static int StrToInt(std::string *value) {

            if (value->c_str() == "true") {
                return 1;
            }else if (value->c_str() == "false") {
                return 0;
            } else {
                const char *charconversion = value->c_str();

                return TextToInteger(charconversion);
            }

        }

        static int Int64ToInt(int64_t *value) {
            return *value;
        }
        
    private:


};