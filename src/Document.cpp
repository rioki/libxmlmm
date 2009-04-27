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

#include "Document.h"

#include <stdexcept>
#include <libxml/tree.h>

#include "utils.h"

namespace xml
{
//------------------------------------------------------------------------------
    Document::Document()
    : cobj(xmlNewDoc(BAD_CAST "1.0"))
    {
        cobj->_private = this;
    }

//------------------------------------------------------------------------------
    Document::~Document()
    {
        xmlFreeDoc(cobj);
    }

//------------------------------------------------------------------------------
    bool Document::has_root_element() const
    {
        return xmlDocGetRootElement(cobj) != NULL;    
    }

//------------------------------------------------------------------------------
    Element* Document::get_root_element()
    {
        xmlNode* root = xmlDocGetRootElement(cobj);
        if (root != NULL)
        {
            return reinterpret_cast<Element*>(root->_private);
        }
        else
        {
            throw std::logic_error("no root element");
        }
    }

//------------------------------------------------------------------------------    
    const Element* Document::get_root_element() const
    {
        return const_cast<Document*>(this)->get_root_element();
    }

//------------------------------------------------------------------------------
    Element* Document::create_root_element(const std::string& name)
    {
        xmlNode* root = xmlNewDocNode(cobj, NULL, reinterpret_cast<const xmlChar*>(name.c_str()), NULL);
        xmlDocSetRootElement(cobj, root);
        if (root != NULL)
        {
            return reinterpret_cast<Element*>(root->_private);
        }
        else
        {
            throw std::logic_error(get_last_error());            
        }
    }

//------------------------------------------------------------------------------    
    std::string Document::write_to_string() const
    {
        xmlChar* buffer = 0;
        int length = 0;

        xmlDocDumpMemory(cobj, &buffer, &length);
        if (!buffer)
        {
            throw std::runtime_error(get_last_error());
        }
        std::string xml(reinterpret_cast<const char*>(buffer));

        xmlFree(buffer);
        
        return xml;
    }

//------------------------------------------------------------------------------    
    void Document::write_to_stream(std::ostream& os) const
    {
        os << write_to_string();    
    }
    
//------------------------------------------------------------------------------
    void Document::read_from_string(const std::string& xml)
    {
        xmlDoc* tmp_cobj = xmlReadDoc(reinterpret_cast<const xmlChar*>(xml.c_str()), NULL, NULL, 0);
        if (tmp_cobj != NULL)                
        {        
            xmlFreeDoc(cobj);
            cobj = tmp_cobj;
        }
        else
        {
            throw std::runtime_error(get_last_error());            
        }
    }    

//------------------------------------------------------------------------------
    void Document::read_from_stream(std::istream& is)
    {
        read_from_string(read_until_eof(is));
    }

//------------------------------------------------------------------------------
    std::ostream& operator << (std::ostream& os, const Document& doc)
    {
        doc.write_to_stream(os);
        return os;
    }
    
//------------------------------------------------------------------------------
    std::istream& operator >> (std::istream& is, Document& doc)
    {
        doc.read_from_stream(is);
        return is;
    }
}

