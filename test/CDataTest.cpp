//
// Copyright (c) 2008-2012 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights to use, 
// copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
// Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// 

#include <string>
#include <stdexcept>
#include <UnitTest++/UnitTest++.h>

#include "Document.h"
#include "Element.h"
#include "CData.h"

// NOTE: Nodes can not live w/o their Document.

SUITE(CDataTest)
{
//------------------------------------------------------------------------------
    TEST(cdata_get_content)
    {
        xml::Document doc;
                
        std::string xml = 
            "<?xml version=\"1.0\"?>\n"
            "<test><![CDATA[This is a test.]]></test>\n";
            
        doc.read_from_string(xml);
        
        xml::Element* element = doc.get_root_element();
        CHECK(element != NULL);
        
        std::vector<xml::Node*> children = element->get_children();
        CHECK_EQUAL(1, children.size());        
        xml::CData* c_data = dynamic_cast<xml::CData*>(children.at(0));
        CHECK(c_data != NULL);
        CHECK_EQUAL("This is a test.", c_data->get_content());        
    }
    
//------------------------------------------------------------------------------
    TEST(cdata_element_get_text)
    {
        xml::Document doc;
                
        std::string xml = 
            "<?xml version=\"1.0\"?>\n"
            "<test><![CDATA[This is a test.]]></test>\n";
            
        doc.read_from_string(xml);
        
        xml::Element* element = doc.get_root_element();
        CHECK(element != NULL);
                
        CHECK_EQUAL("This is a test.", element->get_text());        
    }
    
//------------------------------------------------------------------------------
    TEST(cdata_behaves_like_text_in_xpath)
    {
        xml::Document doc;
                
        std::string xml = 
            "<?xml version=\"1.0\"?>\n"
            "<test><![CDATA[This is a test.]]></test>\n";
            
        doc.read_from_string(xml);
        std::string text = doc.query_string("/test/text()");
        CHECK_EQUAL("This is a test.", text);
    }
}    