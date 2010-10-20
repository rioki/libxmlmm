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

#include "Element.h"
#include "exceptions.h"
#include "utils.h"

#include <cassert>
#include <algorithm>
#include <typeinfo> 

namespace xml
{
//------------------------------------------------------------------------------
    Element::Element(xmlNode* const cobj)
    : Node(cobj) {}
    
//------------------------------------------------------------------------------    
    std::string Element::get_name() const
    {
        assert(cobj != NULL);
        if (cobj->name != NULL)
        {
            return reinterpret_cast<const char*>(cobj->name);
        }
        return "";
    }

//------------------------------------------------------------------------------        
    void Element::set_name(const std::string& value)
    {
        xmlNodeSetName(cobj, reinterpret_cast<const xmlChar*>(value.c_str()));
    }
    
//------------------------------------------------------------------------------
    bool Element::has_attribute(const std::string& key) const
    {
        return xmlGetProp(cobj, reinterpret_cast<const xmlChar*>(key.c_str())) != NULL;
    }
    
//------------------------------------------------------------------------------
    std::string Element::get_attribute(const std::string& key) const
    {
        const xmlChar* const value = xmlGetProp(cobj, reinterpret_cast<const xmlChar*>(key.c_str()));
        if (!value)
        {
            throw NoSuchAttribute(key, get_name());
        }
        return reinterpret_cast<const char*>(value);
    }
    
//------------------------------------------------------------------------------
    void Element::set_attribute(const std::string& key, const std::string& value)
    {
        xmlSetProp(cobj, reinterpret_cast<const xmlChar*>(key.c_str()), reinterpret_cast<const xmlChar*>(value.c_str()));
    }
        
//------------------------------------------------------------------------------
    void Element::remove_attribute(const std::string& key)
    {
        xmlUnsetProp(cobj, reinterpret_cast<const xmlChar*>(key.c_str()));    
    }

//------------------------------------------------------------------------------
    std::string Element::get_value() const
    {        
        const Content* const content = get_text_node();
        if (content != NULL)
        {
          return content->get_value();
        }
        return "";
    }

//------------------------------------------------------------------------------
    Content* Element::get_text_node() const
    {
        for(xmlNode* child = cobj->children; child; child = child->next)
        {
            if (child->type == XML_TEXT_NODE)
            {
                return reinterpret_cast<Content*>(child->_private);
            }
            if (child->type == XML_CDATA_SECTION_NODE)
            {
                return reinterpret_cast<Content*>(child->_private);
            }            
        }
        return NULL;
    }

//------------------------------------------------------------------------------
    void Element::set_text(const std::string& text)
    {
        Content* node = get_text_node();
        if(node)
        {
            node->set_content(text);
        }
        else
        {
            add_text(text);
        }
    }

//------------------------------------------------------------------------------
    void Element::add_text(const std::string& text)
    {
        xmlNode* node = xmlNewText(reinterpret_cast<const xmlChar*>(text.c_str()));
        xmlAddChild(cobj, node); 
    }

//------------------------------------------------------------------------------    
    Element* Element::add_element(const std::string& name)
    {
        xmlNode* node = xmlNewNode(NULL, reinterpret_cast<const xmlChar*>(name.c_str()));
        xmlAddChild(cobj, node); 
        return reinterpret_cast<Element*>(node->_private);
    }
    
//------------------------------------------------------------------------------    
    std::vector<Node*> Element::get_children()
    {
        std::vector<Node*> children;
        xmlNode* child = cobj->children;
        while (child != NULL)
        {
            children.push_back(reinterpret_cast<Node*>(child->_private));
            child = child->next;
        }
        return children;
    }

//------------------------------------------------------------------------------        
    std::vector<const Node*> Element::get_children() const
    {
        std::vector<const Node*> children;
        const xmlNode* child = cobj->children;
        while (child != NULL)
        {
            children.push_back(reinterpret_cast<const Node*>(child->_private));
            child = child->next;
        }
        return children;
    }
    
//------------------------------------------------------------------------------        
    Element* Element::find_element(const std::string& xpath)
    {
        return this->find<Element*>(xpath);
    }
    
//------------------------------------------------------------------------------
    const Element* Element::find_element(const std::string& xpath) const
    {
        return this->find<const Element*>(xpath);
    }
    
//------------------------------------------------------------------------------        
    std::vector<Element*> Element::find_elements(const std::string& xpath)
    {
        return this->find_all<Element*>(xpath);
    }

//------------------------------------------------------------------------------
    std::vector<const Element*> Element::find_elements(const std::string& xpath) const
    {
        return this->find_all<const Element*>(xpath);
    }
}
