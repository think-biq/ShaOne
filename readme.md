# ShaOne

Minimalistic sha1 implementation. Public interface based on work by Bob Liu
(MIT license), and public domain implementation by Steve Reid.

## Setup

Clone the repository recursively:

```bash
git clone --recursive https://github.com/think-biq/ShaOne .
```

To build the library:

```bash
make
```

Will generate the build environment to ./staging through cmake, and builds the
library.

To run the tests:

```bash
make run-test
```

Will build a test executable using the [testly](https://github.com/think-biq/testly) test library.

## Modules

### Hash

Features a wrapper function *CreateSha1Hash* and helper function to create a
hex string from a data array called *Hexify*.

```c
/**
* Create SHA1 hash of given data.
* 
* @param Hash Output buffer holding resulting cash.
* @param Data Data to be hashed.
* @returns DataSize Size of the data to be hashed.
*/
void CreateSha1Hash(uint8_t Hash[SHA1_DIGEST_SIZE], const void* Data, size_t DataSize);

```

```c
/**
* Creates a hexadecimal version of the given buffer. Should be freed after usage.
* 
* @param Buffer Data buffer.
* @param Count Element size of buffer.
* @returns Newly allocate hex string.
*/
char* Hexify(const uint8_t* Buffer, size_t Count);
```

### Sha1

Features a three step sha1 creation api. *SHA1_Init* lets you create a new sha1
hash context. *SHA1_Update* lets you add data to the context and *SHA1_Final* 
processes the staged data.

```c
/**
* Initialize new context
*
* @param context SHA1-Context
*/
void SHA1_Init(SHA1_CTX *context);
```

```c
/**
* Run your data through this
*
* @param context SHA1-Context
* @param p       Buffer to run SHA1 on
* @param len     Number of bytes
*/
void SHA1_Update(SHA1_CTX *context, const void *p, size_t len);
```

```c
/**
* Add padding and return the message digest
*
* @param digest  Generated message digest
* @param context SHA1-Context
*/
void SHA1_Final(uint8_t digest[SHA1_DIGEST_SIZE], SHA1_CTX *context);
```