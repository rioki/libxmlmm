//
// libxmlmmm
// Copyright 2008 - 2009 Sean Farell
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
    struct exception : std::runtime_error
    {
        explicit exception(const std::string &what)
            : runtime_error("xmlmm: " + what) {}
        ~exception() throw() {}
    };

    struct NoRootElement : exception
    {
        NoRootElement() : exception("No root element") {}
    };

    struct EmptyDocument : exception
    {
        EmptyDocument() : exception("Document is empty") {}
    };

    struct InvalidXPath : exception
    {
        explicit InvalidXPath(const std::string &xpath)
            : exception("Invalid XPath: " + xpath) {}
        ~InvalidXPath() throw() {}
    };

    struct NoSuchAttribute : exception
    {
        NoSuchAttribute(const std::string &attribute,
                        const std::string &nodeName)
            : exception("There is no attribute '" + attribute +
                        "' on the element '" + nodeName + "'.") {}
        ~NoSuchAttribute() throw() {}
    };
}

#endif
