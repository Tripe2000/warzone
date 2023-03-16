#pragma once
#include "gameEngine.h"
#include <list>

class Command {
    public:
    void saveEffect(std::string&);
    Command(std::string&);
    Command(std::string, std::string);
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
    void getCommand();
    virtual ~CommandProcessor();
    CommandProcessor(const CommandProcessor &obj);
    CommandProcessor& operator =(const CommandProcessor &obj);
    friend std::ostream& operator <<(std::ostream &output, const CommandProcessor &obj);

    private:
    GameEngine * gameEngine;
    std::list<Command*> * commandList;
    virtual std::string readCommand();
    void saveCommand(std::string);
    bool validate(std::string&);
};

class FileCommandProcessorAdapter: public CommandProcessor {
    public:
    FileCommandProcessorAdapter(FileLineReader * f) { this->fileLineReader = f; };
    std::string readCommand() { fileLineReader->readLineFromFile(); };
    ~FileCommandProcessorAdapter();

    private:
    FileLineReader * fileLineReader;
};

class FileLineReader {
    public:
    FileLineReader(std::string& f) { this->fileName = new std::string(f); };
    std::string& readLineFromFile();
    ~FileLineReader();

    private:
    std::string * fileName;
};