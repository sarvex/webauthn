#include "WebAuthnDef.h"

#include <Random.h>

std::optional<std::vector<std::byte>> webauthn::UserData::generateRandomID(std::size_t size)
{
	return crypto::random::genRandom(size);
}
