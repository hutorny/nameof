/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * nameof.h - nameof function returning names of types, members, methods, variables
 *
 * Licensed under MIT License, see full text in LICENSE
 * or visit page https://opensource.org/license/mit/
 */

#pragma once
#include <string_view>
#include <algorithm> //std::min

/*
 * nameof<> templates using __PRETTY_FUNCTION__/__FUNCSIG__ to infer the template parameter name
 * Compiler support:
 *   GCC 8.1 - 14.2 (enum names since 9.1)
 *   CLANG 9.0 - 19.1
 *   ICX 2021.1 - 2024.2
 *   NVC 22.7 - 24.7
 *   MSVC 19.4
 */

namespace meta {
using name_type = std::string_view;

//----------------------------------------------------------------------------------------------------------------------
namespace detail {
inline constexpr auto npos = name_type::npos;

struct view_range { // std::pair is not yet constexpr in msvc
    std::size_t start;
    std::size_t finish;
};

constexpr view_range find_group(name_type name, std::size_t start = 0) {
    unsigned depth = 0;
    for(auto n = name.find('<', start), i = n; i < name.size(); ++i) {
        if( name[i] == '<' ) ++depth;
        else if( name[i] == '>' ) --depth;
        if (depth == 0)
            return { n, i };
    }
    return { npos, npos };
}

constexpr auto parse_funcsig(name_type name) {
    auto group_pos = find_group(name);
    if (group_pos.start == npos)
        return name;
    name = name.substr(group_pos.start + 1, group_pos.finish - group_pos.start - 1);
    if (name.find("struct ") == 0) {
       name = name.substr(sizeof("struct"));
    } else if (name.find("class ") == 0) {
       name = name.substr(sizeof("class"));
    } else {
      if (name[0] == '&') name.remove_prefix(1);
      if (name[0] == ' ') name.remove_prefix(1);
    }
    const auto thiscall_pos = name.rfind("__thiscall ");
    if (thiscall_pos != npos) {
        name = name.substr(thiscall_pos + sizeof("__thiscall"));
        auto pos = find_group(name);
        while(pos.start != npos && name[pos.finish + 1] != '(') {
            pos = find_group(name, pos.start + 1);
        }
        if (pos.start != npos)
            return name.substr(0, pos.start);
    }
    auto cdecl_pos = name.rfind("*__cdecl ");
    if (cdecl_pos != npos) {
        name = name.substr(cdecl_pos + sizeof("*__cdecl"));
        auto pos = find_group(name);
        while(pos.start != npos && name[pos.finish + 1] != '(') {
            pos = find_group(name, pos.start + 1);
        }
        if (pos.start != npos)
            return name.substr(0, pos.start);
    }
    cdecl_pos = name.rfind(" __cdecl ");
    if (cdecl_pos != npos) {
        name = name.substr(cdecl_pos + sizeof(" __cdecl"));
        auto pos = find_group(name);
        while(pos.start != npos && name[pos.finish + 1] != '(') {
            pos = find_group(name, pos.start + 1);
        }
        if (pos.start != npos)
            return name.substr(0, pos.start);
    }
    auto end_pos = name.find('(');
    if(end_pos == npos)
        return name;
    return name.substr(0, end_pos);
}

constexpr auto parse_pretty_function(name_type name) {
    const auto eq_pos = name.find('=');
    if (eq_pos == npos)
        return name;
    name.remove_prefix(eq_pos + 2);
    if (name[0] == '(') name.remove_prefix(1);
    if (name[0] == '&') name.remove_prefix(1);
    if (name[0] == ' ') name.remove_prefix(1);
    auto semi_pos = name.find(';');
    auto rbra_pos = name.find(']');
    auto rcur_pos = name.find(')');
    auto end_pos = std::min(semi_pos, std::min(rbra_pos, rcur_pos));
    if(end_pos == npos)
        return name;
    return name.substr(0, end_pos);
}

constexpr auto parse_fully_qualified_name(name_type name) {
  const auto col_pos = name.rfind(':');
  if (col_pos != npos)
    name.remove_prefix(col_pos + 1);
  const auto less_pos = name.find('<');
  if (less_pos != npos)
      return name.substr(0, less_pos);
  return name;
}

#ifdef _MSC_VER
template <typename T>
constexpr auto name() {
    return name_type{__FUNCSIG__};
}
template <auto V>
constexpr auto name() {
    return name_type{__FUNCSIG__};
}
constexpr auto parse_name(std::string_view name) {
    return parse_funcsig(name);
}

#else
template <typename T>
constexpr auto name() {
    return name_type{__PRETTY_FUNCTION__};
}
template <auto V>
constexpr auto name() {
    return name_type{__PRETTY_FUNCTION__};
}
constexpr auto parse_name(std::string_view name) {
    return parse_pretty_function(name);
}
#endif
} // namespace detail
//----------------------------------------------------------------------------------------------------------------------

/// Returns fully qualified name of type T
template <typename T>
constexpr auto fully_qualified_nameof() {
    return detail::parse_name(detail::name<T>());
}

/// Returns fully qualified name of parameter V (if available)
template <auto V>
constexpr auto fully_qualified_nameof() {
    return detail::parse_name(detail::name<V>());
}

/// Returns last stem of the fully qualified name of V
template <auto V>
constexpr auto nameof() {
  return detail::parse_fully_qualified_name(fully_qualified_nameof<V>());
}

/// Returns last stem of the fully qualified name of T
template <typename T>
constexpr auto nameof() {
    return detail::parse_fully_qualified_name(fully_qualified_nameof<T>());
}
} // namespace meta
