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
#include "Element.h"

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
}

