dnl 
dnl Copyright (c) 2008 - 2009 Sean Farrell
dnl 
dnl Permission is hereby granted, free of charge, to any person
dnl obtaining a copy of this software and associated documentation
dnl files (the "Software"), to deal in the Software without
dnl restriction, including without limitation the rights to use,
dnl copy, modify, merge, publish, distribute, sublicense, and/or sell
dnl copies of the Software, and to permit persons to whom the
dnl Software is furnished to do so, subject to the following
dnl conditions:
dnl 
dnl The above copyright notice and this permission notice shall be
dnl included in all copies or substantial portions of the Software.
dnl 
dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl OTHER DEALINGS IN THE SOFTWARE.
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

