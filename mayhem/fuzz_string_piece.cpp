#include <stdint.h>
#include <stdio.h>
#include <climits>

#include <fuzzer/FuzzedDataProvider.h>
#include "string_piece.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    
    std::string string = provider.ConsumeRandomLengthString();
    shaderc_util::string_piece sp(string);

    return 0;
}