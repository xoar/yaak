#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([Odin], [1.17.11], [odin-build-users@lists.sourceforge.net])
AC_CONFIG_SRCDIR([pkg])
AC_CONFIG_HEADERS([pkg/odin/inc/config.hh])

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_LEX
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_YACC

if test "$LN_S" != 'ln -s'; then
   AC_MSG_ERROR([Odin requires symbolic links])
fi

# Checks for libraries.

AC_SEARCH_LIBS(t_accept, nsl)
AC_SEARCH_LIBS(socket, socket)

changequote(<<, >>)
LIBS_QUOTED=`echo $LIBS | sed -e "s/-L\([^ ]*\)/+lib_sp=(\1)/g" -e "s/-l\([^ ]*\)/+lib='\1'/g" -e "s/-R [^ ]*//g"`
changequote([, ])
AC_SUBST(LIBS_QUOTED)

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([dirent.h process.h termio.h termios.h unistd.h unix.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_WAIT3
AC_CHECK_FUNCS([getcwd putenv sigaction waitpid])

AC_CONFIG_FILES([pkg/config/boot.sh pkg/config/config.dg pkg/config/version])
AC_OUTPUT
