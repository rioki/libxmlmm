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

#include "utils.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <libxml/xmlerror.h>

#include "Node.h"
#include "Element.h"
#include "Text.h"
#include "Comment.h"
#include "CData.h"
#include "ProcessingInstruction.h"
#include "Attribute.h"

namespace xml
{
//------------------------------------------------------------------------------
    std::string get_last_error()
    {
        const xmlError* const error = xmlGetLastError();
        if (error != NULL)
        {
            return error->message;
        }
        else
        {
            return "";
        }
    }

//------------------------------------------------------------------------------    
    void wrap_node(xmlNode* const cobj)
    {
        switch (cobj->type)
        {
            case XML_ELEMENT_NODE:
            {
                cobj->_private = new Element(cobj);
                break;
            }
            case XML_TEXT_NODE:
            {
                cobj->_private = new Text(cobj);
                break;
            }
            case XML_COMMENT_NODE:
            {
                cobj->_private = new Comment(cobj);
                break;
            }
            case XML_CDATA_SECTION_NODE:
            {
                cobj->_private = new CData(cobj);
                break;
            }
            case XML_PI_NODE:
            {
                cobj->_private = new ProcessingInstruction(cobj);
                break;
            }
            case XML_ATTRIBUTE_NODE:
            {
                cobj->_private = new Attribute(cobj);
                break;    
            }
            case XML_DOCUMENT_NODE:
            {
                /* this node is not wrapped */
                break;
            }
            default:
            {
                break;
            }
        }
    }

//------------------------------------------------------------------------------    
    void free_wrapper(xmlNode* const cobj)
    {
        switch (cobj->type)
        {
            case XML_ELEMENT_NODE:
            case XML_TEXT_NODE:
            case XML_COMMENT_NODE:
            case XML_CDATA_SECTION_NODE:
            case XML_PI_NODE:
            case XML_ATTRIBUTE_NODE:
            {
                Node* const node = reinterpret_cast<Node* const>(cobj->_private);
                delete node;
                cobj->_private = NULL;
                break;
            }                        
            case XML_DOCUMENT_NODE:
            {
                /* there nodes are not wrapped */
                break;
            }
            default:
            {
                break;
            }
        }
    }

//------------------------------------------------------------------------------        
    std::string read_until_eof(std::istream& is)
    {
        std::string result;
        const std::ios_base::fmtflags saved = is.flags();
        is.unsetf(std::ios::skipws);
        std::copy(std::istream_iterator<char>(is),
                  std::istream_iterator<char>(),
                  std::back_inserter(result));
        is.flags(saved);
        return result;
    }
}
