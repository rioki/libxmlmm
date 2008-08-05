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

#include "String.h"

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <libxml/xmlmemory.h>

namespace xml
{
//------------------------------------------------------------------------------    
    String::String()
    : xstr(xmlCharStrdup("")) 
    {
        assert(xstr != NULL);
    }

//------------------------------------------------------------------------------    
    String::String(const char* cstr)
    : xstr(xmlCharStrdup(cstr))
    {
        assert(xstr != NULL);
    }
    
//------------------------------------------------------------------------------    
    String::String(const xmlChar* str)
    : xstr(xmlStrdup(str))
    {
        assert(xstr != NULL);
    }

//------------------------------------------------------------------------------        
    String::String(const std::string& str)
    : xstr(xmlCharStrdup(str.c_str())) 
    {
        assert(xstr != NULL);
    }
    
//------------------------------------------------------------------------------    
    String::String(const String& orig)
    : xstr(xmlStrdup(orig.xstr))
    {
        assert(xstr != NULL);
    }

//------------------------------------------------------------------------------        
    String::~String()
    {
        xmlFree(xstr);
    }

//------------------------------------------------------------------------------
    String& String::operator == (const String& orig)
    {
        String tmp(orig);
        tmp.swap(*this);
        return *this;
    }

//------------------------------------------------------------------------------    
    size_t String::size() const
    {
        return xmlStrlen(xstr);
    }

//------------------------------------------------------------------------------
    const xmlChar* String::c_str() const 
    {
        return xstr;
    }

//------------------------------------------------------------------------------    
    void String::swap(String& other)
    {
        std::swap(xstr, other.xstr);
    }
        
//------------------------------------------------------------------------------
    bool operator == (const String& a, const String& b)
    {
        return xmlStrEqual(a.c_str(), b.c_str());
    }
    
//------------------------------------------------------------------------------
    bool operator != (const String& a, const String& b)
    {
        return !(a == b);
    }
    
//------------------------------------------------------------------------------
    std::ostream& operator << (std::ostream& os, const String& s)
    {
        os << reinterpret_cast<const char*>(s.c_str());
        return os;
    }
}

