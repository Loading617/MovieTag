#ifndef _MovieTag_MovieTag_h
#define _MovieTag_MovieTag_h

#include <CtrlLib/CtrlLib.h>

class MovieTag : public WithMovieTagLayout<TopWindow> {
public:
	MovieTag();
};

private:
    void OnLoadVideo();
    void OnSaveMetadata();
    void OnExtractThumbnail();
    void OnManageSubtitles();
};

#endif
