/**
* Copyright (c) 2021 blurryroots innovation qanat OÜ
*
* All rights reserved.
*/

#undef TESTLY_ASSERT_DISABLED
#include <testly/assert.h>
#include <testly/run.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <ShaOne/sha.h>
#include <ShaOne/hash.h>

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

	int Passed = Check("SecretToSha1", SHA_DIGEST_LENGTH, Expected, KeyBuffer, 
		"Expected %s, got %s.", Expected, KeyBuffer
	);

	return Passed;
}

int TestHash()
{
	const char* Secret = "CAFEBABECAFEBABFECAFEBABE";
	const size_t SecretLength = strlen(Secret);

	uint8_t Expected[SHA_DIGEST_LENGTH] = {
		208, 8, 154, 24, 43, 91, 35, 233, 25, 105,
		250, 23, 20, 76, 154, 131, 124, 59, 146, 140
	};

	int Passed;
	uint8_t Hash[SHA_DIGEST_LENGTH];

	{
		CreateSha1Hash(Hash, Secret, SecretLength);
		Passed = Check("CreateSha1Hash", SHA_DIGEST_LENGTH, Expected, Hash, 
			"Expected %s, got %s.", Expected, Hash
		);
	}

	{
		char* HashHex = Hexify(Hash, SHA_DIGEST_LENGTH);
		char* HashExpected = Hexify(Expected, SHA_DIGEST_LENGTH);
		
		Passed = Check("Hexify", 0, HashExpected, HashHex, 
			"Expected %s, got %s.", HashExpected, HashHex
		);

		free(HashExpected);
		free(HashHex);
	}

	return Passed;
}

int TestHexify()
{
	int Passed = 1;

	{
		const char* Expected = "0810";
		const uint8_t Buffer[2] = { 8, 16 };

		char* Hex = Hexify(Buffer, 2);

		Passed &= Check("Hexify", 0, Expected, Hex, 
			"Expected %s, got %s.", Expected, Hex
		);

		free(Hex);
	}

	{
		const char* Expected = "48616e73";
		const uint8_t* Buffer = "Hans";

		char* Hex = Hexify(Buffer, 4);

		Passed &= Check("Hexify", 0, Expected, Hex, 
			"Expected %s, got %s.", Expected, Hex
		);

		free(Hex);
	}

	return Passed;
}

int main(void)
{
	RUN_TEST(TestSha);
	RUN_TEST(TestHash);
	RUN_TEST(TestHexify);
}