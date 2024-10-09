/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * parse_pretty_test.cpp - Unit test for parse_pretty_function
 *
 * Licensed under MIT License, see full text in LICENSE
 * or visit page https://opensource.org/license/mit/
 */

#include <gtest/gtest.h>
#include <meta/nameof.h>
#include <string_view>
#include <array>

namespace {
using namespace testing;
using namespace meta::detail;
using namespace std::literals;

struct TestItem {
    std::string_view expected;
    std::string_view input;
};

constexpr std::array<TestItem, 12> test_sigs = {
    TestItem{ "test_enum::test_zero"sv,                       "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = test_enum::test_zero]"sv},
    TestItem{ "variable"sv,                                   "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = (& variable)]"sv},
    TestItem{ "1"sv,                                          "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = 1]"sv},
    TestItem{ "function"sv,                                   "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = function]"sv},
    TestItem{ "func"sv,                                       "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = func]"sv},
    TestItem{ "constant"sv,                                   "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = (& constant)]"sv},
    TestItem{ "std::basic_string_view<char>"sv,               "int test(std::initializer_list<std::basic_string_view<char> >) [with T = std::basic_string_view<char>]"sv},
    TestItem{ "TestSpace::Test"sv,                            "int test(std::initializer_list<std::basic_string_view<char> >) [with T = TestSpace::Test]"sv},
    TestItem{ "TestSpace::Test::member"sv,                    "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = &TestSpace::Test::member]"sv},
    TestItem{ "TestSpace::Test::Inner::member"sv,             "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = &TestSpace::Test::Inner::member]"sv},
    TestItem{ "TestSpace::Test::Template<wchar_t>"sv,         "int test(std::initializer_list<std::basic_string_view<char> >) [with T = TestSpace::Test::Template<wchar_t>]"sv},
    TestItem{ "TestSpace::Test::Template<wchar_t>::method"sv, "int test(std::initializer_list<std::basic_string_view<char> >) [with auto V = &TestSpace::Test::Template<wchar_t>::method]"sv},
};
}

TEST(NameOf, PrettyFunction) {
    for(const auto i : test_sigs) {
        const auto actual = parse_pretty_function(i.input);
        RecordProperty("Input"s, std::string{i.input});
        EXPECT_EQ(actual, i.expected);
    }
}

