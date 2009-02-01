AC_INIT([sadegh_g], [bd], [sadegh@lrde.epita.fr])

AC_PREREQ([2.57])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.7.5 dist-bzip2 no-dist-gzip no-installinfo -Wall foreign])

dnl If the user didn't supplied a CXXFLAGS value,
dnl set an empty one to prevent autoconf to stick -O2 -g here.
test -z $CXXFLAGS && CXXFLAGS=

dnl Checks for programs.
AC_PROG_CXX([g++42 g++43 g++ cc])

CXXFLAGS="${CXXFLAGS} -Wall -W -Werror -O3 -funroll-loops -ffast-math" dnl -ffast-math ?

boost_filesystem=boost_filesystem
dnl --with-boost-filesystem
dnl AC_ARG_WITH([boost-filesystem],
dnl   [AS_HELP_STRING([--with-boost-filesystem], [])],
dnl   [boost_filesystem=$with_boost_filesystem], [])

LDFLAGS="$LDFLAGS -L/usr/local/lib -l$boost_filesystem"

AC_CANONICAL_HOST

case "$host_os" in
    linux*)
	;;
    freebsd*)
         CXXFLAGS="${CXXFLAGS} -I /usr/local/include"
	;;
    *)
    cat <<EOF
******************************************************************
WARNING: your system, _${host_os}_, was never tested. It may or
may not work.

Good luck !
******************************************************************
EOF
    sleep 2
  ;;
esac


dnl --with-debug.
AC_ARG_WITH([debug],
  [AS_HELP_STRING([--with-debug],
    [For debugging with gdb])],
  [with_debug=yes;
  echo "compiling in debug mode ... -ggdb3";
  CXXFLAGS="$CXXFLAGS -ggdb3"],
  [CXXFLAGS="${CXXFLAGS} -DNDEBUG"])

dnl Check libraries.

dnl dnl Check for OpenGL
dnl AC_CHECK_HEADERS(GL/gl.h GL/glu.h, ,
dnl [AC_MSG_ERROR([OpenGL is require (`apt-get install libgl1-mesa-dev libglu1-mesa-dev` with Ubuntu)])])
dnl
dnl AC_CHECK_LIB(GL, glInitNames, ,
dnl [AC_MSG_ERROR([OpenGL is require (`apt-get install libgl1-mesa-dev libglu1-mesa-dev` with Ubuntu)])])
dnl
dnl dnl Check for glut libary
dnl AC_CHECK_HEADERS(GL/glut.h, ,
dnl [AC_MSG_ERROR([GLut is require (apt-get install freeglut3-dev with Ubuntu)])])
dnl
dnl AC_CHECK_LIB(glut, glutInit, ,
dnl [AC_MSG_ERROR([GLut is require (apt-get install freeglut3-dev with Ubuntu)])])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/core/Makefile
])

AC_OUTPUT
