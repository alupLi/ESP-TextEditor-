#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <vector>
#include "Command.h"

class UndoManager {
private:
    std::vector<Command*> undoStack;

public:
    ~UndoManager();
    void executeCommand(Command* cmd);
    void undo();
    bool canUndo() const;
};

#endif