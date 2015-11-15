API for Tagged Video Archive project
Using REST API

// json responces types

// VIDEO
{    
    "name": "name",
    "tags": ["tag1", "tag2", ..., "tagn"],
    // if we have enough time to implement
    "url": "url"
}

// LIST OF VIDEOS
[ 
    // exactly the same as VIDEO above
    {
        "name": "name",
        "tags": ["tag1", "tag2", ..., "tagn"],
        "url": "url"
    },
    ...,
    {
        "name": "name",
        "tags": ["tag1", "tag2", ..., "tagn"],
        "url": "url"
    }
]

// LIST OF TAGS
[
    "tag1",
    "tag2",
    ...,
    "tagn"
]

//////////////////////////////////////////////////////////////////////////////////////////////////////

// get the list of all videos
GET /videos
json responce: LIST OF VIDEOS

// add video
POST /videos?source=source_path&tags=tag1,tag2,...,tagn
only http status code

// get the list of all tags
GET /tags
json responce: LIST OF TAGS

// modify video tags
PUT /videos/video_id/tags
only http status code

// get video tags
GET /videos/video_id/tags
json responce: LIST OF TAGS

// get video
GET /videos/video_id
json responce: VIDEO

// delete video
DELETE /videos/video_id
only http status code

// get the list of all videos that have the selected tag
GET /tags/tag_name
json responce: LIST OF VIDEOS

// get the list of the most popular tags (number is specified)
GET /top_tags?n=n
json responce: LIST OF TAGS
