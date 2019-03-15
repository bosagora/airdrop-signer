// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "stellar/SecretKey.h"
#include "stellar/StrKey.h"
#include <memory>
#include <mutex>
#include <sodium.h>
#include <type_traits>

namespace stellar
{
SecretKey::~SecretKey()
{
    std::memset(mSecretKey.data(), 0, mSecretKey.size());
}

SecretKey::Seed::~Seed()
{
    std::memset(mSeed.data(), 0, mSeed.size());
}

void SecretKey::clear()
{
    std::memset(mSecretKey.data(), 0, mSecretKey.size());
}

PublicKey const&
SecretKey::getPublicKey() const
{
    return mPublicKey;
}

// Addition to support a simple signing process
int SecretKey::sign (std::string msg, unsigned char* result, unsigned long long& resultLength) const
{
    return crypto_sign_ed25519(result, &resultLength,
                               reinterpret_cast<const unsigned char*>(msg.c_str()), msg.length(),
                               this->mSecretKey.data());
}

SecretKey::Seed
SecretKey::getSeed() const
{
    Seed seed;
    if (crypto_sign_ed25519_sk_to_seed(seed.mSeed.data(), mSecretKey.data()) !=
        0)
    {
        throw std::runtime_error("error extracting seed from secret key");
    }
    return seed;
}


bool
SecretKey::isZero() const
{
    for (auto i : mSecretKey)
    {
        if (i != 0)
        {
            return false;
        }
    }
    return true;
}

SecretKey
SecretKey::fromSeed(ByteSlice const& seed)
{
    SecretKey sk;
    if (seed.size() != crypto_sign_SEEDBYTES)
    {
        throw std::runtime_error("seed does not match byte size");
    }
    if (crypto_sign_seed_keypair(sk.mPublicKey.data(),
                                 sk.mSecretKey.data(), seed.data()) != 0)
    {
        throw std::runtime_error("error generating secret key from seed");
    }
    return sk;
}

SecretKey
SecretKey::fromStrKeySeed(std::string const& strKeySeed)
{
    uint8_t ver;
    std::vector<uint8_t> seed;
    if (!strKey::fromStrKey(strKeySeed, ver, seed) ||
        (ver != strKey::STRKEY_SEED_ED25519) ||
        (seed.size() != crypto_sign_SEEDBYTES) ||
        (strKeySeed.size() != strKey::getStrKeySize(crypto_sign_SEEDBYTES)))
    {
        throw std::runtime_error("invalid seed");
    }

    SecretKey sk;
    if (crypto_sign_seed_keypair(sk.mPublicKey.data(),
                                 sk.mSecretKey.data(), seed.data()) != 0)
    {
        throw std::runtime_error("error generating secret key from seed");
    }
    return sk;
}

std::string
SecretKey::getStrKeyPublic() const
{
    return strKey::toStrKey(strKey::STRKEY_PUBKEY_ED25519, this->getPublicKey());
}
};
