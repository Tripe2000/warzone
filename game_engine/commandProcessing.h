#pragma once
#include "gameEngine.h"
#include <list>
#include <fstream>

class Command {
    public:
    void saveEffect(std::string&);
    Command(std::string);
    Command(std::string, std::string);
    std::string& getCommand() { return *command; };
    std::string& getEffect() { return *effect; };
    ~Command();
    Command(const Command &obj);
    Command& operator =(const Command &obj);
    friend std::ostream& operator <<(std::ostream &output, const Command &obj);

    private:
    std::string * command;
    std::string * effect;
};

class CommandProcessor {
    public:
    CommandProcessor(GameEngine*);
    std::string getCommand();
    virtual ~CommandProcessor();
    CommandProcessor(const CommandProcessor &obj);
    CommandProcessor& operator =(const CommandProcessor &obj);
    friend std::ostream& operator <<(std::ostream &output, const CommandProcessor &obj);
    bool validate(std::string&);

    private:
    GameEngine * gameEngine;
    std::list<Command> * commandList;
    virtual std::string readCommand();
    void saveCommand(std::string);
};

class FileLineReader {
    public:
    FileLineReader(std::string& f) {
        input->open(f);
    };
    std::string readLineFromFile();
    ~FileLineReader();

    private:
    std::ifstream * input;
};

class FileCommandProcessorAdapter: public CommandProcessor {
    public:
    FileCommandProcessorAdapter(GameEngine * ge, FileLineReader * f): CommandProcessor(ge) { this->fileLineReader = f; };
    std::string readCommand() { return fileLineReader->readLineFromFile(); };
    ~FileCommandProcessorAdapter();

    private:
    FileLineReader * fileLineReader;
};