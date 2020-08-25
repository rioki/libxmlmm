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

#include "Document.h"

#include <libxml/tree.h>

#include "utils.h"
#include "exceptions.h"

namespace xml
{


    Document::Document()
    : cobj(xmlNewDoc(BAD_CAST "1.0"))
    {
        cobj->_private = this;
    }


    Document::Document(const std::string &xml)
    : cobj(xmlNewDoc(BAD_CAST "1.0"))
    {
        cobj->_private = this;
        this->read_from_string(xml);
    }


    Document::~Document()
    {
        xmlFreeDoc(cobj);
    }


    bool Document::has_root_element() const
    {
        return xmlDocGetRootElement(cobj) != NULL;
    }


    Element* Document::get_root_element()
    {
        xmlNode* root = xmlDocGetRootElement(cobj);
        if (root == NULL)
        {
            throw NoRootElement();
        }
        return reinterpret_cast<Element*>(root->_private);
    }


    const Element* Document::get_root_element() const
    {
        return const_cast<Document*>(this)->get_root_element();
    }


    Element* Document::create_root_element(const std::string& name)
    {
        if (has_root_element())
        {
            throw Exception("xml::Document::create_root_element(): Already has a root element.");
        }

        xmlNode* root = xmlNewDocNode(cobj, NULL, reinterpret_cast<const xmlChar*>(name.c_str()), NULL);
        if (root == NULL)
        {
            throw Exception(get_last_error());
        }

        xmlDocSetRootElement(cobj, root);

        return reinterpret_cast<Element*>(root->_private);
    }


    std::string Document::write_to_string() const
    {
        xmlChar* buffer = 0;
        int length = 0;

        xmlDocDumpMemory(cobj, &buffer, &length);
        if (!buffer)
        {
            throw Exception(get_last_error());
        }
        std::string xml(reinterpret_cast<const char*>(buffer));

        xmlFree(buffer);

        return xml;
    }


    std::string Document::write_to_string(const std::string& encoding) const
    {
        xmlChar* buffer = 0;
        int length = 0;

        xmlDocDumpMemoryEnc(cobj, &buffer, &length, encoding.c_str());
        if (!buffer)
        {
            throw Exception(get_last_error());
        }
        std::string xml(reinterpret_cast<const char*>(buffer));

        xmlFree(buffer);

        return xml;
    }


    void Document::write_to_stream(std::ostream& os) const
    {
        os << write_to_string();
    }


    void Document::write_to_stream(std::ostream& os, const std::string& encoding) const
    {
        os << write_to_string(encoding);
    }


    void Document::write_to_file(const std::string& file) const
    {
        int result = xmlSaveFormatFile(file.c_str(), cobj, 1);
        if (result == -1)
        {
            throw Exception(get_last_error());
        }
    }


    void Document::write_to_file(const std::string& file, const std::string& encoding) const
    {
        int result = xmlSaveFormatFileEnc(file.c_str(), cobj, encoding.c_str(), 1);
        if (result == -1)
        {
            throw Exception(get_last_error());
        }
    }


    void Document::read_from_string(const std::string& xml)
    {
        xmlDoc* tmp_cobj = xmlReadDoc(reinterpret_cast<const xmlChar*>(xml.c_str()), NULL, NULL, 0);
        if (tmp_cobj == NULL)
        {
            throw Exception(get_last_error());
        }
            xmlFreeDoc(cobj);
            cobj = tmp_cobj;
        }


    void Document::read_from_stream(std::istream& is)
    {
        read_from_string(read_until_eof(is));
    }


    void Document::read_from_file(const std::string& file)
    {
        xmlDoc* tmp_cobj = xmlReadFile(file.c_str(), NULL, 0);
        if (tmp_cobj == NULL)
        {
            throw Exception(get_last_error());
        }
        xmlFreeDoc(cobj);
        cobj = tmp_cobj;
    }


    Node* Document::find_node(const std::string& xpath)
    {
        try
        {
            return get_root_element()->find_node(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    const Node* Document::find_node(const std::string& xpath) const
    {
        try
        {
            return get_root_element()->find_node(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    std::vector<Node*> Document::find_nodes(const std::string& xpath)
    {
        try
        {
            return get_root_element()->find_nodes(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    std::vector<const Node*> Document::find_nodes(const std::string& xpath) const
    {
        try
        {
            return get_root_element()->find_nodes(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    Element* Document::find_element(const std::string& xpath)
    {
        try
        {
            return get_root_element()->find_element(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    const Element* Document::find_element(const std::string& xpath) const
    {
        try
        {
            return get_root_element()->find_element(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    std::vector<Element*> Document::find_elements(const std::string& xpath)
    {
        try
        {
            return get_root_element()->find_elements(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    std::vector<const Element*> Document::find_elements(const std::string& xpath) const
    {
        try
        {
            return get_root_element()->find_elements(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    std::string Document::query_string(const std::string& xpath) const
    {
        try
        {
            return get_root_element()->query_string(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    double Document::query_number(const std::string& xpath) const
    {
        try
        {
            return get_root_element()->query_number(xpath);
        }
        catch (const NoRootElement &)
        {
            throw EmptyDocument();
        }
    }


    LIBXMLMM_EXPORT
    std::ostream& operator << (std::ostream& os, const Document& doc)
    {
        doc.write_to_stream(os);
        return os;
    }


    LIBXMLMM_EXPORT
    std::istream& operator >> (std::istream& is, Document& doc)
    {
        doc.read_from_stream(is);
        return is;
    }
}
