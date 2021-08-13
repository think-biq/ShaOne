/**
* Copyright (c) 2021 blurryroots innovation qanat OÜ
*
* All rights reserved.
*/
/*! \file hash.h
    \brief SHA1 hash and utility functions.
    
    ^^
*/

#ifndef SHAONE_HASH_H_
#define SHAONE_HASH_H_ (1)

#include <stdint.h>
#include "sha.h"

/**
* Creates a hexadecimal version of the given buffer. Should be freed after usage.
* 
* @param Buffer Data buffer.
* @param Count Element size of buffer.
* @returns Newly allocate hex string.
*/
char* Hexify(const uint8_t* Buffer, size_t Count);

/**
* Create SHA1 hash of given data.
* 
* @param Hash Output buffer holding resulting cash.
* @param Data Data to be hashed.
* @returns DataSize Size of the data to be hashed.
*/
void CreateSha1Hash(uint8_t Hash[SHA1_DIGEST_SIZE], const void* Data, size_t DataSize);

#endif