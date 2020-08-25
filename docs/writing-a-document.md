
# Writing a Document

If you are creating a document you need to do this through the methods of the 
Document and Node classes. This comes from the fact that libxml2 can only create 
the nodes in a linked state. 

As an example we want to create a small HTML document:

    <?xml version="1.0"?>
    <html>
      <head>
        <title>This is a test HTML.</title>
        <link rel="stylesheet" type="text/css" href="style.css"/>
      </head>
      <body>
        <h1>This is a test HTML</h1>
        <p>This is a test for <em>libxmlmm</em>. It aimes to see if a HTML document 
        can be created with the interface.</p>
      </body>
    </html>

The code do this is the following:

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

The code is fairly straight forward. You create a document; in this case we simply 
create it on the stack. This has the advantage that we don't have to bother about it being deleted. The same is with all child objects, they are managed by their parents and as a result by the document. The important bit to remember is that **a node will be deleted once the document is deleted.** So if you happen to pass node pointers around, you need to ensure that your document lives longer than the context in which the pointer is used.

The root node is created through `create_root_element`. As you should know, in 
XML you can only have one root node. If one already exists, the method will throw 
an exception. To get a already created root node, simply use `get_root_node`.

The following code is a repetition of 'add_element'. This will append a new 
element as a child to the node.

To set the inner text simply use 'set_text'. If you need to interchange text and 
elements you want to use `add_text`, this will add a single text node.

Attributes are simple to set and this is done by using `set_attribute`.

Finally you need to write the document to somewhere. To write the document to 
file use:

    doc.write_to_file("index.html");

If you want to write it to a stream you have two options, you can use the 
stream operator:

    std::ostream& os = ...;
    os << doc;

or the method `write_to_stream`:

    std::ostream& os = ...;
    doc.write_to_stream(os);

Basically that is all whats to writing a document with libxmlmm.
