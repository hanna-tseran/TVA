## Tagged Video Archive
Service creating tagged database of videos which allows to:
 - upload a video
 - add tags to a video, tags added by different users get summed. Tags list looks like: tag1(amount), ..., tagN(amount)
 - get a list of videos using tags, list is sorted by the amount of tags
  
*Same in Russian*

Сервис преследует цель создания качественно тэгированной базы видео, для этого он позволяет:
 - загрузить видео
 - ставить видео тэги, при этом тэги, поставленные разными пользователями суммируются. Т.е. сисок тэгов для видео имеет вид: тэг1 (количество), ..., тэгN (количество)
 - получать список видео по тэгам, отсортированный по их суммарному количеству

###API *(Using REST API)*

####Json responces types

**TAG**
```
{
    "name": "name",
    "count": "count"
}
```

**LIST OF TAGS**
```
[
  TAG_0,
  TAG_1,
  ...,
  TAG_N
]
```

**VIDEO**
```
{    
  "name": "name", //can be used as uri
  "tags": LIST OF TAGS
}
```

**LIST OF VIDEOS**
```
[
  VIDEO_0,
  VIDEO_1,
  ...,
  VIDEO_N
]
```

**VIDEO ID**
```
{    
  "_id": "id"
}
```

####Requests

**Get the list of all videos**
```
GET /videos
json responce: LIST OF VIDEOS
```

**Add video**
```
POST /videos
data: source=source_path&tags=tag1,tag2,...,tagn
json responce: VIDEO ID
```

**Add new video tags**
```
PUT /videos/video_id/tags
data: tags=tag1,tag2,...,tagn
responce: only http status code
```

**Delete video**
```
DELETE /videos/video_id
responce: only http status code
```

**Get video tags**
```
GET /videos/video_id/tags
json responce: LIST OF TAGS
```

**Get video**
```
GET /videos/video_id
json responce: VIDEO
```

**Get the list of all videos with tags**
```
GET /tags?tags=tag1,tag2,...,tagn
json responce: LIST OF VIDEOS
```
