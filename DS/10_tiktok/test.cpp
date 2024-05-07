#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "video.h"
using namespace std;

Video parseJson(const string& json) {
    // Find and extract relevant fields from JSON string
    size_t coverUrlPos = json.find("\"coverMediumUrl\": \"");
    size_t webVideoUrlPos = json.find("\"webVideoUrl\": \"");
    size_t playCountPos = json.find("\"playCount\": ");
    size_t textPos = json.find("\"text\": \"");
    size_t musicNamePos = json.find("\"musicName\": \"");
    size_t musicAuthorPos = json.find("\"musicAuthor\": \"");
    size_t musicIdPos = json.find("\"musicId\": ");

    if (coverUrlPos != string::npos && webVideoUrlPos != string::npos && playCountPos != string::npos &&
        textPos != string::npos && musicNamePos != string::npos && musicAuthorPos != string::npos && musicIdPos != string::npos) {
        // Extract cover URL
        size_t coverUrlStart = coverUrlPos + 19; // length of "\"coverMediumUrl\": \""
        size_t coverUrlEnd = json.find("\",", coverUrlStart);
        string coverUrl = json.substr(coverUrlStart, coverUrlEnd - coverUrlStart);

        // Extract web video URL
        size_t webVideoUrlStart = webVideoUrlPos + 16; // length of "\"webVideoUrl\": \""
        size_t webVideoUrlEnd = json.find("\"", webVideoUrlStart);
        string webVideoUrl = json.substr(webVideoUrlStart, webVideoUrlEnd - webVideoUrlStart);

        // Extract play count (views)
        size_t playCountStart = playCountPos + 12; // length of "\"playCount\": "
        size_t playCountEnd = json.find(",", playCountStart);
        int views = stoi(json.substr(playCountStart, playCountEnd - playCountStart));

        // Extract hashtags
        size_t textStart = textPos + 9; // length of "\"text\": \""
        size_t textEnd = json.find("\"", textStart);
        string text = json.substr(textStart, textEnd - textStart);

        // Extract hashtags from text
        vector<string> hashtags;
        size_t hashtagPos = text.find("#");
        while (hashtagPos != string::npos) {
            size_t spacePos = text.find(" ", hashtagPos);
            hashtags.push_back(text.substr(hashtagPos + 1, spacePos - hashtagPos - 1));
            hashtagPos = text.find("#", spacePos);
        }

        // Extract song title
        size_t musicNameStart = musicNamePos + 14; // length of "\"musicName\": \""
        size_t musicNameEnd = json.find("\",", musicNameStart);
        string songTitle = json.substr(musicNameStart, musicNameEnd - musicNameStart);

        // Extract song artist
        size_t musicAuthorStart = musicAuthorPos + 16; // length of "\"musicAuthor\": \""
        size_t musicAuthorEnd = json.find("\",", musicAuthorStart);
        string songArtist = json.substr(musicAuthorStart, musicAuthorEnd - musicAuthorStart);

        // Extract song ID
        size_t musicIdStart = musicIdPos + 12; // length of "\"musicId\": "
        size_t musicIdEnd = json.find("\"},", musicIdStart);
        string songId = json.substr(musicIdStart, musicIdEnd - musicIdStart);

        // Return Product object
        return Video(coverUrl, webVideoUrl, views, hashtags, songTitle, songArtist, songId);
    } else {
        cerr << "Error: Required fields not found in JSON." << endl;
        // Return an empty/invalid Product object
        return Video("", "", 0, vector<string>(), "", "", "");
    }
}

int main() {
    string json = "{\"id\": \"6971973705173830918\", \"text\": \"Truco para limpiar tu rasuradora #truco #lifehack #rasuradora\", \"createTime\": 1623289129, \"createTimeISO\": \"2021-06-10T01:38:49.000Z\", \"authorMeta\": {\"id\": \"6640997977560334341\", \"name\": \"pongamoslo_a_prueba\", \"nickName\": \"Pong\\u00e1moslo a Prueba\", \"verified\": true, \"signature\": \"Aqu\\u00ed est\\u00e1 todo lo que pongo a prueba\", \"bioLink\": null, \"avatar\": \"https://p16-sign-va.tiktokcdn.com/tos-maliva-avt-0068/33506332eaed8fc4ffba9cb753f4e7bd~c5_720x720.jpeg?x-expires=1700452800&x-signature=mcLKq8eaPYJHjEz3nEeTFPM6gjw%3D\", \"privateAccount\": false, \"following\": 865, \"fans\": 43800000, \"heart\": 1500000000, \"video\": 777, \"digg\": 4560}, \"musicMeta\": {\"musicName\": \"sonido original\", \"musicAuthor\": \"Pong\\u00e1moslo a Prueba\", \"musicOriginal\": true, \"playUrl\": \"https://v19.tiktokcdn-us.com/b708dbfdb280a3231fc0af998c02bb38/655890c1/video/tos/useast5/tos-useast5-v-27dcd7c799-tx/419a0592bb5e40d696cfa7f7641e4772/?a=1233&ch=0&cr=0&dr=0&er=2&cd=0%7C0%7C0%7C0&br=250&bt=125&bti=NDU3ZjAwOg%3D%3D&ft=t5PLr-Inz7THaKYZiyq8Z&mime_type=audio_mpeg&qs=6&rc=aGVkN2c4PDRlNDk8M2g1OkBpM2g6PHRweGVwNjMzNzU8M0AzY2JhNWI2NjIxNjQ2YDEyYSMzcXFvXl5hbi1gLS1kMTZzcw%3D%3D&l=20231118042320D7B2824139323F333970&btag=e00008000&download=true\", \"coverMediumUrl\": \"https://p16-sign-va.tiktokcdn.com/tos-maliva-avt-0068/33506332eaed8fc4ffba9cb753f4e7bd~c5_720x720.jpeg?x-expires=1700452800&x-signature=mcLKq8eaPYJHjEz3nEeTFPM6gjw%3D\", \"musicId\": \"6971973514953886470\"}, \"webVideoUrl\": \"https://www.tiktok.com/@pongamoslo_a_prueba/video/6971973705173830918\", \"videoMeta\": {\"height\": 1024, \"width\": 576, \"duration\": 40, \"coverUrl\": \"https://p16-sign-va.tiktokcdn.com/obj/tos-maliva-p-0068/0deb77f3b0d7478790e44badf2685edd_1623289130?x-expires=1700452800&x-signature=b9QsjuVtxrqBX4qj%2Bo1WX6uYnTc%3D\", \"definition\": \"540p\", \"format\": \"mp4\", \"downloadAddr\": \"https://v16-webapp-prime.us.tiktok.com/video/tos/useast2a/tos-useast2a-ve-0068c004/8bb675f1ae584f7dbed9a54ee728c91f/?a=1988&ch=0&cr=3&dr=0&lr=tiktok_m&cd=0%7C0%7C1%7C3&cv=1&br=2548&bt=1274&bti=NDU3ZjAwOg%3D%3D&cs=0&ds=3&ft=_rKBMBnZq8ZmoD6IKQ_vjINnsAhLrus&mime_type=video_mp4&qs=0&rc=NjM7ODRkNWk8NjlkN2doPEBpajVmO2dtODRwNjMzNzczM0AwLjJfNGNeXy4xMV4yYjIvYSNuZGkxZjEwbi1gLS1kMTZzcw%3D%3D&btag=e00008000&expire=1700454241&l=20231118042320D7B2824139323F333970&ply_type=2&policy=2&signature=761def397383281ac8a9950b0b0c8772&tk=tt_chain_token\"}, \"diggCount\": 1600000, \"shareCount\": 9719, \"playCount\": 13700000, \"commentCount\": 2537, \"mentions\": []}";

    Video product = parseJson(json);

    cout << "Cover URL: " << product.getCoverUrl() << endl;
    cout << "Web Video URL: " << product.getWebVideoUrl() << endl;
    cout << "Views: " << product.getViews() << endl;
    cout << "Hashtags:";
    for (const auto& tag : product.getHashtags()) {
        cout << " #" << tag;
    }
    cout << endl;
    cout << "Song Title: " << product.getSongTitle() << endl;
    cout << "Song Artist: " << product.getSongArtist() << endl;
    cout << "Song ID: " << product.getSongId() << endl;

    return 0;
}
