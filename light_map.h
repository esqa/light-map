#ifndef LIGHT_MAP_H
#define LIGHT_MAP_H

#include <cassert>
#include <cstdint>

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
    map(T1 key, T2 value)
    {
#ifdef PLATFORM_32
        _value = (static_cast<uint64_t>(key) << 32) | static_cast<uint32_t>(value);
#elif PLATFORM_64
        _value = (static_cast<unsigned __int128>(key) << 64) | static_cast<uint64_t>(value);
#endif
    }
#ifdef PLATFORM_32
    __forceinline uint32_t upper() const { return _value >> 32; }
    __forceinline uint32_t lower() const { return _value & 0xFFFFFFFF; }
#elif PLATFORM_64
    __forceinline  uint64_t upper() const { return _value >> 64; }
    __forceinline  uint64_t lower() const { return _value & 0xFFFFFFFFFFFFFFFF; }
#endif

private:
#ifdef PLATFORM_32
    uint64_t _value{};
#elif PLATFORM_64
    unsigned __int128 _value{};
#endif
};

} // namespace lmap

#endif
