#undef TESTLY_ASSERT_DISABLED
#include "testly/assert.h"
#include "testly/run.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <ShaOne/sha.h>

int TestSha()
{
	const char* Secret = "CAFEBABECAFEBABFECAFEBABE";
	const size_t SecretLength = strlen(Secret);

	uint8_t Expected[SHA_DIGEST_LENGTH] = {
		208, 8, 154, 24, 43, 91, 35, 233, 25, 105,
		250, 23, 20, 76, 154, 131, 124, 59, 146, 140
	};

    uint8_t KeyBuffer[SHA_DIGEST_LENGTH];
    {
	    SHA_CTX KeyContext;
	    SHA1_Init(&KeyContext);
	    SHA1_Update(&KeyContext, Secret, SecretLength);
	    SHA1_Final(KeyBuffer, &KeyContext);
	}

	int Passed = Assert(SHA_DIGEST_LENGTH, "SecretToSha1", TESTLY_EXIT_ON_FAIL,
		Expected, KeyBuffer, 
		"Expected %s, got %s.", Expected, KeyBuffer
	);

	return Passed;
}

int main(void)
{
	RUN_TEST(TestSha);
}