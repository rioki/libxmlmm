
# Reading a Document

When reading a XML document with libxmlmm there are two options. You can either 
navigate the document by querying each element for it's children or you can 
use XPATH queries into the document.

For this example we have the following simple XML:

    <?xml version='1.0'?>
    <message version="1.2">
      <from>Mack</from>
      <to>Joe</to>
      <to>Sally</to>
      <to>Mike</to>
      <body>Hello everybody!</body>
    </message>

It is our goal to get all recipients; the names that are in the `to` elements.

## Navigating the Document

To navigate the document you basically use 'get_children' all the time.

    xml::Document doc;
    doc.read_from_file("message.xml");

    xml::Element* message = doc.get_root_node();
    assert(message != NULL);
    assert(message->get_name() == "message");
    assert(message->get_attribute("version") == "1.2");

    std::vector<xml::Node*> children = root->get_children();
    std::vector<std::string> recipients;
    for (unsigned int i; i < children.size(); i++)
    {
        xml::Element* element = dynamic_cast<xml::Element*>(children[i]);
        if (element != NULL && element->get_name() == "to")
        {
            recipients.push_back(element->get_text());
        }
    }

Basically you create a document; in this case we simply create it on the stack. 
This has the advantage that we don't have to bother about it being deleted. The 
same is with all child objects, they are managed by their parents and as a 
result by the document. The important bit to remember is that **a node will be 
deleted once the document is deleted.** So if you happen to pass node pointers 
around, you need to ensure that your document lives longer than the context in 
which the pointer is used.

After creating the document you can read it from file with `read_from_file`. 
Alternately you can also read it from any stream with `read_from_stream`.

The first thing you need to do is get the root element. This is simply done by 
calling 'get_root_element'. In this case we get an Element object. In the case 
here we check if the root node really is a message element and the attribute 
'version' is 1.2.

To access the children of the root element, you call 'get_children'. Here you 
get a vector of `Node` object. These can be anything from `Element`, `TextNode` 
to `CDataNode`. In contrast to other DOM implementations you do not get 
attributes as Node object. They can only be accessed though `get_attribute` and 
friends. To check the type of node, you need to use `dynamic_cast`. In this case 
we are looking for nodes of type `Element` that are "to". 

As a simplification, the inner text of an element can be accessed though 
`get_text`. It would also be possible to call `get_children` and cast the 
resulting `Node` to `TextNode` and call `get_value` on it.

## XPath

libxmlmm features the ability to use XPath to access values in a document. 
To access single values you can use `query_string` and `query_number` and to 
access nodes you can use `find_node` for one node and `find_nodes` for multiple 
nodes. As a shortcut you may also use `find_element` and `find_elements` if 
you are sure that the result of your query are only elements.

    xml::Document doc;
    doc.read_from_file("message.xml");
    
    assert("1.2" == doc.query_string("/message/@version"));

    double recipients_count = doc.query_number("count(/message/to)");
    std::vector<std::string> recipients(static_cast<size_t>(recipients_count));
    
    std::vector<xml::Element*> to_elements doc.find_elements("/message/to");
    assert(recipients_count == to_elements.size());
    for (unsigned int i; i < to_elements.size(); i++)
    {
        recipients.push_back(to_elements[i]->get_text());
    }

This approach starts like the other with creating and reading a document. 

First we check the version by calling `query_string`. The important thing to 
remember is that when the XPath query fails it will throw a `InvalidXPath` 
exception, so by simply calling `query_string`, it is ensured that there is a 
root element named 'message' and it has an attribute names 'version'. 

The next thing we do is demonstrate `query_number`. The clever programmer will 
notice that we can also get the value from `to_elements.size()` and that is 
probably 100 times faster. Nevertheless `query_number` will return a double 
containing the number of 'to' elements. 'query_number' is especially useful for 
XPath queries that do not return nodes, such as the XPath function `count`.

Finally we query all 'to' elements with `query_elements`. This can also be done 
with `query_nodes` and the code would look like the enumeration example. This 
shows why this method is so useful, it make much cleaner code in those cases 
where you are accessing only elements; and experience shows that when working 
with XML you will probably query 80% of the time for elements.

## Conclusion

Which approach you take depends on your use case. Basically the XPath approach 
is simpler, but will probably be slower, since the XPath must be evaluated. It 
is up to you to gauge the tradeoff between speed and simplicity. 
