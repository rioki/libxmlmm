
libxmlmm

1. About

Libxmlmm is a C++ wrapper for libxml 2.0 that only relies on standard C++ and 
libxml2.


2. Install

2.1 Dependencies

To build libxmlmm you need libxml2. You can get it from http://xmlsoft.org/.

2.2 Building With Make 

To install the library you use the traditional "GNU tipple jump":

    ./configure
    make
    make install

2.2 Building With Visual Studio

Currently you can build libxmlmm with Visual Studio 2008. Upgrading to 
a newer version (like VS 2010) should work flawless. You can either add 
the project to your solution or distribute the binary files to a common 
location.
    
3. Copying

Libxmlmm is released under the Lesser GNU Public License. 
See Copying.txt for details.

4. Further Information

You can find good resources on the official project website 
http://libxmlmm.rioki.org.

5. Changes

2009-04-27 libxmlmm-0.1

    * Wrappers for all basic node types.
    * Load and save of documents.
    * Basic access API for node types.

2009-05-10 libxmlmm-0.2

    * XPath expression for simple types (query_string, query_number).
    * Access to nodes and with the help of XPath expression.
    * Specialisation for elements to XPath nodes queries.

2009-10-15 libxmlmm-0.3

    * Improved error message in Element::get_attribute.
    * Fixed crash in Node::query_number.
    * Adapted build system to build a windows DLL.

2010-04-08 libxmlmm-0.4
    
    * Visual Studio 2008 support.
