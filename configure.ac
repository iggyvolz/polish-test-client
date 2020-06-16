# files=`find ./src -type f -regex  '.*\(hpp\|cpp\)$' -exec printf ' '{} \;`
# sed -i "s@^._SOURCES\$@polish_SOURCES=$files@" src/Makefile.am
AC_INIT([amhello], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
])

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=true])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AC_OUTPUT
