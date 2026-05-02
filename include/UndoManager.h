#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "Command.h"
#include <vector>
#include <memory>

class UndoManager {
private:
    std::vector<std::unique_ptr<Command>> undoStack;
    std::vector<std::unique_ptr<Command>> redoStack;

public:
    void executeCommand(Command* cmd);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;
};

#endif