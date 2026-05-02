#include <iostream>
#include <limits>
#include <fstream>
#include "Editor.h"
#include "UndoManager.h"
#include "Command.h"

using namespace std;

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

void editMode(Editor& editor, UndoManager& undoManager) {
    bool editing = true;

    while (editing) {
        editor.display();
        cout << "\n[1] Edit line    [2] Add line    [3] Save & Exit\n";
        cout << "[4] Exit w/o save [u] Undo\n";
        cout << "Choose: ";

        string input;
        cin >> input;

        if (input == "1") {
            int lineNum;
            cout << "Line number to edit: ";
            cin >> lineNum;
            cin.ignore();

            if (lineNum >= 1 && lineNum <= editor.getLineCount()) {
                string newText;
                cout << "New text: ";
                getline(cin, newText);

                string oldText = editor.getLine(lineNum - 1);

                Command* cmd = new EditLineCommand(&editor.getLines(), lineNum - 1, oldText, newText);
                undoManager.executeCommand(cmd);

                cout << "Line edited. Press Enter...";
                cin.get();
            }
            else {
                cout << "\nLine not found. \n";
            }
        }
        else if (input == "2") {
            string newLine;
            cout << "New line text: ";
            cin.ignore();
            getline(cin, newLine);

            Command* cmd = new AddLineCommand(&editor.getLines(), newLine, editor.getLineCount());
            undoManager.executeCommand(cmd);

            cout << "Line added. Press Enter...";
            cin.get();
        }
        else if (input == "3") {
            if (editor.saveFile()) {
                cout << "File saved.\n";
            }
            else {
                cout << "Error saving file.\n";
            }
            editing = false;
        }
        else if (input == "4") {
            cout << "Changes lost.\n";
            editing = false;
        }
        else if (input == "u" || input == "U") {
            if (undoManager.canUndo()) {
                undoManager.undo();
                cout << "Undo performed.\n";
            }
            else {
                cout << "Nothing to undo.\n";
            }
            cout << "Press Enter...";
            cin.get();
        }
    }
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

            Editor editor;
            if (!editor.loadFile(filepath)) {
                cout << "File not found. Create new file? (y/n): ";
                string answer;
                cin >> answer;
                if (answer == "y" || answer == "Y") {
                    editor.createNewFile(filepath);
                }
                else {
                    continue;
                }
            }

            UndoManager undoManager;
            editMode(editor, undoManager);
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