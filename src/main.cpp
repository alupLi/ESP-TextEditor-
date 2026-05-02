#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

// ==================== COMMAND PATTERN ====================

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class InsertLineCommand : public Command {
private:
    vector<string>* content;
    string line;
    int index;
    bool executed;

public:
    InsertLineCommand(vector<string>* cont, const string& newLine, int pos)
        : content(cont), line(newLine), index(pos), executed(false) {
    }

    void execute() override {
        content->insert(content->begin() + index, line);
        executed = true;
    }

    void undo() override {
        if (executed && index >= 0 && index < content->size()) {
            content->erase(content->begin() + index);
        }
    }
};

class UndoManager {
private:
    vector<Command*> undoStack;

public:
    ~UndoManager() {
        for (auto cmd : undoStack) delete cmd;
    }

    void executeCommand(Command* cmd) {
        cmd->execute();
        undoStack.push_back(cmd);
    }

    void undo() {
        if (!undoStack.empty()) {
            Command* cmd = undoStack.back();
            cmd->undo();
            undoStack.pop_back();
            delete cmd;
        }
    }

    bool canUndo() const {
        return !undoStack.empty();
    }
};

// ==================== ФУНКЦИИ РЕДАКТОРА ====================

vector<string> loadFileLines(const string& path) {
    vector<string> lines;
    ifstream file(path);
    if (!file.is_open()) {
        return lines;
    }
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

void saveFileLines(const string& path, const vector<string>& lines) {
    ofstream file(path);
    if (!file.is_open()) return;
    for (const auto& line : lines) {
        file << line << '\n';
    }
    file.close();
}

void displayContent(const vector<string>& lines) {
    cout << "\n=================================================\n";
    cout << "|                  FILE CONTENT                 |\n";
    cout << "=================================================\n";
    for (size_t i = 0; i < lines.size(); i++) {
        cout << i + 1 << " | " << lines[i] << '\n';
    }
    if (lines.empty()) {
        cout << "| [EMPTY FILE]                                 |\n";
    }
    cout << "=================================================\n";
}

void editMode(const string& filepath) {
    vector<string> lines = loadFileLines(filepath);
    UndoManager undoManager;
    bool editing = true;

    while (editing) {
        displayContent(lines);
        cout << "\n[1] Edit line    [2] Add line    [3] Save & Exit\n";
        cout << "[4] Exit w/o save [u] Undo\n";
        cout << "Choose: ";

        string input;
        cin >> input;

        if (input == "1") {  // Edit line
            int lineNum;
            cout << "Line number to edit: ";
            cin >> lineNum;
            cin.ignore();

            if (lineNum >= 1 && lineNum <= lines.size()) {
                string newText;
                cout << "New text: ";
                getline(cin, newText);

                // Сохраняем старую строку для Undo
                string oldLine = lines[lineNum - 1];
                lines[lineNum - 1] = newText;

                // Команда для отмены
                Command* cmd = new InsertLineCommand(&lines, oldLine, lineNum - 1);
                undoManager.executeCommand(cmd);
                // Замену сделали, команду используем для отмены
                cout << "Line edited. Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
        }
        else if (input == "2") {  // Add line
            string newLine;
            cout << "New line text: ";
            cin.ignore();
            getline(cin, newLine);

            Command* cmd = new InsertLineCommand(&lines, newLine, lines.size());
            undoManager.executeCommand(cmd);

            cout << "Line added. Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (input == "3") {  // Save & Exit
            saveFileLines(filepath, lines);
            cout << "File saved.\n";
            editing = false;
        }
        else if (input == "4") {  // Exit w/o save
            cout << "Changes lost.\n";
            editing = false;
        }
        else if (input == "u" || input == "U") {  // Undo
            if (undoManager.canUndo()) {
                undoManager.undo();
                cout << "Undo performed.\n";
            }
            else {
                cout << "Nothing to undo.\n";
            }
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

// ==================== MAIN ====================

void showMenu() {
    cout << "\n=================================================\n";
    cout << "|                 TEXT EDITOR                   |\n";
    cout << "|           Intermediate version                |\n";
    cout << "=================================================\n";
    cout << "|                                                |\n";
    cout << "|   [1] Open and edit file                      |\n";
    cout << "|   [2] Exit                                    |\n";
    cout << "|                                                |\n";
    cout << "=================================================\n";
    cout << "Choose action: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1) {
            string filepath;
            cout << "\nEnter file path: ";
            cin.ignore();
            getline(cin, filepath);

            ifstream test(filepath);
            if (!test.is_open()) {
                cout << "File not found. Create new file? (y/n): ";
                string answer;
                cin >> answer;
                if (answer == "y" || answer == "Y") {
                    ofstream create(filepath);
                    create.close();
                    cout << "New file created.\n";
                }
                else {
                    continue;
                }
            }
            test.close();

            editMode(filepath);
        }
        else if (choice == 2) {
            cout << "\nGoodbye!\n";
            break;
        }
        else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}