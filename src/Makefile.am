## 
## Copyright (c) 2008 Sean Farrell
## 
## Permission is hereby granted, free of charge, to any person
## obtaining a copy of this software and associated documentation
## files (the "Software"), to deal in the Software without
## restriction, including without limitation the rights to use,
## copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the
## Software is furnished to do so, subject to the following
## conditions:
## 
## The above copyright notice and this permission notice shall be
## included in all copies or substantial portions of the Software.
## 
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
## EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
## OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
## NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
## HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
## WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
## FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
## OTHER DEALINGS IN THE SOFTWARE.
## 

pkginclude_HEADERS   = LibXmlSentry.h Document.h Node.h Element.h \
                       Content.h Text.h CData.h Comment.h \
                       ProcessingInstruction.h utils.h

lib_LTLIBRARIES      = libxmlmm.la

libxmlmm_la_CXXFLAGS = @LIBXML_CFLAGS@
libxmlmm_la_LDFLAGS  = --version-info @LTVERSION@
libxmlmm_la_LIBADD   = @LIBXML_LIBS@
libxmlmm_la_SOURCES  = LibXmlSentry.cpp Document.cpp Node.cpp Element.cpp \
                       Content.cpp Text.cpp CData.cpp Comment.cpp \
                       ProcessingInstruction.cpp utils.cpp

