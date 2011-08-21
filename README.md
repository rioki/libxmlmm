
========
libxmlmm
========

About
=====

Libxmlmm is a C++ wrapper for libxml 2.0 that only relies on standard C++ and 
libxml2.

Install
=======

Dependencies
------------

To build libxmlmm libxml2 is needed. The latest version of libxml2 can be found
at http://xmlsoft.org/. There the dependency iconv can also be found.

For the unit tests UnitTest++ is required. The latest version can be found
at http://unittest-cpp.sourceforge.net/. (The active development moved to
http://code.google.com/p/unittestpp/, but there seems not to be much activity.)

Building with Make 
------------------

To install the library you use the traditional "GNU tipple jump":

    ./configure
    make
    make install
    
Building with CodeLite
----------------------

The windows version is actively developed with CodeLite. To build the package
you will have to set the environment variables ICONV_DIR, LIBXML2_DIR and 
UNIT_TEST_DIR to the corresponding dependencies.

Building With Visual Studio
---------------------------

Although Visual Studio is useful for many, this package is not developed with
Visual Studio. As a result keeping the Visual Studio build files up to date
is problematic, especially since Microsoft adds incompatible file formats every
3 years. Patches of up to date Visual Studio build configurations are welcome.

The sources should be buildable with MSC from version 8 (VS 2005) to version 10
(VS 2010). Just create a native dynamic library project with all files from
src and include/libxmlmm. You can build the unit tests by creating a native 
win32 executable and add all files from test. You will need a copy of 
UnitTest++.
   
Copying
=======

Libxmlmm is released under the Lesser GNU Public License. 
See Copying.txt for details.

Known Issues
============

* When building with MinGW it is imperitive to use a version above 4.4 and
the same exception model. If the exception model is different any exception
that tries to propagate over a DLL boundary will cause a process abort.

Further Information
===================

You can find good resources on the official github page: 
http://github.com/rioki/libxmlmm.
  
Changes
=======

2011-08-21 libxmlmm-0.5

* Cleans up some code.
* Adds build support with CodeLite and MinGW32 (gcc 4.5.2).
* Drops active Visual Studio support.    
* Adds API documentation with doxygen on Windows platform.
* Limits used of dllexport to MSC. (YAY, gcc auto export...)

2010-04-08 libxmlmm-0.4
    
* Visual Studio 2008 support.
    
2009-10-15 libxmlmm-0.3

* Improved error message in Element::get_attribute.
* Fixed crash in Node::query_number.
* Adapted build system to build a windows DLL.    
    
2009-05-10 libxmlmm-0.2

* XPath expression for simple types (query_string, query_number).
* Access to nodes and with the help of XPath expression.
* Specialisation for elements to XPath nodes queries.

2009-04-27 libxmlmm-0.1

* Wrappers for all basic node types.
* Load and save of documents.
* Basic access API for node types.
