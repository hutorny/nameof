/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * fully_qualified_nameof_test.cpp - Unit test for fully_qualified_nameof
 *
 * Licensed under MIT License, see full text in LICENSE
 * or visit page https://opensource.org/license/mit/
 */

#include <gtest/gtest.h>
#include <meta/nameof.h>
#include "test_inputs.h"

using namespace testing;
using namespace std::literals;
using namespace meta;
using namespace NameSpace;

#define TESTCASE(NAME, INPUT, EXPECTED) TEST(NameOf, NAME) { EXPECT_EQ(fully_qualified_nameof<INPUT>(), EXPECTED) << meta::detail::name<INPUT>(); }

TESTCASE(FullEnum,             test_enum::test_zero, "test_enum::test_zero")
TESTCASE(FullVariable,         &variable, "variable")
TESTCASE(FullConstant,         constant, (AnyOf{"1", "1L", "0x1"}))
TESTCASE(FullConstantPtr,      &constant, "constant")
TESTCASE(FullFunction,         function, "function")
TESTCASE(FullFunctionPtr,      &function, "function")
TESTCASE(FullFuncPtr,          &func, "func")
TESTCASE(FullFuncCall,         func(), "function")
TESTCASE(FullFancy,            &fancy, "fancy")
TESTCASE(FullFunctionCall,     function(), "constant")
TESTCASE(FullResult,           *function(), (AnyOf{"1", "1L", "0x1"}))
TESTCASE(FullStringView,       std::string_view, (AnyOf{"std::basic_string_view<char>", "std::basic_string_view<char,struct std::char_traits<char> >", "std::basic_string_view<char, std::char_traits<char>>", "std::basic_string_view<char, std::char_traits<char> >"}))
TESTCASE(FullClassName,        Class, "NameSpace::Class")
TESTCASE(FullMethod,           &Class::method, "NameSpace::Class::method")
TESTCASE(FullMember,           &Class::member, "NameSpace::Class::member")
TESTCASE(FullInnerClass,       Class::Inner, "NameSpace::Class::Inner")
TESTCASE(FullInnerMember,      &Class::Inner::member, "NameSpace::Class::Inner::member")
TESTCASE(FullInnerMethod,      &Class::Inner::method, "NameSpace::Class::Inner::method")
TESTCASE(FullMethodPtr,        &Class::Inner::methodptr, "NameSpace::Class::Inner::methodptr")
TESTCASE(FullTemplate,         Class::Template<wchar_t>, "NameSpace::Class::Template<wchar_t>")
TESTCASE(FullTemplateMethod,   &Class::Template<wchar_t>::method, "NameSpace::Class::Template<wchar_t>::method")
TESTCASE(FullTemplateFunction, &Class::Template<wchar_t>::function<std::string>, "NameSpace::Class::Template<wchar_t>::function")
TESTCASE(FullMethodPtrMember,  &Class::Template<wchar_t>::methodptr, "NameSpace::Class::Template<wchar_t>::methodptr")

