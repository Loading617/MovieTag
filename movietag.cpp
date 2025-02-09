#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>

void loadMetadata(const std::string& filename, tgui::EditBox::Ptr titleBox, tgui::EditBox::Ptr artistBox) {
    TagLib::FileRef f(filename.c_str());
    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        titleBox->setText(tag->title().toCString(true));
        artistBox->setText(tag->artist().toCString(true));
    } else {
        std::cout << "Failed to load metadata." << std::endl;
    }
}

void saveMetadata(const std::string& filename, const std::string& title, const std::string& artist) {
    TagLib::FileRef f(filename.c_str());
    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        tag->setTitle(title);
        tag->setArtist(artist);
        f.file()->save();
        std::cout << "Metadata saved." << std::endl;
    } else {
        std::cout << "Failed to save metadata." << std::endl;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Video Tag Editor");
    tgui::Gui gui(window);

    
    auto fileBox = tgui::EditBox::create();
    fileBox->setPosition(20, 20);
    fileBox->setSize(400, 30);
    gui.add(fileBox);

    auto browseButton = tgui::Button::create("Browse");
    browseButton->setPosition(430, 20);
    browseButton->setSize(100, 30);
    gui.add(browseButton);

    
    auto titleBox = tgui::EditBox::create();
    titleBox->setPosition(20, 70);
    titleBox->setSize(300, 30);
    gui.add(titleBox);

    auto artistBox = tgui::EditBox::create();
    artistBox->setPosition(20, 120);
    artistBox->setSize(300, 30);
    gui.add(artistBox);

    
    auto saveButton = tgui::Button::create("Save");
    saveButton->setPosition(20, 170);
    saveButton->setSize(100, 40);
    gui.add(saveButton);

    
    browseButton->onPress([&] {
        std::string filename = fileBox->getText().toStdString();
        loadMetadata(filename, titleBox, artistBox);
    });

    saveButton->onPress([&] {
        std::string filename = fileBox->getText().toStdString();
        std::string title = titleBox->getText().toStdString();
        std::string artist = artistBox->getText().toStdString();
        saveMetadata(filename, title, artist);
    });

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            gui.handleEvent(event);
        }
        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}
