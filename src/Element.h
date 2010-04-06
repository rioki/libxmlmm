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

#pragma once

#include <string>
#include <sstream>

#include "Node.h"
#include "Text.h"

namespace xml
{
    /**
     * XML Element Wrapper
     **/    
    class LIBXMLMM_EXPORT Element : public Node
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
         *         
         * This method will retrive an attribute.
         *
         * @param id the attribtue id
         * @return the attribute value
         *
         * @throws std::logic_error if the attibute does not exist on this 
         * element.
         **/
        std::string get_attribute(const std::string& key) const;
        
        /**
         * Get a given attribute in given type.
         *
         * This method will retrive an attribute and try to convert it
         * to the given type with the help of stream operators.
         *
         * @param id the attribtue id
         * @return the attribute value
         *
         * @throws std::logic_error if the attibute does not exist on this 
         * element.
         *
         * @todo add check if conversion to value worked
         **/
        template <typename T>
        T get_attribute(const std::string& id) const
        {
            std::stringstream conv(get_attribute(id));
            
            T value;
            conv >> value;
            
            return value;
        }
        
        /**
         * Set an attribute.
         **/
        void set_attribute(const std::string& id, const std::string& value);
               
        /**
         * Set an attribute with generic type.
         **/
        template <typename T>
        void set_attribute(const std::string& id, T value)
        {
            std::stringstream conv;
            conv << value;
            set_attribute(id, conv.str());
        }
        
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
        
        /**
         * Get all children of this element.
         *
         * @return All children of this element. 
         **/
        std::vector<const Node*> get_children() const;
        
        /**
         * Find a given element.
         *
         * @param xpath the xpath relative to this element
         * @return the element found
         *
         * @{
         **/
        Element* find_element(const std::string& xpath);
        const Element* find_element(const std::string& xpath) const;
        /** @} **/
        
        /**
         * Find a given set of elements.
         *
         * @param xpath the xpath relative to this element
         * @return the elements found
         *
         * @{
         **/
        std::vector<Element*> find_elements(const std::string& xpath);
        std::vector<const Element*> find_elements(const std::string& xpath) const;
        /** @} **/  
        
    private:             
        
    };    
}
