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

#include <string>
#include <stdexcept>
#include <UnitTest++/UnitTest++.h>

#include "Document.h"
#include "Element.h"
#include "Comment.h"

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
    /*TEST(add_comment)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");
        xml::Comment* comment = root->add_comment_node("This is a comment.");
        CHECK_EQUAL("This is a comment.", comment->get_content());
    }*/
}

