# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

list(APPEND EXTRA_CFLAGS -save-temps=obj)
list(APPEND EXTRA_CFLAGS -fno-tree-vrp -fno-tree-dominator-opts)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)


add_subdirectory(./src/Test)