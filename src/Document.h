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

#pragma once

#include <string>
#include <iosfwd>
#include <libxml/tree.h>

#include "LibXmlSentry.h"
#include "Element.h"

namespace xml
{
    /**
     * XML DOM Document
     *
     * This class is the root class for the XML DOM. 
     *
     * @todo Add read and write from file.      
     **/    
    class Document
    {
    public:    
        /** 
         * Default Constructor
         **/
        Document();
        
        /** 
         * Destructor
         **/
        ~Document();
        
        /**
         * Check if the document has a root element.
         *
         * @return true if the document has a root element.
         **/
        bool has_root_element() const;
        
        /**
         * Get the root element.
         *
         * @return The root element.
         *
         * @exception std::logic_error Throws logic_error if the document has
         * no root element.
         **/
        Element* get_root_element();
        
        /**
         * Get the root element.
         *
         * @return The root element.
         *
         * @exception std::logic_error Throws logic_error if the document has
         * no root element.
         **/
        const Element* get_root_element() const;
    
        /**
         * Create the root element of a document.
         *
         * @param name The name of the root node.
         * @return The root element.
         *
         * @exception std::logic_error Throws logic_error if the document 
         * already has a root element.         
         **/
        Element* create_root_element(const String& name);
        
        /**
         * Write document to string.
         **/
        String write_to_string() const;
        
        /**
         * Write document to stream.
         **/
        void write_to_stream(std::ostream& os) const;
        
        /**
         * Read document from string.
         *
         * @todo Add error handling.
         **/
        void read_from_string(const String& xml);
        
        /**
         * Read document from stream.
         *
         * @todo Add error handling.
         **/
        void read_from_stream(std::istream& is);
        
    private:
        xmlDoc* cobj;
        
        LibXmlSentry libxml_sentry;
        
    Document(const Document&);
    Document& operator = (const Document&);
    };   
    
    /** 
     * Stream insert operator.
     **/
    std::ostream& operator << (std::ostream& os, const Document& doc);
    
    /** 
     * Stream extract operator.
     **/
    std::istream& operator >> (std::istream& is, Document& doc);
}

