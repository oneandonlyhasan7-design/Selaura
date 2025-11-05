#pragma once
#include <libhat/scanner.hpp>

namespace selaura {
    template <hat::fixed_string str>
    void* find_signature() {
        auto signature = hat::compile_signature<str>();
        return reinterpret_cast<void*>(hat::find_pattern(signature, ".text").get());
    }
    namespace abi {
        template <typename T>
        constexpr void* mpf_to_fn(T member_fn) noexcept {
            static_assert(std::is_member_function_pointer_v<T>,
                          "mpf_to_fn expects a member function pointer");

#if defined(_MSC_VER)
            union {
                T mfptr;
                void* addr;
            } u{};
            u.mfptr = member_fn;
            return u.addr;
#else
            return reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(&member_fn));
#endif
        }

    }
}