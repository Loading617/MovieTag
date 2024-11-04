#include "grab YouTube video metadata from YouTube to tag video"

#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string GrabYouTubeVideoMetadata(const std::string& videoId) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return "";
    }