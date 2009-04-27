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

#pragma once

#include <string>

#include "Node.h"
#include "Text.h"

namespace xml
{
    /**
     * XML Element Wrapper
     **/    
    class Element : public Node
    {
    public: 
        /** 
         * Construct the Wrapper
         **/
        Element(xmlNode* cobj);
        
        /**
         * Get the node's name.
         **/
        std::string get_name() const;
        
        /**
         * Set a node's name.
         **/
        void set_name(const std::string& value);
        
        /**
         * Check if a given attribute exists.
         **/
        bool has_attribute(const std::string& key) const;
        
        /** 
         * Get a given attribute. 
         **/
        std::string get_attribute(const std::string& key) const;
        
        /**
         * Set a attribute.
         **/
        void set_attribute(const std::string& key, const std::string& value);
        
        /**
         * Remove a given attribute.
         **/
        void remove_attribute(const std::string& key);
        
        /**
         * Get the element's text.
         **/
        std::string get_text() const;
        
        /**
         * Get the element's text node.
         **/
        Text* get_text_node() const;
        
        /**
         * Set the 
         **/
        void set_text(const std::string& text);
        
        /**
         * Add/append text to this element.
         **/
        void add_text(const std::string& text);
        
        /**
         * Add a element.
         **/
        Element* add_element(const std::string& name);
        
        /**
         * Get all children of this element.
         *
         * @return All children of this element. 
         **/
        std::vector<Node*> get_children();
        
        std::vector<const Node*> get_children() const;
    };    
}
