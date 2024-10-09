## nameof
Functions, returing name of its parameter - a type, a function, a member, a method or an enum value

### Introduction
`nameof<>` template functions using `__PRETTY_FUNCTION__`/`__FUNCSIG__` to infer the template parameter name

### Examples

```C++
#include <iostream>
#include <meta/nameof.h>

struct Class {
  bool member{};
  int method() { return 0; }
};
inline int function() { return 0; }
inline long variable {};
enum class Enum { value };

int main() {
  using namespace meta;
  std::cout << fully_qualified_nameof<Class>() << '\n'
            << fully_qualified_nameof<&Class::member>() << '\n'
            << fully_qualified_nameof<&Class::method>() << '\n'
            << fully_qualified_nameof<&variable>() << '\n'
            << fully_qualified_nameof<&function>() << '\n'
            << fully_qualified_nameof<Enum::value>() << '\n'
            << nameof<Class>() << '\n'
            << nameof<&Class::member>() << '\n'
            << nameof<&Class::method>() << '\n'
            << nameof<&variable>() << '\n'
            << nameof<&function>() << '\n'
            << nameof<Enum::value>() << '\n';
}
```

### Requirements
- C++17 capable compiler

### Compiler support:
* GCC 8.1 - 14.2 (enum names since 9.1)
* CLANG 9.0 - 19.1
* ICX 2021.1 - 2024.2
* NVC 22.7 - 24.7
* MSVC 19.4
