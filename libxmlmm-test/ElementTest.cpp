//
// Copyright (c) 2008-2020 Sean Farrell
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
#include <gtest/gtest.h>

#include <libxmlmm/Document.h>
#include <libxmlmm/Element.h>
#include <libxmlmm/Comment.h>
#include <libxmlmm/exceptions.h>

// NOTE: Elements can not live w/o their Document.

TEST(ElementTest, get_name)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    EXPECT_EQ("test", root->get_name());
}

TEST(ElementTest, set_name)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    root->set_name("root");
    EXPECT_EQ("root", root->get_name());
}

TEST(ElementTest, set_text)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    root->set_text("This is a test");
    EXPECT_EQ("This is a test", root->get_text());
}

TEST(ElementTest, add_text)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    root->add_text("This is");
    root->add_text(" a test");
    EXPECT_EQ("This is a test", root->get_text());
}

TEST(ElementTest, get_set_attribute)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    root->set_attribute("key", "value");
    EXPECT_TRUE(root->has_attribute("key"));
    EXPECT_EQ("value", root->get_attribute("key"));
}

TEST(ElementTest, remove_attribute)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    root->set_attribute("key", "value");
    root->remove_attribute("key");

    EXPECT_TRUE(! root->has_attribute("key"));
}

TEST(ElementTest, add_element)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    xml::Element* element1 = root->add_element("element1");
    EXPECT_TRUE(element1 != NULL);
    EXPECT_EQ("element1", element1->get_name());
}

TEST(ElementTest, get_parent)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    xml::Element* element1 = root->add_element("element1");
    EXPECT_EQ(root, element1->get_parent());
}

TEST(ElementTest, rowse_children)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    xml::Element* element1 = root->add_element("element1");
    xml::Element* element2 = root->add_element("element2");
    xml::Element* element3 = root->add_element("element3");

    std::vector<xml::Node*> children = root->get_children();
    EXPECT_EQ(3, children.size());
    EXPECT_EQ(element1, children[0]);
    EXPECT_EQ(element2, children[1]);
    EXPECT_EQ(element3, children[2]);
}

TEST(ElementTest, simple_xpath_querry)
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
    EXPECT_TRUE(xroot != NULL);

    xml::Element* xambient = xroot->find_element("./ambient");
    EXPECT_TRUE(xambient != NULL);
    EXPECT_EQ("ambient", xambient->get_name());
}

TEST(ElementTest, get_attribute_with_type)
{
    std::stringstream xmsg(
        "<?xml version='1.0'?>\n"
        "<root version=\"1.2\" id=\"1\" />\n");

    xml::Document doc;
    doc.read_from_stream(xmsg);

    xml::Element* xroot = doc.get_root_element();
    EXPECT_TRUE(xroot != NULL);

    EXPECT_FLOAT_EQ(1.2f, xroot->get_attribute<float>("version"));
    EXPECT_EQ(1, xroot->get_attribute<unsigned int>("id"));
    EXPECT_EQ("1.2", xroot->get_attribute<std::string>("version"));
}

TEST(ElementTest, get_attribute_with_invalid_type)
{
    std::stringstream xmsg(
        "<?xml version='1.0'?>\n"
        "<root version=\"foo\" id=\"1\" />\n");

    xml::Document doc;
    doc.read_from_stream(xmsg);

    xml::Element* xroot = doc.get_root_element();
    EXPECT_TRUE(xroot != NULL);

    EXPECT_THROW(xroot->get_attribute<float>("version"), xml::Exception);
}

TEST(ElementTest, set_attribute_with_type)
{
    xml::Document doc;
    xml::Element* root = doc.create_root_element("test");
    root->set_attribute("key", 8);
    EXPECT_TRUE(root->has_attribute("key"));
    EXPECT_EQ("8", root->get_attribute("key"));
}
