/**
* Copyright (c) 2021 blurryroots innovation qanat OÜ
*
* All rights reserved.
*/

#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

char* Hexify(const uint8_t* Buffer, size_t Count)
{
    if (NULL == Buffer)
    {
        return NULL;
    }

    char* Hash = calloc(1, Count*2+1);
    for (size_t Index = 0; Index < Count; ++Index)
    {
        char Hex[3];
        snprintf(Hex, 3, "%02x", Buffer[Index]);
        strcat(Hash, Hex);
    }

    Hash[Count*2] = '\0';
    return Hash;
}

void CreateSha1Hash(uint8_t Hash[SHA1_DIGEST_SIZE], const void* Data, size_t DataSize)
{
    SHA_CTX KeyContext;
    uint8_t KeyBuffer[SHA_DIGEST_LENGTH];

    SHA1_Init(&KeyContext);
    SHA1_Update(&KeyContext, Data, DataSize);
    SHA1_Final(Hash, &KeyContext);
}