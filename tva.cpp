#include "mongo/client/dbclient.h"

#include "tva.h"

using mongo::BSONElement;
using mongo::BSONObj;
using mongo::BSONObjBuilder;


string TaggedVideoArchive::AddVideo() {
	// cout << "Content-type:text/html\r\n\r\n";
 //   cout << "<html>\n";
 //   cout << "<head>\n";
 //   cout << "<title>File Upload in CGI</title>\n";
 //   cout << "</head>\n";
 //   cout << "<body>\n";

 //   // get list of files to be uploaded
 //   const_file_iterator file = cgi.getFile("userfile");
 //   if(file != cgi.getFiles().end()) {
 //      // send data type at cout.
 //      cout << HTTPContentHeader(file->getDataType());
 //      // write content at cout.
 //      file->writeToStream(cout);
 //   }
 //   cout << "<File uploaded successfully>\n";
 //   cout << "</body>\n";
 //   cout << "</html>\n";


	string responce;
	responce = "Content-type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "  <head>\n"
        "    <title>Add video</title>\n"
        "  </head>\n"
        "  <body>\n"
        "    <h1>Add video</h1>\n"
         //"    current counter = "++counter"<p>\n"
         //"    requested URL = "uri"<p>\n"
         //"    requested METHOD = "method"\n"
        "  </body>\n"
        "</html>\n";
    return responce;
}

string TaggedVideoArchive::AddVideoTags() {
	string responce;
	responce = "Content-type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "  <head>\n"
        "    <title>Add video tags</title>\n"
        "  </head>\n"
        "  <body>\n"
        "    <h1>Add video tags</h1>\n"
         //"    current counter = "++counter"<p>\n"
         //"    requested URL = "uri"<p>\n"
         //"    requested METHOD = "method"\n"
        "  </body>\n"
        "</html>\n";
    return responce;
}

string TaggedVideoArchive::GetVideo() {
	string responce;
	responce = "Content-type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "  <head>\n"
        "    <title>Get video</title>\n"
        "  </head>\n"
        "  <body>\n"
        "    <h1>Get video</h1>\n"
         //"    current counter = "++counter"<p>\n"
         //"    requested URL = "uri"<p>\n"
         //"    requested METHOD = "method"\n"
        "  </body>\n"
        "</html>\n";
    return responce;
}

string TaggedVideoArchive::GetVideoTags() {
	string responce;
	responce = "Content-type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "  <head>\n"
        "    <title>Get video tags</title>\n"
        "  </head>\n"
        "  <body>\n"
        "    <h1>Get video tags</h1>\n"
         //"    current counter = "++counter"<p>\n"
         //"    requested URL = "uri"<p>\n"
         //"    requested METHOD = "method"\n"
        "  </body>\n"
        "</html>\n";
    return responce;
}

string TaggedVideoArchive::GetVideosWithTags() {
	string responce;
	responce = "Content-type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "  <head>\n"
        "    <title>Get videos with tags</title>\n"
        "  </head>\n"
        "  <body>\n"
        "    <h1>Get videos with tags</h1>\n"
         //"    current counter = "++counter"<p>\n"
         //"    requested URL = "uri"<p>\n"
         //"    requested METHOD = "method"\n"
        "  </body>\n"
        "</html>\n";
    return responce;
}

string TaggedVideoArchive::ListVideos() {
	string responce;
	responce = "Content-type: text/html\r\n"
        "\r\n"
        "<html>\n"
        "  <head>\n"
        "    <title>List of videos!</title>\n"
        "  </head>\n"
        "  <body>\n"
        "    <h1>List of videos!</h1>\n"
         //"    current counter = "++counter"<p>\n"
         //"    requested URL = "uri"<p>\n"
         //"    requested METHOD = "method"\n"
        "  </body>\n"
        "</html>\n";
    return responce;
}
