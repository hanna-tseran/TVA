## Tagged Video Archive
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
    "num": "num"
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
responce: only http status code
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
