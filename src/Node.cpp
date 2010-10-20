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

#include "utils.h"
#include "exceptions.h"
#include "Element.h"
#include "Content.h"

namespace xml
{
//------------------------------------------------------------------------------
    Node::Node(xmlNode* const co)
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
    std::string Node::get_path() const
    {
        xmlChar* const path = xmlGetNodePath(cobj);
        if (path == NULL)
        {
            // WTF: How is this suposed to happen?
            throw exception("Node::get_path(): failed to allocated path");
        }
            
        std::string value(reinterpret_cast<const char*>(path));
        xmlFree(path);
        return value;
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
            throw exception("no parent");
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
        return this->find<Node*>(xpath);
    }
    
//------------------------------------------------------------------------------
    const Node* Node::find_node(const std::string& xpath) const
    {
        return this->find<const Node*>(xpath);
    }
    
//------------------------------------------------------------------------------
    std::vector<Node*> Node::find_nodes(const std::string& xpath)
    {
        return this->find_all<Node*>(xpath);
    }
    
//------------------------------------------------------------------------------
    std::vector<const Node*> Node::find_nodes(const std::string& xpath) const
    {
        return this->find_all<const Node*>(xpath);
    }

//------------------------------------------------------------------------------    
    std::string Node::query_string(const std::string& xpath) const
    {
        find_nodeset search(cobj, xpath);
        const xmlXPathObject* const result = search;
        
        std::string value;
        if (result->type == XPATH_STRING)
        {
            value = reinterpret_cast<const char*>(result->stringval);                            
        }
        else if (result->type == XPATH_NUMBER)
        {
            value = to_string(result->floatval);                            
        }
        else if (result->type == XPATH_NODESET)
        {
            xmlNodeSet* const nodeset = result->nodesetval;
            if (nodeset)
            {
                // Concatenate all the text from all the text nodes we
                // have.  NOTE: we technically shouldn't have to do this
                // since all adjacent text nodes are supposed to merge to
                // a single node, but that doesn't always happen in
                // libxml2.  Most notably, when CDATA nodes are adjacent
                // to other text nodes. 
                for (int i = 0; i != nodeset->nodeNr; i++)
                {
                    const Node* const node = reinterpret_cast<const Node*>(nodeset->nodeTab[i]->_private);
                    value.append(node->get_value());
                }
            }
        }
        
        return value;
    }
    
//------------------------------------------------------------------------------    
    double Node::query_number(const std::string& xpath) const
    {
        find_nodeset search(cobj, xpath);
        const xmlXPathObject *const result = search;
        
        double value;
        if (result->type == XPATH_NUMBER)
        {
            value = result->floatval;                            
        }
        else if (result->type == XPATH_STRING)
        {
            value = from_string<double>(reinterpret_cast<const char*>(result->stringval));
        }
        else if (result->type == XPATH_NODESET)
        {
            xmlNodeSet* const nodeset = result->nodesetval;
            std::vector<Node*> nodes;
            if (! xmlXPathNodeSetIsEmpty(nodeset))
            {
                const Node* const node = reinterpret_cast<const Node*>(nodeset->nodeTab[0]->_private);
                value = from_string<double>(node->get_value());
            }
        }
        
        return value;
    }
                

//------------------------------------------------------------------------------

    Node::find_nodeset::find_nodeset(xmlNode *const cobj,
                                     const std::string &xpath,
                                     const xmlXPathObjectType type)
    {
        ctxt = xmlXPathNewContext(cobj->doc);
        ctxt->node = cobj;

        result = xmlXPathEval(reinterpret_cast<const xmlChar*>(xpath.c_str()), ctxt);
        if (!result)
        {
        xmlXPathFreeContext(ctxt);
            throw InvalidXPath(xpath);
        }
                
        if (type != XPATH_UNDEFINED && result->type != type)
        {
            xmlXPathFreeObject(result);
            xmlXPathFreeContext(ctxt);
            throw exception("Unsuported query.");
        }
    }

//------------------------------------------------------------------------------

    Node::find_nodeset::~find_nodeset()
    {
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(ctxt);
}

//------------------------------------------------------------------------------

}
