/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * nameof_slefcheck.h - compile-time self-check for nameof functions
 *
 * Licensed under MIT License, see full text in LICENSE
 * or visit page https://opensource.org/license/mit/
 */

#pragma once
#include <meta/nameof.h>

namespace meta::nameof_selfcheck {
struct Class {
  bool member{};
  int method() { return 0; }
};
inline int function() { return 0; }
inline long variable {};
enum class Enum { value };
decltype(&function) tough(decltype(&Class::method));

static_assert(fully_qualified_nameof<Class>() == "meta::nameof_selfcheck::Class");
static_assert(fully_qualified_nameof<&Class::member>() == "meta::nameof_selfcheck::Class::member");
static_assert(fully_qualified_nameof<&Class::method>() == "meta::nameof_selfcheck::Class::method");
static_assert(fully_qualified_nameof<&variable>() == "meta::nameof_selfcheck::variable");
static_assert(fully_qualified_nameof<&function>() == "meta::nameof_selfcheck::function");
static_assert(fully_qualified_nameof<Enum::value>() == "meta::nameof_selfcheck::Enum::value");
static_assert(fully_qualified_nameof<&tough>() == "meta::nameof_selfcheck::tough");

static_assert(nameof<Class>() == "Class");
static_assert(nameof<&Class::member>() == "member");
static_assert(nameof<&Class::method>() == "method");
static_assert(nameof<&variable>() == "variable");
static_assert(nameof<&function>() == "function");
static_assert(nameof<Enum::value>() == "value");
static_assert(nameof<&tough>() == "tough");

}

 // namespace meta::nameof_selfcheck
