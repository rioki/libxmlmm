//
// libxmlmmm
// Copyright 2008 - 2011 Sean Farell
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
#include <vector>
#include <libxml/tree.h>
#include <libxml/xpath.h>

#include "defines.h"

namespace xml
{
    class Element;

    /**
     * XML DOM Node
     *
     * The Node class is the base class for all DOM elements (except Document). 
     * It is effectively a wrapper for xmlNode.
     **/    
    class LIBXMLMM_EXPORT Node
    {
    protected:
        /**
         * Construct Wrapper
         *
         * @param cobj The xmlNode object to wrap.
         **/
        explicit Node(xmlNode* const cobj);
        
    public:
        /**
         * Destructor
         **/
        virtual ~Node();       
        
        /**
         * Get the node's path
         **/
        std::string get_path() const;

        /**
         * Get the node's parent.
         *
         * @return The node's parent.
         *
         * @throw exception If the node has no parent node.
         *
         * @note It is safe to assume that all nodes have a parent. If this
         * is not the case something is really broken.
         **/
        Element* get_parent(); 
        
        /**
         * Get the node's parent.
         *
         * @return The node's parent.
         *
         * @throw exception If the node has no parent node, exception is
         * raised.
         *
         * @note It is safe to assume that all nodes have a parent. If this
         * is not the case something is really broken.
         **/
        const Element* get_parent() const;  
        
        /**
         * Find a given node.
         *
         * @param xpath the xpath relative to this node
         * @return the node found
         *
         * @{
         **/
        Node* find_node(const std::string& xpath);
        const Node* find_node(const std::string& xpath) const;
        /** @} **/
        
        /**
         * Find a set of nodes.
         *
         * @param xpath the xpath relative to this node
         * @return the nodes found
         *
         * @{
         **/
        std::vector<Node*> find_nodes(const std::string& xpath);
        std::vector<const Node*> find_nodes(const std::string& xpath) const;
        /** @} **/
        
        /**
         * Query a value.
         *
         * @param xpath the xpath
         * @return the value
         *
         * @{
         **/
        std::string query_string(const std::string& xpath) const;
        double query_number(const std::string& xpath) const;
        /** @} **/
    
        /**
         * Get the value of this node.  Empty if not found.
         **/
        virtual std::string get_value() const = 0;

    protected:    
        /** The wrapped xmlNode object. **/
        xmlNode* cobj;
    
        // Helper object to keep our xpath search context.
        struct find_nodeset 
        {
            find_nodeset(xmlNode *const cobj,
                         const std::string &xpath,
                         const xmlXPathObjectType type = XPATH_UNDEFINED);
            ~find_nodeset();

            operator xmlXPathObject *()
            { return result; }

            operator xmlNodeSet *()
            { return result->nodesetval; }

        private:
            xmlXPathContext* ctxt;
            xmlXPathObject* result;
        };

        template <typename NodeType_>
        NodeType_ find(const std::string &xpath) const {
            find_nodeset search(cobj, xpath, XPATH_NODESET);
            xmlNodeSet *const nodeset = search;
            if (!nodeset || nodeset->nodeNr == 0)
            {
                return NULL;
            }
            return reinterpret_cast<NodeType_>(nodeset->nodeTab[0]->_private);
        }

        template <typename NodeType_>
        std::vector<NodeType_> find_all(const std::string &xpath) const {
            find_nodeset search(cobj, xpath, XPATH_NODESET);
            xmlNodeSet *const nodeset = search;
            std::vector<NodeType_> nodes;
            if (nodeset != NULL)
            {
                for (int i = 0; i != nodeset->nodeNr; i++)
                {
                    nodes.push_back(reinterpret_cast<NodeType_>(nodeset->nodeTab[i]->_private));
                }
            }
            return nodes;
        }

    private:
        Node(const Node&);
        Node& operator = (const Node&);

    };    
}
