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

