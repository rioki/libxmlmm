
# libxmlmm


## About

Libxmlmm is a C++ wrapper for libxml 2.0 that only relies on standard C++ and 
libxml2.

## Install

### Dependencies

To build libxmlmm libxml2 is needed. The latest version of libxml2 can be found
at http://xmlsoft.org/. There the dependency iconv can also be found.

### Building with Make 

To install the library you use the traditional "GNU tipple jump":

    ./configure
    make
    make install
    
### Building with Visual Studio 2019

The windows version is actively developed with Visual Studio 2019. It is generally
encuraged to use vcpkg to get the dependencies. All you need is libxml2 and gtest.

## Documentation

Some simple introductory documentation can be found in the docs folder.

* [Writing a Document](docs/writing-a-document.md)
* [Reading a Document](docs/reading-a-document.md)

libxmlmm uses extensivly api documentation that can be extracted with doxygen.

## Further Information

You can find good resources on the official github page: 
http://github.com/rioki/libxmlmm
  
## Changes

2020-08-25 libxmlmm-0.6 

* Updates build system to include VS 2019.
* Changes to unit testing to gtest.
* Prepare code for vcpkg.

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

## Copying

	Copyright (c) 2008-2020 Sean Farrell

	Permission is hereby granted, free of charge, to any person obtaining a copy of 
	this software and associated documentation files (the "Software"), to deal in 
	the Software without restriction, including without limitation the rights to use, 
	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
	Software, and to permit persons to whom the Software is furnished to do so, 
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all 
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
