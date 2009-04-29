##
## libxmlmmm
## Copyright 2008 - 2009 Sean Farell
##
## This file is part of libqgl.
##
## libxmlmmm is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## libxmlmmm is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with libxmlmmm. If not, see <http:##www.gnu.org/licenses/>.
##

pkginclude_HEADERS   = LibXmlSentry.h Document.h Node.h Element.h \
                       Content.h Text.h CData.h Comment.h \
                       ProcessingInstruction.h Attribute.h utils.h libxmlmm.h

lib_LTLIBRARIES      = libxmlmm.la

libxmlmm_la_CXXFLAGS = @LIBXML_CFLAGS@
libxmlmm_la_LDFLAGS  = -version-info @LT_VERSION@
libxmlmm_la_LIBADD   = @LIBXML_LIBS@
libxmlmm_la_SOURCES  = LibXmlSentry.cpp Document.cpp Node.cpp Element.cpp \
                       Content.cpp Text.cpp CData.cpp Comment.cpp \
                       ProcessingInstruction.cpp Attribute.cpp utils.cpp

