/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * test_inputs.h - Unit test inputs and definitions
 *
 * Licensed under MIT License, see full text in LICENSE
 * or visit page https://opensource.org/license/mit/
 */

#pragma once
#include <string>
#include <string_view>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

inline int variable {};
constexpr long constant = 1L;
constexpr static auto function() { return &constant; }

namespace NameSpace {
struct Class {
  bool member{};
  std::string_view method() { return {}; }
  struct Inner {
      std::string member;
      std::string_view method() { return {}; }
      std::string_view (*methodptr)();
  };
  template<typename T>
  struct Template {
      std::string member;
      std::basic_string<T> method() { return {}; }
      std::string_view (*methodptr)(T);
      template<typename R>
      R function() { return R{}; }
  };
};
}

enum class test_enum {
  test_zero,
};

static constexpr const long*(*func())() { return function; }
decltype(&func) fancy(decltype(&function), decltype(&NameSpace::Class::Template<char>::methodptr));

using AnyOf = std::vector<std::string_view>;
namespace testing::internal {
template <>
inline AssertionResult CmpHelperEQ<std::string_view, AnyOf>(const char* lhs_expression,
                            const char* rhs_expression, const std::string_view& lhs,
                            const AnyOf& rhs) {
    for(const auto item : rhs) {
        if (lhs == item)
            return AssertionSuccess();
    }
    return CmpHelperEQFailure(lhs_expression, rhs_expression, lhs, rhs);
}

template<class Stream>
inline auto& operator<<(Stream& stream, const AnyOf& list) {
    std::string_view dlm {""};
    for(const auto item : list) {
        stream << dlm << item;
        dlm = "\n\t";
    }
    return stream;
}
}
