#include "MovieTag.h"
#include "MetadataHandler.h"
#include "ThumbExtractor.h"
#include "SubtitleManager.h"

MovieTag::MovieTag() {
    CtrlLayout(*this, "MovieTag");

    loadBtn <<= [=] { OnLoadVideo(); };
    saveBtn <<= [=] { OnSaveMetadata(); };
    thumbBtn <<= [=] { OnExtractThumbnail(); };
    subtitleBtn <<= [=] { OnManageSubtitles(); };
}

void MovieTag::OnLoadVideo() {
    String file = SelectFileOpen("*.mp4;*.mkv;*.avi");
    if (!file.IsEmpty()) {
        MetadataHandler::Load(file, *this);
    }
}

void MovieTag::OnSaveMetadata() {
    MetadataHandler::Save(currentFile, *this);
}

void MovieTag::OnExtractThumbnail() {
    ThumbExtractor::Extract(currentFile, "thumb.jpg");
}

void MovieTag::OnManageSubtitles() {
    SubtitleManager::Open(currentFile);
}
