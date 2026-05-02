#include "Command.h"

using namespace std;

// EditLineCommand
EditLineCommand::EditLineCommand(vector<string>* cont, int idx, const string& oldT, const string& newT)
    : content(cont), index(idx), oldLine(oldT), newLine(newT) {
}

void EditLineCommand::execute() {
    (*content)[index] = newLine;
}

void EditLineCommand::undo() {
    (*content)[index] = oldLine;
}

// AddLineCommand
AddLineCommand::AddLineCommand(vector<string>* cont, const string& newLine, int pos)
    : content(cont), line(newLine), index(pos) {
}

void AddLineCommand::execute() {
    content->insert(content->begin() + index, line);
}

void AddLineCommand::undo() {
    content->erase(content->begin() + index);
}