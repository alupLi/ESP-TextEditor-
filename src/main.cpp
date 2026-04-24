#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\n=================================================\n";
    cout << "|                 TEXT EDITOR                   |\n";
    cout << "|           Intermediate version                |\n";
    cout << "=================================================\n";
    cout << "|                                                |\n";
    cout << "|   [1] Open file                               |\n";
    cout << "|   [2] Exit                                    |\n";
    cout << "|                                                |\n";
    cout << "=================================================\n";
    cout << "Choose action: ";
}

string readFileContent(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        return "[ERROR] Cannot open file. Check path.";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void showFileContent(const string& filepath) {
    string content = readFileContent(filepath);

    cout << "\n=================================================\n";
    cout << "| FILE CONTENT: " << filepath;
    for (int i = filepath.length(); i < 33; i++) cout << " ";
    cout << "|\n";
    cout << "=================================================\n\n";

    if (content.empty()) {
        cout << "[File is empty]\n";
    }
    else {
        cout << content << "\n";
    }

    cout << "\n=================================================\n";
    cout << "Press Enter to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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
            showFileContent(filepath);
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