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

#ifndef _LIBXMLMM_UTILS_H_
#define _LIBXMLMM_UTILS_H_

#include <iosfwd>
#include <string>
#include <sstream>
#include <libxml/tree.h>

namespace xml
{    
    /**
     * Get the last error as string from libxml.
     **/
    std::string get_last_error();
    
    /**
     * Wrap a node.
     *
     * @note This function is used as callback to libxml.
     **/
    void wrap_node(xmlNode* const node);
    
    /**
     * Free the wrapper of a node.
     *
     * @note This function is used as callback to libxml.
     **/
    void free_wrapper(xmlNode* node);
    
    /** Read from a stream until EOF. **/    
    std::string read_until_eof(std::istream& is);
    
    /**
     * Convert arbitrary value to string.
     **/
    // TODO: shouldn't this be "const T&" to avoid copy?  consider when this
    // is a complex object.
    template <typename T>
    std::string to_string(T value)
    {
        std::stringstream buff;
        buff << value;
        return buff.str();
    }
    
    /**
     * Convert arbitrary value from string.
     **/
    template <typename T>
    T from_string(const std::string& str)
    {
        std::stringstream buff(str);
        T value;
        buff >> value;
        return value;
    }
}

#endif
