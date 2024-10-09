/*
 * Copyright (C) 2024 Eugene Hutorny <eugene@hutorny.in.ua>
 *
 * test_main.cpp - Unit test runner
 *
 * Licensed under MIT License, see full text in LICENSE
 * or visit page https://opensource.org/license/mit/
 */

#include <gtest/gtest.h>
#include <iostream>

#ifndef NAMEOF_SKIP_SELFCHECK
#include <meta/nameof_selfcheck.h>
#endif

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
