#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>

class Editor {
private:
    std::vector<std::string> lines;
    std::string filepath;

public:
    bool loadFile(const std::string& path);
    bool saveFile();
    void display() const;
    void editLine(int lineNum, const std::string& newText);
    void addLine(const std::string& newLine);
    int getLineCount() const;
    std::string getLine(int index) const;
    bool isLoaded() const;
    void createNewFile(const std::string& path);
    std::vector<std::string>& getLines() { return lines; }
};

#endif