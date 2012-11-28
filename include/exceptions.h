//
// libxmlmmm
// Copyright 2008 - 2011 Sean Farell
//
// This file is part of libqgl.
//
// libxmlmmm is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libxmlmmm is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with libxmlmmm. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _LIBXMLMM_EXCEPTIONS_H_
#define _LIBXMLMM_EXCEPTIONS_H_

#include <stdexcept>

namespace xml
{
    struct Exception : std::runtime_error
    {
        explicit Exception(const std::string &what)
        : runtime_error("xmlmm: " + what) {}
        
        ~Exception() throw() {}
    };

    struct NoRootElement : Exception
    {
        NoRootElement() 
        : Exception("No root element") {}
    };

    struct EmptyDocument : Exception
    {
        EmptyDocument() 
        : Exception("Document is empty") {}
    };

    struct InvalidXPath : Exception
    {
        explicit InvalidXPath(const std::string &xpath)
        : Exception("Invalid XPath: " + xpath) {}
        
        ~InvalidXPath() throw() {}
    };

    struct NoSuchAttribute : Exception
    {
        NoSuchAttribute(const std::string &attribute, const std::string &nodeName)
        : Exception("There is no attribute '" + attribute + "' on the element '" + nodeName + "'.") {}
        
        ~NoSuchAttribute() throw() {}
    };
}

#endif
