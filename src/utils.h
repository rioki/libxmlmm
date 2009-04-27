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

#include <string>
#include <iosfwd>
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
    void wrap_node(xmlNode* node);
    
    /**
     * Free the wrapper of a node.
     *
     * @note This function is used as callback to libxml.
     **/
    void free_wrapper(xmlNode* node);
    
    /** Read from a stream until EOF. **/    
    std::string read_until_eof(std::istream& is);
}

#endif

