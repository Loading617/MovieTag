#include <taglib/fileref.h>
#include <taglib/tag.h>

void readMetadata(const std::string& filename) {
    TagLib::FileRef file(filename.c_str());
    if (!file.isNull() && file.tag()) {
        TagLib::Tag *tag = file.tag();
        std::cout << "Title: " << tag->title().toCString(true) << std::endl;
        std::cout << "Artist: " << tag->artist().toCString(true) << std::endl;
    }
}
