#include "Editor.h"
#include <iostream>
#include <fstream>

using namespace std;

bool Editor::loadFile(const string& path) {
    filepath = path;
    lines.clear();

    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return true;
}

bool Editor::saveFile() {
    ofstream file(filepath);
    if (!file.is_open()) return false;

    for (const auto& line : lines) {
        file << line << '\n';
    }
    file.close();
    return true;
}

void Editor::display() const {
    cout << "\n=================================================\n";
    cout << "|                  FILE CONTENT                 |\n";
    cout << "=================================================\n";
    if (lines.empty()) {
        cout << "| [EMPTY FILE]                                 |\n";
    }
    else {
        for (size_t i = 0; i < lines.size(); i++) {
            cout << i + 1 << " | " << lines[i] << '\n';
        }
    }
    cout << "=================================================\n";
}

void Editor::editLine(int lineNum, const string& newText) {
    if (lineNum >= 1 && lineNum <= (int)lines.size()) {
        lines[lineNum - 1] = newText;
    }
}

void Editor::addLine(const string& newLine) {
    lines.push_back(newLine);
}

int Editor::getLineCount() const {
    return lines.size();
}

string Editor::getLine(int index) const {
    if (index >= 0 && index < (int)lines.size()) {
        return lines[index];
    }
    return "";
}

bool Editor::isLoaded() const {
    return !lines.empty() || true;
}

void Editor::createNewFile(const string& path) {
    filepath = path;
    lines.clear();
    ofstream create(path);
    create.close();
}