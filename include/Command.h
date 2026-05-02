#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class EditLineCommand : public Command {
private:
    std::vector<std::string>* content;
    std::string oldLine;
    std::string newLine;
    int index;

public:
    EditLineCommand(std::vector<std::string>* cont, int idx, const std::string& oldT, const std::string& newT);
    void execute() override;
    void undo() override;
};

class AddLineCommand : public Command {
private:
    std::vector<std::string>* content;
    std::string line;
    int index;

public:
    AddLineCommand(std::vector<std::string>* cont, const std::string& newLine, int pos);
    void execute() override;
    void undo() override;
};

#endif