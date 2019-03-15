#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "stellar/ByteSlice.h"

#include <array>
#include <functional>
#include <ostream>

namespace stellar
{
    using uint256 = std::array<unsigned char, 32>;
    using uint512 = std::array<unsigned char, 64>;
    using PublicKey = uint256;
    using SecretValue = std::string;

    class ByteSlice;
    struct SignerKey;

    class SecretKey
    {
        uint512 mSecretKey;
        PublicKey mPublicKey;

        struct Seed
        {
            uint256 mSeed;
            Seed() = default;
            Seed(const Seed&) = default;
            ~Seed();
        };

        // Get the seed portion of this secret key.
        Seed getSeed() const;

    public:
        SecretKey() = default;
        SecretKey(const SecretKey&) = default;
        ~SecretKey();
        void clear();

        // Simple signature interface, not originally in stellar
        // We assume the `result` already has the right size
        int sign (std::string msg, unsigned char* result, unsigned long long& resultLength) const;

        // Get the public key portion of this secret key.
        PublicKey const& getPublicKey() const;

        // Get the seed portion of this secret key as a StrKey string.
        SecretValue getStrKeySeed() const;

        // Get the public key portion of this secret key as a StrKey string.
        std::string getStrKeyPublic() const;

        // Return true iff this key is all-zero.
        bool isZero() const;

        // Create a new, random secret key.
        static SecretKey random();

        // Decode a secret key from a provided StrKey seed value.
        static SecretKey fromStrKeySeed(std::string const& strKeySeed);
        static SecretKey
        fromStrKeySeed(std::string&& strKeySeed)
        {
            SecretKey ret = fromStrKeySeed(strKeySeed);
            for (std::size_t i = 0; i < strKeySeed.size(); ++i)
                strKeySeed[i] = 0;
            return ret;
        }

        // Decode a secret key from a binary seed value.
        static SecretKey fromSeed(ByteSlice const& seed);

        bool
        operator==(SecretKey const& rh) const
        {
            return (mSecretKey == rh.mSecretKey);
        }
    };
}

namespace std
{
    template <> struct hash<stellar::PublicKey>
    {
        size_t operator()(stellar::PublicKey const& x) const noexcept;
    };
}
