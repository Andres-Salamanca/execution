// src/beman/execution26/tests/meta-transform.pass.cpp                -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/execution26/detail/meta_transform.hpp>
#include <beman/execution26/detail/type_list.hpp>
#include <test/execution.hpp>
#include <concepts>
#include <type_traits>

// ----------------------------------------------------------------------------

namespace
{
    template <typename>
    struct foo {};
    template <typename T>
    using bar = foo<T>;

    template <typename T>
    struct baz { using type = foo<T>; };
    template <typename T>
    using baz_t = typename baz<T>::type;;
}

auto main() -> int
{
    static_assert(std::same_as<
        test_detail::type_list<>,
        test_detail::meta::transform<foo, test_detail::type_list<>>
    >);
    static_assert(std::same_as<
        test_detail::type_list<foo<bool>, foo<char>>,
        test_detail::meta::transform<foo, test_detail::type_list<bool, char>>
    >);
    static_assert(std::same_as<
        test_detail::type_list<foo<bool>, foo<char>>,
        test_detail::meta::transform<bar, test_detail::type_list<bool, char>>
    >);
    static_assert(std::same_as<
        test_detail::type_list<foo<bool>, foo<char>>,
        test_detail::meta::transform<baz_t, test_detail::type_list<bool, char>>
    >);
    static_assert(std::same_as<
        test_detail::type_list<bool, char>,
        test_detail::meta::transform<std::type_identity_t, test_detail::type_list<bool, char>>
    >);
}