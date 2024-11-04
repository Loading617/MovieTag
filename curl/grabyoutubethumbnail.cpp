#include "grab YouTube Thumbnail to tag video"

#include <iostream>
#include <string>
#include <curl/curl.h>

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string GrabYouTubeThumbnailFromURL(const std::string& videoUrl) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return "";
    }