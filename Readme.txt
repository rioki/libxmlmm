
libxmlmm

1. About

Libxmlmm is a C++ wrapper for libxml 2.0 that only relies on standard C++ and 
libxml2.


2. Install

To install the library you use the traditional "GNU tipple jump":

    ./configure
    make
    make install


3. Copying

Libxmlmm is released under the Lesser GNU Public License. 
See COPYING.txt for details.

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
