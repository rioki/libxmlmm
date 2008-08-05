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

#include "Element.h"

#include <cassert>

namespace xml
{
//------------------------------------------------------------------------------
    Element::Element(xmlNode* cobj)
    : Node(cobj) {}
    
//------------------------------------------------------------------------------    
    String Element::get_name() const
    {
        assert(cobj != NULL);
        if (cobj->name != NULL)
        {
            return cobj->name;
        }
        else
        {
            return "";
        }
    }

//------------------------------------------------------------------------------        
    void Element::set_name(const String& value)
    {
        xmlNodeSetName(cobj, value.c_str());
    }
    
//------------------------------------------------------------------------------
    bool Element::has_attribute(const String& key) const
    {
        return xmlGetProp(cobj, key.c_str()) != NULL;
    }
    
//------------------------------------------------------------------------------
    String Element::get_attribute(const String& key) const
    {
        const xmlChar* value = xmlGetProp(cobj, key.c_str());
        if (value != NULL)
        {
            return value;            
        }
        else
        {
            return "";
        }
    }
    
//------------------------------------------------------------------------------
    void Element::set_attribute(const String& key, const String& value)
    {
        xmlSetProp(cobj, (key.c_str()), value.c_str());
    }
    
//------------------------------------------------------------------------------
    void Element::remove_attribute(const String& key)
    {
        xmlUnsetProp(cobj, key.c_str());    
    }

//------------------------------------------------------------------------------
    String Element::get_text() const
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
    void Element::set_text(const String& text)
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
    void Element::add_text(const String& text)
    {
        xmlNode* node = xmlNewText(text.c_str());
        xmlAddChild(cobj, node); 
    }

//------------------------------------------------------------------------------    
    Element* Element::add_element(const String& name)
    {
        xmlNode* node = xmlNewNode(NULL, name.c_str());
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
}
