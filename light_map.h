#ifndef LIGHT_MAP_H
#define LIGHT_MAP_H

#include <cstdint>
#include <cstring>

#if UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF
#define PLATFORM_64
#elif UINTPTR_MAX == 0xFFFFFFFF
#define PLATFORM_32
#else
assert(!"unknown platform!");
#endif

namespace lmap
{

    class map
    {
    public:
        template <typename T1, typename T2>
        map(T1 key_, T2 value_)
        {
#ifdef PLATFORM_32
            uint32_t key{}, value{};
            memcpy(&value, &value_, sizeof(T2));
            memcpy(&key, &key_, sizeof(T2));

            _value = (static_cast<uint64_t>(key) << 32) | value;
#elif PLATFORM_64
            uint64_t key{}, value{};
            memcpy(&value, &value_, sizeof(T2));
            memcpy(&key, &key_, sizeof(T2));

            _value = (static_cast<__int128>(key) << 64) | value;
#endif
        }
#ifdef PLATFORM_32
        // raw accessor, for encoded types use upper_as
        __forceinline uint32_t upper() const
        {
            return _value >> 32;
        }

        // raw accessor, for encoded types use lower_as
        __forceinline uint32_t lower() const
        {
            return _value & 0xFFFFFFFF;
        }

#elif PLATFORM_64
        // raw accessor, for encoded types use upper_as
        __forceinline uint64_t upper() const
        {
            return _value >> 64;
        }

        // raw accessor, for encoded types use lower_as
        __forceinline uint64_t lower() const
        {
            return _value & 0xFFFFFFFFFFFFFFFF;
        }
#endif

        template <typename T>
        __forceinline T upper_as() const
        {
            T value{};
            auto bits = upper();
            memcpy(&value, &bits, sizeof(T));
            return value;
        }

        template <typename T>
        __forceinline T lower_as() const
        {
            T value{};
            auto bits = lower();
            memcpy(&value, &bits, sizeof(T));
            return value;
        }

    private:
#ifdef PLATFORM_32
        uint64_t _value{};
#elif PLATFORM_64
        unsigned __int128 _value{};
#endif
    };

} // namespace lmap

#endif