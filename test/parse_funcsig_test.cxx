/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * parse_funcsig_test.cpp - Unit test for parse_funcsig
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

constexpr std::array<TestItem, 19> test_sigs = {
    TestItem{ "test_enum::test_zero"sv,                                        "int __cdecl test<test_enum::test_zero>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >"sv},
    TestItem{ "variable"sv,                                                    "int __cdecl test<&variable>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "0x1"sv,                                                         "int __cdecl test<0x1>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "constant"sv,                                                    "int __cdecl test<& constant>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "function"sv,                                                    "int __cdecl test<const long *__cdecl function(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "func"sv,                                                        "int __cdecl test<&const long *(__cdecl *__cdecl func(void))(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "fancy"sv,                                                       "int __cdecl test<&const long *(__cdecl *(__cdecl *__cdecl fancy(const long *(__cdecl *)(void),class std::basic_string_view<char,struct std::char_traits<char> > (__cdecl *TestSpace::Test::Template<char>::* )(char)))(void))(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "std::basic_string_view<char,struct std::char_traits<char> >"sv, "int __cdecl test<class std::basic_string_view<char,struct std::char_traits<char> >>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test"sv,                                             "int __cdecl test<struct TestSpace::Test>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::method"sv,                                     "int __cdecl test<class std::basic_string_view<char,struct std::char_traits<char> > __cdecl TestSpace::Test::method(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::member"sv,                                     "int __cdecl test<&TestSpace::Test::member>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Inner"sv,                                      "int __cdecl test<struct TestSpace::Test::Inner>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Inner::member"sv,                              "int __cdecl test<&TestSpace::Test::Inner::member>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Inner::method"sv,                              "int __cdecl test<class std::basic_string_view<char,struct std::char_traits<char> > __cdecl TestSpace::Test::Inner::method(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Inner::methodptr"sv,                           "int __cdecl test<&TestSpace::Test::Inner::methodptr>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Template<wchar_t>"sv,                          "int __cdecl test<struct TestSpace::Test::Template<wchar_t>>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Template<wchar_t>::method"sv,                  "int __cdecl test<class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> > __cdecl TestSpace::Test::Template<wchar_t>::method(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Template<wchar_t>::function"sv,                "int __cdecl test<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl TestSpace::Test::Template<wchar_t>::function<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >>(void)>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv},
    TestItem{ "TestSpace::Test::Template<wchar_t>::methodptr"sv,               "int __cdecl test<&TestSpace::Test::Template<wchar_t>::methodptr>(class std::initializer_list<class std::basic_string_view<char,struct std::char_traits<char> > >)"sv}
};

TEST(NameOf, Funsig) {
    for(const auto i : test_sigs) {
        const auto actual = parse_funcsig(i.input);
        RecordProperty("Input"s, std::string{i.input});
        EXPECT_EQ(actual, i.expected);
    }
}
}

