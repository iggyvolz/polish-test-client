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
AC_OUTPUT

