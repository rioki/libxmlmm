// 
// Copyright (c) 2008 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 

#include "utils.h"

#include <cassert>
#include <iostream>
#include <libxml/xmlerror.h>

#include "Node.h"
#include "Element.h"
#include "Text.h"
#include "Comment.h"
#include "CData.h"
#include "ProcessingInstruction.h"

namespace xml
{
//------------------------------------------------------------------------------
    std::string get_last_error()
    {
        xmlError* error = xmlGetLastError();
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
    void wrap_node(xmlNode* cobj)
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
            case XML_DOCUMENT_NODE:
            {
                /* there nodes are not wraped */
                break;
            }
            default:
            {
                assert(false && "unknown type");
                
                cobj->_private = new Node(cobj);
                break;
            }
        }
    }

//------------------------------------------------------------------------------    
    void free_wrapper(xmlNode* cobj)
    {
        switch (cobj->type)
        {
            case XML_ELEMENT_NODE:
            case XML_TEXT_NODE:
            case XML_COMMENT_NODE:
            case XML_CDATA_SECTION_NODE:
            case XML_PI_NODE:
            {
                Node* node = reinterpret_cast<Node*>(cobj->_private);
                delete node;
                cobj->_private = NULL;
                break;
            }
            case XML_ATTRIBUTE_NODE:                        
            case XML_DOCUMENT_NODE:
            {
                /* there nodes are not wraped */
                break;
            }
            default:
            {
                assert(false && "unknown type");
                
                Node* node = reinterpret_cast<Node*>(cobj->_private);
                delete node;
                cobj->_private = NULL;
                break;
            }
        }
    }

//------------------------------------------------------------------------------        
    std::string read_until_eof(std::istream& is)
    {
        // TODO Can this be done more effectivly?
        std::string result;
        while (is.good())
        {
            char c = is.get();
            if (is.good())
            {
                result += c;
            }
        }
        return result;
    }
}

