dnl ************************************************************************
dnl
dnl This file is part of the Cal3D library/package
dnl Copyright (C) 2002 Bruno 'Beosil' Heidelberger (beosil@swileys.com)
dnl Copyright (C) 2006 Loic Dachary <loic@dachary.org>
dnl
dnl This library is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU Lesser General Public License as published by
dnl the Free Software Foundation; either version 2.1 of the License, or (at
dnl your option) any later version.
dnl
dnl ************************************************************************

AC_INIT
AC_CONFIG_SRCDIR([src/cal3d/cal3d.h])

AM_CONFIG_HEADER(config.h)

AC_CANONICAL_TARGET
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE(cal3d,0.12.0)

AC_ARG_WITH(cxx,[  --with-cxx=CXX          force the use of a particular C++ compiler ],
[
  CXX="$withval"
],)

AC_ARG_WITH(cc,[  --with-cc=CC            force the use of a particular C compiler ],
[
  CC="$withval"
],)


dnl ************************************************************************

CAL3D_CHECK_USER_CXX_FLAGS

dnl ************************************************************************

AC_PROG_CXX

AC_DISABLE_STATIC

LT_INIT(win32-dll)

AC_PROG_INSTALL

AC_CHECK_PROG(DOXYGEN, doxygen, true, false)
if test "$DOXYGEN" = false; then
  AC_MSG_WARN([cannot find doxygen, unable to generate Cal3D API Reference!])
fi

AC_CHECK_PROG(DB2HTML, db2html, true, false)
if test "$DB2HTML" = false; then
  AC_MSG_WARN([cannot find db2html, unable to generate Cal3D User's Guide!])
fi

AC_PATH_PROG(BLENDER, [blender])
AC_PATH_PROG(VALGRIND, [valgrind])

# Check for unittest++
#AM_USE_UNITTESTCPP

CPPFLAGS="$CPPFLAGS"' -I${top_srcdir}/src'

dnl ************************************************************************

CAL3D_CHECK_BUILD

dnl ************************************************************************

AC_CONFIG_FILES([tests/coverage/test-coverage],[chmod 555 $ac_file])

AC_CONFIG_FILES([Makefile src/Makefile src/cal3d/Makefile docs/Makefile docs/api/Makefile docs/shared/Makefile tests/Makefile tests/coverage/Makefile tests/run cal3d.pc src/cal3d_converter.1 fileformats.txt])
AC_OUTPUT

dnl AC_CONFIG_FILES([test-coverage],[chmod 555 $ac_file])

dnl ************************************************************************

echo "o-----------------------------------------------------------o"
echo "| To build and install the Cal3D library type...            |"
echo "|     make; make install                                    |"

echo "|                                                           |"

if test "$DB2HTML" = false; then
  echo "| To generate the Cal3D User's Guide you need to install    |"
  echo "| the DocBook tools first. ('docbktls' package)             |"
else
  echo "| To generate the Cal3D User's Guide type...                |"
  echo "|     cd docs; make doc-guide                               |"
fi

echo "|                                                           |"

if test "$DOXYGEN" = false; then
  echo "| To generate the Cal3D API Reference you need to install   |"
  echo "| the Doxygen tool first. (see http://www.doxygen.org)      |"
else
  echo "| To generate the Cal3D API Reference type...               |"
  echo "|     cd docs; make doc-api                                 |"
fi

echo "o-----------------------------------------------------------o"

dnl ************************************************************************

