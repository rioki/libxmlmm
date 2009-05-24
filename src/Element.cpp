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

#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <typeinfo> 

namespace xml
{
//------------------------------------------------------------------------------
    Element::Element(xmlNode* cobj)
    : Node(cobj) {}
    
//------------------------------------------------------------------------------    
    std::string Element::get_name() const
    {
        assert(cobj != NULL);
        if (cobj->name != NULL)
        {
            return reinterpret_cast<const char*>(cobj->name);
        }
        else
        {
            return "";
        }
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
        const xmlChar* value = xmlGetProp(cobj, reinterpret_cast<const xmlChar*>(key.c_str()));
        if (value != NULL)
            return reinterpret_cast<const char*>(value);
        else
            throw std::logic_error("There is no attribtue '" + key + "' on the element '" + get_name() + "'." );
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
    std::string Element::get_text() const
    {
        Text* text = get_text_node();
        if (text != NULL)
        {
            return text->get_content();
        }
        else
        {
            return "";
        }
    }

//------------------------------------------------------------------------------
    Text* Element::get_text_node() const
    {
        for(xmlNode* child = cobj->children; child; child = child->next)
        {
            if(child->type == XML_TEXT_NODE)
            {
                return reinterpret_cast<Text*>(child->_private);
            }
        }
        return NULL;
    }

//------------------------------------------------------------------------------
    void Element::set_text(const std::string& text)
    {
        Text* node = get_text_node();
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
        xmlNode* child = cobj->children;
        if(child == NULL)
        {
            return std::vector<Node*>();
        }

        std::vector<Node*> children;
        do
        {
            children.push_back(reinterpret_cast<Node*>(child->_private));
            child = child->next;
        }
        while(child != NULL);
        
        return children;
    }

//------------------------------------------------------------------------------        
    std::vector<const Node*> Element::get_children() const
    {
        std::vector<Node*> children = const_cast<Element*>(this)->get_children();
        std::vector<const Node*> result(children.size());
        std::copy(children.begin(), children.end(), result.begin());
        return result;
    }

//------------------------------------------------------------------------------            
    Element* Element::find_element(const std::string& xpath)
    {
        return dynamic_cast<Element*>(find_node(xpath));
    }
    
//------------------------------------------------------------------------------        
    const Element* Element::find_element(const std::string& xpath) const
    {
        return const_cast<Element*>(this)->find_element(xpath);
    }
    
//------------------------------------------------------------------------------
    Element* cast_node_to_element(Node* node)    
    {
        if (node == NULL)
            throw std::logic_error("cast_node_to_element: 'node' is NULL");
            
        Element* elem = dynamic_cast<Element*>(node);        
        if (elem != NULL)
            return elem;
        else
            throw std::runtime_error("The node is not an element. (" + node->get_path() + ")");
    }
    
//------------------------------------------------------------------------------        
    std::vector<Element*> Element::find_elements(const std::string& xpath)
    {
        std::vector<Node*> nodes = find_nodes(xpath);
        std::vector<Element*> elements(nodes.size());
        std::transform(nodes.begin(), nodes.end(), elements.begin(), cast_node_to_element);        
        return elements;
    }

//------------------------------------------------------------------------------
    std::vector<const Element*> Element::find_elements(const std::string& xpath) const
    {
        std::vector<Element*> elements = const_cast<Element*>(this)->find_elements(xpath);
        return std::vector<const Element*>(elements.begin(), elements.end());             
    }
}

