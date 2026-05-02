#include "UndoManager.h"

UndoManager::~UndoManager() {
    for (auto cmd : undoStack) delete cmd;
}

void UndoManager::executeCommand(Command* cmd) {
    cmd->execute();
    undoStack.push_back(cmd);
}

void UndoManager::undo() {
    if (!undoStack.empty()) {
        Command* cmd = undoStack.back();
        cmd->undo();
        undoStack.pop_back();
        delete cmd;
    }
}

bool UndoManager::canUndo() const {
    return !undoStack.empty();
}