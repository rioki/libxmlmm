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

#include <string>
#include <stdexcept>
#include <UnitTest++/UnitTest++.h>

#include "Document.h"

SUITE(DocumentTest)
{
//------------------------------------------------------------------------------
    TEST(initial_document_has_no_root_element)
    {
        xml::Document doc;
        CHECK(! doc.has_root_element());
    }

//------------------------------------------------------------------------------
    TEST(create_root_element)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        CHECK(root != NULL);
        CHECK_EQUAL("test", root->get_name());     
    }
    
//------------------------------------------------------------------------------
    TEST(get_root_node_throws_on_no_root_elemet)    
    {
        xml::Document doc;
        CHECK_THROW(doc.get_root_element(), std::logic_error);
    }
    
//------------------------------------------------------------------------------
    TEST(write_to_string)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");       
        
        std::string xml = 
            "<?xml version=\"1.0\"?>\n" \
            "<test/>\n";
        CHECK_EQUAL(xml, doc.write_to_string());
    }
    
//------------------------------------------------------------------------------
    TEST(read_from_string)
    {
        xml::Document doc;
                
        std::string xml = 
            "<?xml version=\"1.0\"?>\n" \
            "<test/>\n";
            
        doc.read_from_string(xml);
        
        xml::Element* root = doc.get_root_element();
        CHECK(root != NULL);
        CHECK_EQUAL("test", root->get_name()); 
    }

//------------------------------------------------------------------------------    
    TEST(build_html)
    {
        xml::Document doc;
        xml::Element* html = doc.create_root_element("html");        
        
        xml::Element* head = html->add_element("head");        
        xml::Element* title = head->add_element("title");
        title->set_text("This is a test HTML.");
        xml::Element* style_link = head->add_element("link");
        style_link->set_attribute("rel", "stylesheet");
        style_link->set_attribute("type", "text/css");
        style_link->set_attribute("href", "style.css");
        
        xml::Element* body = html->add_element("body");
        xml::Element* h1 = body->add_element("h1");
        h1->set_text("This is a test HTML");
        xml::Element* p1 = body->add_element("p");
        p1->add_text("This is a test for ");
        xml::Element* em1 = p1->add_element("em");
        em1->set_text("libxmlmm");
        p1->add_text(". It aimes to see if a HTML document can be created with the interface.");
        
        std::stringstream buff;
        buff << doc;
        
        std::string ref = 
          "<?xml version=\"1.0\"?>\n"
          "<html><head><title>This is a test HTML.</title>"
          "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\"/></head>"
          "<body><h1>This is a test HTML</h1><p>This is a test for <em>libxmlmm</em>."
          " It aimes to see if a HTML document can be created with the interface.</p></body></html>\n";
        CHECK_EQUAL(ref, buff.str());
    }

//------------------------------------------------------------------------------    
    TEST(read_from_stream)
    {
        std::stringstream xmat(
            "<?xml version='1.0'?>\n"
            "<material version='1.0'>\n"
            "    <lighting_mode value='TOON_LIGHTING' />\n"
            "    <width value='1.5' />\n"
            "    <ambient red='0.2' green='0.0' blue='0.8' />\n"
            "    <diffuse red='0.9' green='0.8' blue='0.9' />\n"
            "    <specular red='1.0' green='0.7' blue='0.7' />\n"
            "    <emissive red='0.6' green='0.3' blue='0.2' />\n"
            "    <shininess value='0.8' />\n"
            "    <opacity value='0.7' />\n"
            "</material>\n");
        
        xml::Document doc;
        doc.read_from_stream(xmat);
    }
}

