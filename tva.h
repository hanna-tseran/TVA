#include <iostream>
#include <string.h>
using namespace std;


class TaggedVideoArchive {
public:
	static string AddVideo();
	static string AddVideoTags();
	static string GetVideo();
	static string GetVideoTags();
	static string GetVideosWithTags();
	static string ListVideos();
};
