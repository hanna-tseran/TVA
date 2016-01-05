#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "mongo/client/dbclient.h"

using namespace std;


class TaggedVideoArchive {
private:
	const string DB_VIDEOS_NAMESPACE;

	mongo::DBClientConnection dbCnctn;

public:
	TaggedVideoArchive();
	int InitDB();
	string AddVideo(string name, vector<string> tags);
	string AddVideoTags(string id, vector<string> tags);
	string GetVideo(string id);
	string GetVideoTags(string id);
	string GetVideosWithTags();
	string ListVideos();
};
