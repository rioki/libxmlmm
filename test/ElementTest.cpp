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
#include "rtest.h"

#include "Document.h"
#include "Element.h"
#include "Comment.h"
#include "exceptions.h"

// NOTE: Elements can not live w/o their Document.

SUITE(ElementTest)
{
//------------------------------------------------------------------------------
    TEST(get_name)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        CHECK_EQUAL("test", root->get_name());
    }

//------------------------------------------------------------------------------
    TEST(set_name)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        root->set_name("root");
        CHECK_EQUAL("root", root->get_name());
    }

//------------------------------------------------------------------------------
    TEST(set_text)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        root->set_text("This is a test");
        CHECK_EQUAL("This is a test", root->get_text());
    }
    
//------------------------------------------------------------------------------
    TEST(add_text)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        root->add_text("This is");
        root->add_text(" a test");
        CHECK_EQUAL("This is a test", root->get_text());
    }
    
//------------------------------------------------------------------------------
    TEST(get_set_attribute)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        root->set_attribute("key", "value");
        CHECK(root->has_attribute("key"));
        CHECK_EQUAL("value", root->get_attribute("key"));
    }
    
//------------------------------------------------------------------------------
    TEST(remove_attribute)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        root->set_attribute("key", "value");
        root->remove_attribute("key");
        
        CHECK(! root->has_attribute("key"));
    }
    
//------------------------------------------------------------------------------
    TEST(add_element)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        xml::Element* element1 = root->add_element("element1");
        CHECK(element1 != NULL);
        CHECK_EQUAL("element1", element1->get_name());
    }
    
//------------------------------------------------------------------------------
    TEST(get_parent)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        xml::Element* element1 = root->add_element("element1");
        CHECK_EQUAL(root, element1->get_parent());       
    }

//------------------------------------------------------------------------------    
    TEST(browse_children)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        xml::Element* element1 = root->add_element("element1");    
        xml::Element* element2 = root->add_element("element2");
        xml::Element* element3 = root->add_element("element3");
        
        std::vector<xml::Node*> children = root->get_children();
        CHECK_EQUAL(3, children.size());
        CHECK_EQUAL(element1, children[0]);
        CHECK_EQUAL(element2, children[1]);
        CHECK_EQUAL(element3, children[2]);
    }
    
//------------------------------------------------------------------------------
    TEST(simple_xpath_querry)
    {
        std::stringstream xmat(
            "<?xml version='1.0'?>\n"
            "<material version='1.0'>\n"
            "    <ambient red='0.2' green='0.0' blue='0.8' />\n"
            "    <diffuse red='0.9' green='0.8' blue='0.9' />\n"
            "    <specular red='1.0' green='0.7' blue='0.7' />\n"
            "    <emissive red='0.6' green='0.3' blue='0.2' />\n"
            "    <shininess value='0.8' />\n"
            "</material>\n");
        
        xml::Document doc;
        doc.read_from_stream(xmat);
        
        xml::Element* xroot = doc.get_root_element();
        CHECK(xroot != NULL);
        
        xml::Element* xambient = xroot->find_element("./ambient");
        CHECK(xambient != NULL);
        CHECK_EQUAL("ambient", xambient->get_name());
    }
    
//------------------------------------------------------------------------------
    TEST(get_attribute_with_type)
    {
        std::stringstream xmsg(
            "<?xml version='1.0'?>\n"
            "<root version=\"1.2\" id=\"1\" />\n");
        
        xml::Document doc;
        doc.read_from_stream(xmsg);
                
        xml::Element* xroot = doc.get_root_element();
        CHECK(xroot != NULL);
        
        CHECK_CLOSE(1.2f, xroot->get_attribute<float>("version"), 1e-4f);
        CHECK_EQUAL(1, xroot->get_attribute<unsigned int>("id"));
        CHECK_EQUAL("1.2", xroot->get_attribute<std::string>("version"));
    }
    
//------------------------------------------------------------------------------
    TEST(get_attribute_with_invalid_type)
    {
        std::stringstream xmsg(
            "<?xml version='1.0'?>\n"
            "<root version=\"foo\" id=\"1\" />\n");
        
        xml::Document doc;
        doc.read_from_stream(xmsg);
                
        xml::Element* xroot = doc.get_root_element();
        CHECK(xroot != NULL);
        
        CHECK_THROW(xroot->get_attribute<float>("version"), xml::Exception);
    }    
    
//------------------------------------------------------------------------------
    TEST(set_attribute_with_type)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        root->set_attribute("key", 8);
        CHECK(root->has_attribute("key"));
        CHECK_EQUAL("8", root->get_attribute("key"));
    }    
}
