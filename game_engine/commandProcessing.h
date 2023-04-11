#pragma once
#include "gameEngine.h"
#include <list>
#include <fstream>
#include <iostream>
#include <string>

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
    void saveCommand(std::string);

    protected:
    virtual std::string readCommand();
};

class FileLineReader {
    public:
    FileLineReader(std::string& f) {
        input = new std::ifstream(f);
    };
    std::string readLineFromFile();
    ~FileLineReader();

    private:
    std::ifstream * input;
};

class FileCommandProcessorAdapter: public CommandProcessor {
    public:
    FileCommandProcessorAdapter(GameEngine * ge, FileLineReader * f): CommandProcessor(ge), fileLineReader(f) {};
    std::string readCommand() { std::string str = fileLineReader->readLineFromFile(); std::cout << str << std::endl; return str; };
    ~FileCommandProcessorAdapter();

    private:
    FileLineReader * fileLineReader;
};