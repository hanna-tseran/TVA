#include <stdio.h>
#include <stdlib.h>

#include <json/json.h>

#include "tva.h"

using namespace mongo;


TaggedVideoArchive::TaggedVideoArchive() : DB_VIDEOS_NAMESPACE("tva.videos") {}

int TaggedVideoArchive::InitDB() {
	mongo::client::initialize();
    try {
        dbCnctn.connect("localhost");
        cout << "connected ok" << endl;
    } catch( const mongo::DBException &e ) {
        cout << "caught " << e.what() << endl;
    }
    return EXIT_SUCCESS;
}

string ConvertTagsToString(map<string, int> tags) {
	string tagsStr = "";
	for(map<string, int>::iterator it = tags.begin(); it != tags.end(); ++it) {
		char buf[50];
		sprintf(buf, "%i", it->second);
		tagsStr += it->first + ":" + buf + ";";
	}
	return tagsStr;
}

string ConvertTagsToJson(string tags) {
	Json::Value tagsArray;
    std::stringstream ss(tags);
    string item;
    while (getline(ss, item, ';')) {
    	std::stringstream tagss(item);
    	string name;
    	getline(tagss, name, ':');
    	string count;
    	getline(tagss, count, ':');

    	Json::Value tag;
		tag["name"] = name;
		tag["count"] = count;
		tagsArray.append(tag);
    }

	return tagsArray.toStyledString();
}

Json::Value ConvertTagsToJsonValue(string tags) {
	Json::Value tagsArray;
    std::stringstream ss(tags);
    string item;
    while (getline(ss, item, ';')) {
    	std::stringstream tagss(item);
    	string name;
    	getline(tagss, name, ':');
    	string count;
    	getline(tagss, count, ':');

    	Json::Value tag;
		tag["name"] = name;
		tag["count"] = count;
		tagsArray.append(tag);
    }

	return tagsArray;
}

map<string, int> TagsAsMap(string tags) {
	map<string, int> tagsMap;
	std::stringstream ss(tags);
	string item;
	while (getline(ss, item, ';')) {
		std::stringstream tagss(item);
		string name;
		getline(tagss, name, ':');
		string count;
		getline(tagss, count, ':');
		tagsMap.insert(make_pair(name, atoi(count.c_str())));
	}

	return tagsMap;
}

// string ConvertTagsToJson(map<string, int> tags) {
// 	Json::Value tagsArray;
// 	for(map<string, int>::iterator it = tags.begin(); it != tags.end(); ++it) {
// 		Json::Value tag;
// 		tag["name"] = it->first;
// 		tag["count"] = it->second;
// 		tagsArray.append(tag);
// 	}
// 	return tagsArray.toStyledString();
// }

string TaggedVideoArchive::AddVideo(string name, vector<string> tags) {
	// add counts
	map<string, int> tagsMap;
	for (int i = 0; i < tags.size(); ++i) {
		tagsMap.insert(make_pair(tags[i], 1));
	}

	// insert
	BSONObj video = BSON(GENOID << "name" << name << "tags" << ConvertTagsToString(tagsMap));
	// dbCnctn.remove(DB_VIDEOS_NAMESPACE, MONGO_QUERY("_id" << OID("568af24d3ae0cf035a3c2811")));
	// important, uncomment!!!!
	// dbCnctn.insert(DB_VIDEOS_NAMESPACE, video);

	BSONElement oi;
	video.getObjectID(oi);
	OID oid = oi.__oid();
	Json::Value id;
	id["_id"] = oid.toString();
	return id.toStyledString();
	// return 200;
}

string TaggedVideoArchive::AddVideoTags(string id, vector<string> tags) {
	Json::Reader reader;
	auto_ptr<DBClientCursor> cursor = dbCnctn.query(DB_VIDEOS_NAMESPACE, MONGO_QUERY("_id" << OID(id)));
	if (cursor->more()) {
		BSONObj item = cursor->next();
		map<string, int> tagsMap = TagsAsMap(item.getStringField("tags"));
		for (int i = 0; i < tags.size(); ++i) {
			map<string, int>::iterator it = tagsMap.find(tags[i]);
			if (it != tagsMap.end()) {
				++it->second;
			} else {
				tagsMap.insert(make_pair(tags[i], 1));
			}
		}
		dbCnctn.update(DB_VIDEOS_NAMESPACE, BSON("_id" << OID(id)), BSON("$set" << BSON("tags" << ConvertTagsToString(tagsMap))));
		return ConvertTagsToJson(ConvertTagsToString(tagsMap));
	}
    return "{ video-id: " + id + "}\n";
}

string TaggedVideoArchive::GetVideo(string id) {
	Json::Reader reader;
	auto_ptr<DBClientCursor> cursor = dbCnctn.query(DB_VIDEOS_NAMESPACE, MONGO_QUERY("_id" << OID(id)));
	if (cursor->more()) {
		BSONObj item = cursor->next();
		string tags = item["tags"];
		Json::Value video;
		reader.parse(item.jsonString(), video);
		video["tags"] = ConvertTagsToJsonValue(item.getStringField("tags"));
		return video.toStyledString();
	}
    return "{ video-id: " + id + "}\n";
}

string TaggedVideoArchive::GetVideoTags(string id) {
	Json::Reader reader;
	auto_ptr<DBClientCursor> cursor = dbCnctn.query(DB_VIDEOS_NAMESPACE, MONGO_QUERY("_id" << OID(id)));
	if (cursor->more()) {
		BSONObj item = cursor->next();
		return ConvertTagsToJson(item.getStringField("tags"));
	}
    return "{ video-id: " + id + "}\n";
}

string TaggedVideoArchive::GetVideosWithTags() {
	string response;
	response = "Content-type: text/html\r\n"
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
    return response;
}

string TaggedVideoArchive::ListVideos() {
	Json::Value videoArray;
	Json::Reader reader;

	auto_ptr<DBClientCursor> cursor = dbCnctn.query(DB_VIDEOS_NAMESPACE, BSONObj());
	while (cursor->more()) {
		BSONObj item = cursor->next();
		Json::Value video;
		reader.parse(item.jsonString(), video);
		video["tags"] = ConvertTagsToJsonValue(item.getStringField("tags"));
		videoArray.append(video);
	}

	return videoArray.toStyledString();
}

// string TaggedVideoArchive::ListVideos() {
// 	Json::Value root;
// 	Json::Value videoArray;
// 	Json::Reader reader;
// 	// string response;
// 	// response = "Content-type: text/html\r\n"
//  //        "\r\n"
//  //        "<html>\n"
//  //        "  <head>\n"
//  //        "    <title>Videos list</title>\n"
//  //        "  </head>\n"
//  //        "  <body>\n"
//  //        "    <h1>Videos list</h1>\n";

// 	auto_ptr<DBClientCursor> cursor = dbCnctn.query(DB_VIDEOS_NAMESPACE, BSONObj());
// 	while (cursor->more()) {
// 		BSONObj item = cursor->next();
// 		BSONElement oi;
// 		// item.getObjectID(oi);
// 		// OID oid = oi.__oid();

// 		Json::Value video;
// 		reader.parse(item.jsonString(), video); 
// 		videoArray.append(video);

// 		// response += string("_id: ") + oid.toString() + "; ";
// 		// response += "all info: " + item.jsonString() + "\n";
// 	}

// 	// response += "  </body>\n"
//         // "</html>\n";
//     root["videos"] = videoArray;
//     return videoArray.toStyledString();//root.toStyledString();
// }
