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

#include <UnitTest++/UnitTest++.h>
#include <libxml/xmlstring.h>
#include <libxml/xmlmemory.h>

#include "String.h"

SUITE(StringTest)
{
//------------------------------------------------------------------------------
    TEST(initialize_from_string_literal)
    {
        xml::String str("This is a test");
        xmlChar* ref = xmlCharStrdup("This is a test");
        CHECK(xmlStrEqual(ref, str.c_str()));
        xmlFree(ref);
    }

//------------------------------------------------------------------------------    
    TEST(default_is_empty_string)
    {
        CHECK_EQUAL(xml::String(""), xml::String());
    }

//------------------------------------------------------------------------------        
    TEST(copy)    
    {
        xml::String orig("test");
        xml::String copy(orig);
        CHECK_EQUAL(orig, copy);
    }

//------------------------------------------------------------------------------            
    TEST(size)
    {
        CHECK_EQUAL(4, xml::String("test").size());
    }
}

