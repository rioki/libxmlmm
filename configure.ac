dnl
dnl libxmlmmm
dnl Copyright 2008 - 2009 Sean Farell
dnl
dnl This file is part of libqgl.
dnl
dnl libxmlmmm is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU Lesser General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl libxmlmmm is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU Lesser General Public License
dnl along with libxmlmmm. If not, see <http:dnlwww.gnu.org/licenses/>.
dnl

AC_INIT([libxmlmm], [0.1])
AM_INIT_AUTOMAKE([foreign])

dnl Libtool Version (current:revision:age)
LT_VERSION="0:0:0"
dnl 1. Start with version information of ‘0:0:0’ for each libtool library.
dnl 2. Update the version information only immediately before a public release 
dnl    of your software. More frequent updates are unnecessary, and only 
dnl    guarantee that the current interface number gets larger faster.
dnl 3. If the library source code has changed at all since the last update, 
dnl    then increment revision (‘c:r:a’ becomes ‘c:r+1:a’).
dnl 4. If any interfaces have been added, removed, or changed since the last 
dnl    update, increment current, and set revision to 0.
dnl 5. If any interfaces have been added since the last public release,  
dnl    then increment age.
dnl 6. If any interfaces have been removed since the last public release, 
dnl    then set age to 0. 
AC_SUBST(LT_VERSION)


AC_LANG([C++])

AC_PROG_CXX
AC_PROG_LIBTOOL


PKG_CHECK_MODULES(LIBXML, [libxml-2.0 >= 2.6])
AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)


AC_CHECK_LIB([UnitTest++], [main], UT_LIBS="-lUnitTest++", 
    AC_MSG_WARN([*** UnitTest++ not found.]))
AC_CHECK_HEADER([UnitTest++/UnitTest++.h], :, 
    AC_MSG_WARN([*** UnitTest++ headers not found.]))
AM_CONDITIONAL([BUILD_TESTS], [test $UT_LIBS != ""])
AC_SUBST(UT_LIBS)


AC_CHECK_PROG(DOXYGEN, [doxygen], [doxygen], [false])
AC_CHECK_PROG(HAVE_DOT, [dot], [YES], [NO])
AM_CONDITIONAL([BUILD_DOC], [test $DOXYGEN != "false"])
AC_SUBST(DOXYGEN)
AC_SUBST(HAVE_DOT)


AC_CONFIG_FILES([
    Makefile 
    libxmlmm.pc 
    src/Makefile 
    test/Makefile
    examples/Makefile
    doc/Makefile
    doc/Doxyfile
])

AC_OUTPUT

