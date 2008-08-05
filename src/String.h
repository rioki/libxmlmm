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

#include <iosfwd>
#include <string>
#include <libxml/xmlstring.h>

namespace xml
{

    /**
     * UTF-8 handling class.
     **/
    class String
    {
    public:
        /**
         * Initialize empty string.
         **/
        String();        
        
        /**
         * Create a string from char array.
         **/
        String(const char* cstr);
        
        /**
         * Create a string from xmlChar array.
         **/
        String(const xmlChar* str);
        
        /**
         * Create a string from standard string.
         **/
        String(const std::string& str);
        
        /**
         * Copy constructor.
         **/
        String(const String& orig);
        
        /**
         * Free the string.
         **/
        ~String();
        
        /**
         * Assignment operator.
         **/
        String& operator == (const String& orig);
        
        /**
         * Get the size of the string.
         **/
        size_t size() const;
        
        /**
         * Get the internal string buffer.
         **/
        const xmlChar* c_str() const; 
        
        /**
         * Swap two strings.
         **/
        void swap(String& other);
    
    private:
        xmlChar* xstr;    
    };

    /**
     * Is equal operator.
     **/
    bool operator == (const String& a, const String& b);
    
    /**
     * Is not equal operator.
     **/
    bool operator != (const String& a, const String& b);
    
    /**
     * Stream output operator.
     **/
    std::ostream& operator << (std::ostream& os, const String& s);
}

