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

#include "Node.h"

#include <cassert>
#include <stdexcept>
#include <libxml/xpath.h>

namespace xml
{
//------------------------------------------------------------------------------
    Node::Node(xmlNode* co)
    : cobj(co)
    {
        assert(cobj != NULL);
    }
    
//------------------------------------------------------------------------------
    Node::~Node() 
    {
        assert(cobj != NULL);
    }
    
//------------------------------------------------------------------------------
    Element* Node::get_parent()
    {
        if (cobj->parent != NULL)
        {
            return reinterpret_cast<Element*>(cobj->parent->_private);
        }
        else
        {
            // Ok, this never happens! 
            // A xmlNode only has no parent if it it is a document node 
            // (not root element) and this is not wraped by Node.
            assert(false && "no parent");
            throw std::logic_error("no parent");
        }
    }
    
//------------------------------------------------------------------------------
    const Element* Node::get_parent() const
    {
        return const_cast<Node*>(this)->get_parent();
    }

//------------------------------------------------------------------------------    
    Node* Node::find_node(const std::string& xpath)
    {
        std::vector<Node*> nodes = find_nodes(xpath);
        if (!nodes.empty())
            return nodes[0];
        else
            return NULL;
        
    }
    
//------------------------------------------------------------------------------
    const Node* Node::find_node(const std::string& xpath) const
    {
        return const_cast<Node*>(this)->find_node(xpath);
    }
    
//------------------------------------------------------------------------------
    std::vector<Node*> Node::find_nodes(const std::string& xpath)
    {
        xmlXPathContext* ctxt = xmlXPathNewContext(cobj->doc);
        ctxt->node = cobj;
        
        xmlXPathObject* result = xmlXPathEval(reinterpret_cast<const xmlChar*>(xpath.c_str()), ctxt);
        if(!result)
        {
            xmlXPathFreeContext(ctxt);
            throw std::runtime_error("Invalid XPath: " + xpath);
        }
        
        if(result->type != XPATH_NODESET)
        {
            xmlXPathFreeObject(result);
            xmlXPathFreeContext(ctxt);

            throw std::runtime_error("Unsuported querry.");
        }
        
        xmlNodeSet* nodeset = result->nodesetval;
        std::vector<Node*> nodes;
        if (nodeset)
        {
            nodes.reserve(nodeset->nodeNr);
            for (int i = 0; i != nodeset->nodeNr; i++)
                nodes.push_back(static_cast<Node*>(nodeset->nodeTab[i]->_private));
        }

        xmlXPathFreeObject(result);
        xmlXPathFreeContext(ctxt);
        
        return nodes;
    }
    
//------------------------------------------------------------------------------
    std::vector<const Node*> Node::find_nodes(const std::string& xpath) const
    {
        std::vector<Node*> nodes = const_cast<Node*>(this)->find_nodes(xpath);
        return std::vector<const Node*>(nodes.begin(), nodes.end());        
    }
}

