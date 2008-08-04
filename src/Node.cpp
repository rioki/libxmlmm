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

#include "Node.h"

#include <cassert>
#include <stdexcept>

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
}

