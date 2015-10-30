API for Tagged Video Archive project
Using REST API

Urls and methods:
/videos              GET - returns the list of all videos; POST - add video
/tags                GET - returns the list of all tags
/videos/video_id     POST - add tags; POST - remove tags; GET - return video + tags; DELETE - delete video
/tags/tag_name       GET - returns the list of all videos that have the selected tag
/top_tags            GET - returns the list of the most popular tags (count is specified)

Some examples:
POST /videos?source=some_source&tags=cats,fun,stupid+cat
POST /videos/video_id?action=delete&tag=cats
GET /top_tags?n=10
DELETE /videos/video_id  

//////////////////////////////////
/// Service logic (may be implemented for RPC, but wont't be):
/// 
/// list_of_videos GetAllVideos()
/// error_status AddVideo(video, tags)
/// list_of_tags GetAllTags()
/// error_status AddTagsToVideo(video, tags)
/// error_status RemoveTagsFromVideo(video, tags)
/// list_of_tags GetVideoTags(video)
/// error_status RemoveVideo(video)
/// list_of_videos FindVideosByTag(tag)
/// ordered_list_of_tags GetTopTags(n)
//////////////////////////////////

