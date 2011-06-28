dnl libral
dnl Germanov Artem <ru.netz@gmail.com>

dnl Init
AC_INIT([libral],[0.1])
AC_CONFIG_SRCDIR([src/ral.c])
AM_INIT_AUTOMAKE
LT_PREREQ([2.2])
LT_INIT([dlopen])

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC

AC_DEFINE(HAVE_STDC)

dnl
dnl Get snappy library and include locations
dnl 

AC_ARG_WITH([snappy],
  [AS_HELP_STRING([--with-snappy], [snappy support])],
  [],
  [with_snappy=yes])

if test "x${with_snappy}" = "xyes"; then
    have_snappy=no
    AC_SEARCH_LIBS([snappy_compress], [snappy], [have_snappy=yes])

    if test "x${have_snappy}" = xyes; then
        AC_CHECK_HEADERS([snappy-c.h], [], [have_snappy=no])
    fi

    if test "x${have_snappy}" = xno; then
        AC_MSG_WARN([
------------------------------------
Unable to find libsnappy on this system.
Building without it.
------------------------------------])
        with_snappy=no
    fi
fi

if test "x${with_snappy}" = xyes; then
    AC_DEFINE([HAVE_SNAPPY])
fi

dnl
dnl Get lzo library and include locations
dnl

AC_ARG_WITH([lzo],
  [AS_HELP_STRING([--with-lzo], [lzo support])],
  [],
  [with_lzo=yes])

if test "x${with_lzo}" = "xyes"; then
    have_lzo=no
    AC_SEARCH_LIBS([lzo1x_decompress], [lzo2], [have_lzo=yes])

    if test "x${have_lzo}" = xyes; then
        AC_CHECK_HEADERS([lzo/lzoconf.h], [], [have_lzo=no])
    fi

    if test "x${have_lzo}" = xno; then
        AC_MSG_WARN([
------------------------------------
Unable to find liblzo on this system.
Building without it.
------------------------------------])
        with_lzo=no
    fi
fi

if test "x${with_lzo}" = xyes; then
    AC_DEFINE([HAVE_LZO])
fi

dnl
dnl Check for zlib
dnl

AC_ARG_WITH([zlib],
   [AS_HELP_STRING([--with-zlib], [zlib support])],
   [with_zlib="$enableval"],
   [with_zlib="yes"] 
)
AS_IF([test "x$with_zlib" = "xyes"], [
    PKG_CHECK_MODULES([DEPS], [zlib])
    AC_DEFINE(HAVE_GZ)
])



dnl Output
AC_OUTPUT([Makefile src/Makefile])
