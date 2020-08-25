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
#include "rtest.h"

#include <libxmlmm/Document.h>
#include <libxmlmm/exceptions.h>

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
    TEST(get_root_node_throws_on_no_root_element)
    {
        xml::Document doc;
        CHECK_THROW(doc.get_root_element(), xml::NoRootElement);
    }

//------------------------------------------------------------------------------
    TEST(constness)
    {
        const std::string xml =
            "<?xml version=\"1.0\"?>\n" \
            "<test/>\n";
        const xml::Document doc(xml);
        CHECK(doc.has_root_element());
        CHECK(doc.get_root_element() != NULL);
        CHECK_EQUAL(xml, doc.write_to_string());
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
            "<?xml version=\"1.0\"?>\n"
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

        const std::string xml(xmat.str());
        const xml::Document check(xml);

        xml::Document doc;
        doc.read_from_stream(xmat);
        // We assume our earlier testing of write_to_string is valid
        CHECK_EQUAL(doc.write_to_string(), check.write_to_string());
    }

//------------------------------------------------------------------------------
    TEST(xpath_string_query)
    {
        std::stringstream xmsg(
            "<?xml version='1.0'?>\n"
            "<message version=\"1.2\">\n"
            "    <from>Mack</from>\n"
            "    <to>Joe</to>\n"
            "    <to>Sally</to>\n"
            "    <to>Mike</to>\n"
            "    <body>Hello everybody!</body>\n"
            "</message>\n");

        xml::Document doc;
        doc.read_from_stream(xmsg);

        std::string body = doc.query_string("/message/body");
        CHECK_EQUAL("Hello everybody!", body);
        std::string body_text = doc.query_string("/message/body/text()");
        CHECK_EQUAL("Hello everybody!", body_text);
        double to_count = doc.query_number("count(/message/to)");
        CHECK_CLOSE(3.0, to_count, 1e-4);

        std::string message_version_string = doc.query_string("/message/@version");
        CHECK_EQUAL("1.2", message_version_string);
        double message_version_number = doc.query_number("/message/@version");
        CHECK_CLOSE(1.2, message_version_number, 1e-4);
    }

//------------------------------------------------------------------------------
    TEST(xpath_get_elements)
    {
        std::stringstream xmsg(
            "<?xml version='1.0'?>\n"
            "<message version=\"1.2\">\n"
            "    <from>Mack</from>\n"
            "    <to>Joe</to>\n"
            "    <to>Sally</to>\n"
            "    <to>Mike</to>\n"
            "    <body>Hello everybody!</body>\n"
            "</message>\n");

        xml::Document doc;
        doc.read_from_stream(xmsg);

        std::vector<xml::Node*> to_nodes = doc.find_nodes("/message/to");
        CHECK_EQUAL(3, to_nodes.size());

        std::vector<xml::Element*> to_elements = doc.find_elements("/message/to");
        CHECK_EQUAL(3, to_elements.size());

        CHECK_EQUAL("Joe", to_elements[0]->get_text());
        CHECK_EQUAL("Sally", to_elements[1]->get_text());
        CHECK_EQUAL("Mike", to_elements[2]->get_text());
    }

//------------------------------------------------------------------------------
    TEST(xpath_get_element)
    {
        std::stringstream xmsg(
            "<?xml version='1.0'?>\n"
            "<message version=\"1.2\">\n"
            "    <from>Mack</from>\n"
            "    <to>Joe</to>\n"
            "    <to>Sally</to>\n"
            "    <to>Mike</to>\n"
            "    <body>Hello everybody!</body>\n"
            "</message>\n");

        xml::Document doc;
        doc.read_from_stream(xmsg);

        xml::Node* from_node = doc.find_node("/message/from");
        CHECK(from_node != NULL);

        xml::Element* from_element = doc.find_element("/message/from");
        CHECK(from_element != NULL);

        CHECK_EQUAL("Mack", from_element->get_text());
    }

//------------------------------------------------------------------------------
    TEST(writes_latin1)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");

        std::stringstream buff;
        // NOTE: This implicitly tests write_to_string too.
        doc.write_to_stream(buff, "ISO-8859-1");

        std::string ref =
          "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
          "<test/>\n";
        CHECK_EQUAL(ref, buff.str());
    }

//------------------------------------------------------------------------------
    TEST(writes_latin1_to_file)
    {
        xml::Document doc;
        xml::Element* root = doc.create_root_element("test");

        std::stringstream buff;
        // NOTE: This implicitly tests write_to_string too.
        doc.write_to_stream(buff, "ISO-8859-1");

        std::string ref =
          "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
          "<test/>\n";
        CHECK_EQUAL(ref, buff.str());
    }
}

