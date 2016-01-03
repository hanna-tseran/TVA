#include <iostream>
#include <string>
#include "fcgio.h"
#include "mongo/client/dbclient.h"

#include "tva.h"

using namespace std;

enum RequestType {
    LIST_VIDEOS,
    ADD_VIDEO,
    ADD_VIDEO_TAGS,
    GET_VIDEO_TAGS,
    GET_VIDEO,
    GET_VIDEOS_WITH_TAGS,
    NO_REQUEST
};

RequestType GetRequestType(string path, string method) {
    if (!path.compare("/videos")) {
        if (!method.compare("GET")) {
            return LIST_VIDEOS;
        } else if (!method.compare("POST")){
            return ADD_VIDEO;
        }
    }
    if (path.find("/videos") != string::npos) {
        if (path.find("/tags") != string::npos) {
            if (!method.compare("GET")){
                return GET_VIDEO_TAGS;
            } else if (!method.compare("POST")){
                return ADD_VIDEO_TAGS;
            }
        } else if (!method.compare("GET")){
            return GET_VIDEO;
        }
    }
    if (!path.compare("/tags") && !method.compare("GET")) {
        return GET_VIDEOS_WITH_TAGS;
    }
    return NO_REQUEST;
}

string RemoveQuery(string uri) {
    return uri.find('?') != string::npos ? uri.erase(uri.find('?'), uri.size() - 1) : uri;
}

// string get_request_content(const FCGX_Request & request) {
//     char * content_length_str = FCGX_GetParam("CONTENT_LENGTH", request.envp);
//     unsigned long content_length = STDIN_MAX;

//     if (content_length_str) {
//         content_length = strtol(content_length_str, &content_length_str, 10);
//         if (*content_length_str) {
//             cerr << "Can't Parse 'CONTENT_LENGTH='"
//                  << FCGX_GetParam("CONTENT_LENGTH", request.envp)
//                  << "'. Consuming stdin up to " << STDIN_MAX << endl;
//         }

//         if (content_length > STDIN_MAX) {
//             content_length = STDIN_MAX;
//         }
//     } else {
//         // Do not read from stdin if CONTENT_LENGTH is missing
//         content_length = 0;
//     }

//     char * content_buffer = new char[content_length];
//     cin.read(content_buffer, content_length);
//     content_length = cin.gcount();

//     // Chew up any remaining stdin - this shouldn't be necessary
//     // but is because mod_fastcgi doesn't handle it correctly.

//     // ignore() doesn't set the eof bit in some versions of glibc++
//     // so use gcount() instead of eof()...
//     do cin.ignore(1024); while (cin.gcount() == 1024);

//     string content(content_buffer, content_length);
//     delete [] content_buffer;
//     return content;
// }

int InitMongo() {
    mongo::client::initialize();
    try {
        mongo::DBClientConnection c;
        c.connect("localhost");
        cout << "connected ok" << endl;
    } catch( const mongo::DBException &e ) {
        cout << "caught " << e.what() << endl;
    }
    return EXIT_SUCCESS;
}

int main() {
    int mRes = InitMongo();
    if (mRes)
        return mRes;

    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    int counter = 0;

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        string uri = FCGX_GetParam("REQUEST_URI", request.envp);
        string method = FCGX_GetParam("REQUEST_METHOD", request.envp);
        string query = FCGX_GetParam("QUERY_STRING", request.envp);

        RequestType type = GetRequestType(RemoveQuery(uri), method);

        switch(type) {
            case ADD_VIDEO:
                cout << TaggedVideoArchive::AddVideo();
                break;
            case ADD_VIDEO_TAGS:
                cout << TaggedVideoArchive::AddVideoTags();
                break;
            case GET_VIDEO:
                cout << TaggedVideoArchive::GetVideo();
                break;
            case GET_VIDEO_TAGS:
                cout << TaggedVideoArchive::GetVideoTags();
                break;
            case GET_VIDEOS_WITH_TAGS:
                cout << TaggedVideoArchive::GetVideosWithTags();
                break;
            case LIST_VIDEOS:
                cout << TaggedVideoArchive::ListVideos();
                break;
            case NO_REQUEST:
                cout << "Content-type: text/html\r\n"
                 << "\r\n"
                 << "<html>\n"
                 << "  <head>\n"
                 << "    <title>Hello, World!</title>\n"
                 << "  </head>\n"
                 << "  <body>\n"
                 << "    <h1>Hello, World!</h1>\n"
                 << "    current counter = " << ++counter << "<p>\n"
                 << "    requested URL = " << uri << "<p>\n"
                 << "    requested METHOD = " << method << "<p>\n"
                 << "    requested QUERY = " << query << "<p>\n"
                 << "    requested without QUERY = " << RemoveQuery(uri) << "<p>\n"
                 << "    requested PATH_INFO = " << FCGX_GetParam("PATH_INFO", request.envp) << "<p>\n"
                 << "  </body>\n"
                 << "</html>\n";
                 break;
        }
    }

    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}
