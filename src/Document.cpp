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

#include <libxml/tree.h>

#include "utils.h"
#include "exceptions.h"

namespace xml
{
//------------------------------------------------------------------------------
    Document::Document()
    : cobj(xmlNewDoc(BAD_CAST "1.0"))
    {
        cobj->_private = this;
    }

//------------------------------------------------------------------------------
    Document::Document(const std::string &xml)
    : cobj(xmlNewDoc(BAD_CAST "1.0"))
    {
        cobj->_private = this;
        this->read_from_string(xml);
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
        xmlNode* const root = xmlDocGetRootElement(cobj);
        if (!root)
        {
            throw NoRootElement();
        }
        return reinterpret_cast<Element*>(root->_private);
    }

//------------------------------------------------------------------------------    
    const Element* Document::get_root_element() const
    {
        const xmlNode* const root = xmlDocGetRootElement(cobj);
        if (!root)
        {
            throw NoRootElement();
        }
        return reinterpret_cast<const Element*>(root->_private);
    }

//------------------------------------------------------------------------------
    Element* Document::create_root_element(const std::string& name)
    {
        xmlNode* const root = xmlNewDocNode(cobj, NULL, reinterpret_cast<const xmlChar*>(name.c_str()), NULL);
        xmlDocSetRootElement(cobj, root);
        if (!root)
        {
            throw exception(get_last_error());
        }
        return reinterpret_cast<Element*>(root->_private);
    }

//------------------------------------------------------------------------------    
    std::string Document::write_to_string() const
    {
        xmlChar* buffer = 0;
        int length = 0;

        xmlDocDumpMemory(cobj, &buffer, &length);
        if (!buffer)
        {
            throw exception(get_last_error());
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
    void Document::write_to_file(const std::string& file) const
    {
        int result = xmlSaveFormatFile(file.c_str(), cobj, 1);
        if (result == -1)
        {
            throw exception(get_last_error());
        }
    }
    
//------------------------------------------------------------------------------
    void Document::read_from_string(const std::string& xml)
    {
        xmlDoc* const tmp_cobj = xmlReadDoc(reinterpret_cast<const xmlChar*>(xml.c_str()), NULL, NULL, 0);
        if (!tmp_cobj)
        {        
            throw exception(get_last_error());
        }
            xmlFreeDoc(cobj);
            cobj = tmp_cobj;
        }

//------------------------------------------------------------------------------
    void Document::read_from_stream(std::istream& is)
    {
        read_from_string(read_until_eof(is));
    }

//------------------------------------------------------------------------------    
    void Document::read_from_file(const std::string& file)
    {
        xmlDoc* const tmp_cobj = xmlReadFile(file.c_str(), NULL, 0);
        if (!tmp_cobj)
        {        
            throw exception(get_last_error());
        }
            xmlFreeDoc(cobj);
            cobj = tmp_cobj;
        }
    
//------------------------------------------------------------------------------        
    Node* Document::find_node(const std::string& xpath)
    try
    {
        return get_root_element()->find_node(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

    
//------------------------------------------------------------------------------        
    const Node* Document::find_node(const std::string& xpath) const
    try
    {
        return get_root_element()->find_node(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------        
    std::vector<Node*> Document::find_nodes(const std::string& xpath)
    try
    {
        return get_root_element()->find_nodes(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------        
    std::vector<const Node*> Document::find_nodes(const std::string& xpath) const    
    try
    {
        return get_root_element()->find_nodes(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------            
    Element* Document::find_element(const std::string& xpath)
    try
    {
        return get_root_element()->find_element(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }
    
//------------------------------------------------------------------------------
    const Element* Document::find_element(const std::string& xpath) const
    try
    {
        return get_root_element()->find_element(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------    
    std::vector<Element*> Document::find_elements(const std::string& xpath)
    try
    {
        return get_root_element()->find_elements(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }
    
//------------------------------------------------------------------------------
    std::vector<const Element*> Document::find_elements(const std::string& xpath) const
    try
    {
        return get_root_element()->find_elements(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------
    std::string Document::query_string(const std::string& xpath) const
    try
    {
        return get_root_element()->query_string(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------    
    double Document::query_number(const std::string& xpath) const
    try
    {
        return get_root_element()->query_number(xpath);
    }
    catch(const NoRootElement &)
    {
        throw EmptyDocument();
    }

//------------------------------------------------------------------------------
    LIBXMLMM_EXPORT std::ostream& operator << (std::ostream& os, const Document& doc)
    {
        doc.write_to_stream(os);
        return os;
    }
    
//------------------------------------------------------------------------------
    LIBXMLMM_EXPORT std::istream& operator >> (std::istream& is, Document& doc)
    {
        doc.read_from_stream(is);
        return is;
    }
}
