#include "json_fuzz.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char error[json_error_max];
    json_settings settings = {0};
    
    json_value *value = json_parse_ex(&settings, (const json_char *)data, size, error);
    
    if (value) {
        json_value_free_ex(&settings, value);
    }
    
    return 0;
}
