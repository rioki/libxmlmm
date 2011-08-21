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

#include <string>
#include <stdexcept>
#include <UnitTest++/UnitTest++.h>

#include <libxmlmm/Document.h>
#include <libxmlmm/Element.h>
#include <libxmlmm/CData.h>

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