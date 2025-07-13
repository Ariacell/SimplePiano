set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

# Cross compilers to use for C, C++ and Fortran.

# NOTE: Use -posix suffix to explicitly use the pthreads threading model. By
# default, the -win32 based threading model is used.
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc-posix)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++-posix)
set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

# Extra compiler and library flags.
set(CMAKE_C_FLAGS_INIT "-D_WIN32_WINNT=0x600")
set(CMAKE_CXX_FLAGS_INIT "-D_WIN32_WINNT=0x600")
set(CMAKE_C_STANDARD_LIBRARIES "-lws2_32")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lws2_32")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-lws2_32")
set(CMAKE_STATIC_LINKER_FLAGS_INIT "-lws2_32")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-lws2_32")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-lws2_32")

# target environment on the build host system.
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_FIND_ROOT_PATH})
set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_FIND_ROOT_PATH}/usr/lib/pkgconfig:${CMAKE_FIND_ROOT_PATH}/usr/share/pkgconfig")

# Modify default behavior of FIND_XXX() commands.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)