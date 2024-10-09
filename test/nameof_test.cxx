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

#define TESTCASE(NAME, INPUT, EXPECTED) TEST(NameOf, NAME) { EXPECT_EQ(nameof<INPUT>(), EXPECTED) << meta::detail::name<INPUT>(); }

TESTCASE(Enum,             test_enum::test_zero, "test_zero")
TESTCASE(Variable,         &variable, "variable")
TESTCASE(Constant,         constant, (AnyOf{"1", "1L", "0x1"}))
TESTCASE(ConstantPtr,      &constant, "constant")
TESTCASE(Function,         function, "function")
TESTCASE(FunctionPtr,      &function, "function")
TESTCASE(FuncPtr,          &func, "func")
TESTCASE(FuncCall,         func(), "function")
TESTCASE(Fancy,            &fancy, "fancy")
TESTCASE(FunctionCall,     function(), "constant")
TESTCASE(Result,           *function(), (AnyOf{"1", "1L", "0x1"}))
TESTCASE(StringView,       std::string_view, "basic_string_view"sv)
TESTCASE(ClassName,        Class, "Class")
TESTCASE(Method,           &Class::method, "method")
TESTCASE(Member,           &Class::member, "member")
TESTCASE(InnerClass,       Class::Inner, "Inner")
TESTCASE(InnerMember,      &Class::Inner::member, "member")
TESTCASE(InnerMethod,      &Class::Inner::method, "method")
TESTCASE(MethodPtr,        &Class::Inner::methodptr, "methodptr")
TESTCASE(Template,         Class::Template<wchar_t>, "Template")
TESTCASE(TemplateMethod,   &Class::Template<wchar_t>::method, "method");
TESTCASE(TemplateFunction, &Class::Template<wchar_t>::function<std::string>, "function")
TESTCASE(MethodPtrMember,  &Class::Template<wchar_t>::methodptr, "methodptr")
