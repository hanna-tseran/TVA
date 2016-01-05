#include <iostream>
#include <map>
#include <string>

#include "fcgio.h"
#include "mongo/client/dbclient.h"

#include "tva.h"

using namespace std;


static const string OK_REQUEST = "Status: 200 OK\r\n\r\n";
static const string BAD_REQUEST = "Status: 400 Bad Request\r\n\r\n";
static const string NOT_FOUND = "Status: 404 Not Found\r\n\r\n";
static const string SERVER_ERROR = "Status: 500 Internal Server Error\r\n\r\n";
// static const string OK_REQUEST = "\r\nStatus: 200 OK\r\n";
// static const string BAD_REQUEST = "\r\nStatus: 400 Bad Request\r\n";
// static const string NOT_FOUND = "\r\nStatus: 404 Not Found\r\n";
// static const string SERVER_ERROR = "\r\nStatus: 500 Internal Server Error\r\n";

enum RequestType {
    LIST_VIDEOS,
    ADD_VIDEO,
    ADD_VIDEO_TAGS,
    DELETE_VIDEO,
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
            } else if (!method.compare("PUT")){
                return ADD_VIDEO_TAGS;
            }
        } else if (!method.compare("GET")){
            return GET_VIDEO;
        } else if (!method.compare("DELETE")){
            return DELETE_VIDEO;
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

string GetRequestContent(const FCGX_Request& request) {
    int len = atoi(FCGX_GetParam("CONTENT_LENGTH", request.envp));
    char* buf = new char[len+1];
    cin.read(buf, len);
    buf[len] = '\0';
    string content(buf);
    delete [] buf;
    return content;
}

map<string, string> GetParameters(string query) {
    map<string, string> res;
    std::stringstream ss(query);
    string item;
    while (getline(ss, item, '&')) {
        string key = "";
        string value = "";
        std::stringstream kvss(item);
        if (getline(kvss, key, '=')) {
            getline(kvss, value, '=');
        }
        res.insert(make_pair(key, value));
    }
    return res;
}

vector<string> SplitTags(string tags) {
    vector<string> tagsVec;
    std::stringstream ss(tags);
    string tag;
    while (getline(ss, tag, ',')) {
        tagsVec.push_back(tag);
    }
    return tagsVec;
}

vector<string> SplitPath(string path) {
    vector<string> res;
    std::stringstream ss(path);
    string item;
    while (getline(ss, item, '/')) {
        if (item.size() > 0) {
            res.push_back(item);
        }
    }
    return res;
}

int main() {
    TaggedVideoArchive tva;
    int initRes = tva.InitDB();
    if (initRes) {
        return initRes;
    }

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
        map<string, string> uriParams = GetParameters(query);
        string content = GetRequestContent(request);
        map<string, string> params;
        if (content.size()) {
            params = GetParameters(content);
        }
        string path = RemoveQuery(uri);
        vector<string> splittedPath = SplitPath(path);

        RequestType type = GetRequestType(path, method);

        string videoId;

        cout << "Content-type: application/json charset=UTF-8\r\n";
        string response = "";
        string status = OK_REQUEST;
        switch(type) {
            case ADD_VIDEO:
                response = tva.AddVideo(params["source"], SplitTags(params["tags"]));
                if (response.empty()) {
                    status = SERVER_ERROR;
                }
                break;
            case ADD_VIDEO_TAGS:
                videoId = splittedPath[1];
                response = tva.AddVideoTags(videoId, SplitTags(params["tags"]));
                if (response.empty()) {
                    status = NOT_FOUND;
                }
                break;
            case DELETE_VIDEO:
                videoId = splittedPath[1];
                tva.DeleteVideo(videoId);
                break;
            case GET_VIDEO:
                videoId = splittedPath[1];
                response = tva.GetVideo(videoId);
                if (response.empty()) {
                    status = NOT_FOUND;
                }
                break;
            case GET_VIDEO_TAGS:
                videoId = splittedPath[1];
                response = tva.GetVideoTags(videoId);
                if (response.empty()) {
                    status = NOT_FOUND;
                }
                break;
            case GET_VIDEOS_WITH_TAGS:
                response = tva.GetVideosWithTags(SplitTags(uriParams["tags"]));
                if (response.empty()) {
                    status = NOT_FOUND;
                }
                break;
            case LIST_VIDEOS:
                response = tva.ListVideos();
                if (response.empty()) {
                    status = NOT_FOUND;
                }
                break;
            case NO_REQUEST:
                status = BAD_REQUEST;
                break;
        }
        cout << status;
        if (!response.empty()) {
            cout << response;
        }
    }

    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}
