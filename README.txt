
====== libxmlmm ======

Libxmlmm is a C++ wrapper for libxml 2.0 that only relies on standard C++ and 
libxml2.


===== License =====

Libxmlmm is free software and is licensed under the MIT-License. The exact
terms are:

  Copyright (c) 2008 Sean Farrell
  
  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without
  restriction, including without limitation the rights to use,
  copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following
  conditions:
  
  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

===== Building =====

Libxmlmm comes with a build system that is fully GNU compatible.

  ./configure
  make
  make install

Libxmlmm only depends on libxml 2.0 and can be found at http://xmlsoft.org.

===== Using libxmlmm =====

Once libxmlmm is built and installed you can link against it:

  -lxmlmm
  
libxmlmm comes with a pkg-config input file. You can use it with 
PKG_CHECK_MODULE in a autoconf file.

  PKG_CHECK_MODULE(XMLMM, [libxmlmm >= 1.0])

===== Documentation =====

The source code of libxmlmm is annotated with doxygen. To build documentation 
you need doxygen, which you can find at http://www.doxygen.org. Having 
graphviz's dot makes pretty pictures. Graphviz can be found at 
http://www.graphviz.org.

To build the documentation run:

  make doc

The resulting documentation can be found in the doc/html directory. 

===== Examples =====

Introductory examples can be found in the examples directory. They are direct
translations from the libxml examples.

===== Unit Tests =====

Libxmlmm was built with unit tests. The UnitTest++ framework was used. You can
find UnitTest++ at http://unittest-cpp.sourceforge.net/.

To build and run the unit tests:

  make check
  
If you have problems with libxmlmm you should run the tests, if one fails 
please report the errors.  

