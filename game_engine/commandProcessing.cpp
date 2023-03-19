#include "commandProcessing.h"
#include <iostream>

void Command::saveEffect(std::string& eff) { effect = new std::string(eff); }
Command::Command(std::string cmd) { command = new std::string(cmd); effect = new std::string(""); }
Command::Command(std::string cmd, std::string eff) {
    command = new std::string(cmd);
    effect = new std::string(eff);
}
Command::~Command() {
    delete command;
    delete effect;
    command = NULL;
    effect = NULL;
}
Command::Command(const Command &obj) {
    command = new std::string;
    effect = new std::string;
    *command = *obj.command;
    *effect = *obj.effect;
}
Command& Command::operator =(const Command &obj) {
    command = obj.command;
    effect = obj.effect;
    return *this;
}
std::ostream& operator <<(std::ostream &output, const Command &obj) {
    output << "Command: " << *obj.command << "\nEffect: " << *obj.effect << std::endl;
    return output; 
}

CommandProcessor::CommandProcessor(GameEngine * e) {
    gameEngine = e;
    commandList = new std::list<Command>;
}
std::string CommandProcessor::getCommand() {
    std::string cmd = readCommand();
    saveCommand(cmd);
    return cmd;
}
CommandProcessor::~CommandProcessor() {
    delete gameEngine;
    commandList->clear();
    delete commandList;
    gameEngine = NULL;
    commandList = NULL;
}
CommandProcessor::CommandProcessor(const CommandProcessor &obj) {
    gameEngine = new GameEngine(*obj.gameEngine);
    // Missing list copy code
}
CommandProcessor& CommandProcessor::operator =(const CommandProcessor &obj) {
    gameEngine = obj.gameEngine;
    commandList = obj.commandList;
    return *this;
}
std::ostream& operator <<(std::ostream &output, const CommandProcessor &obj) {
    output << *(obj.gameEngine) << "\nCommands: \n";
    std::list<Command>::iterator it;
    for(it = obj.commandList->begin(); it != obj.commandList->end(); ++it){
        std::cout << *it << "\n-----\n";
    }
    return output; 
}
std::string CommandProcessor::readCommand() {
    std::cout << "Enter command: ";
    std::string cmdString;
    std::cin >> cmdString;
    return cmdString;
}
void CommandProcessor::saveCommand(std::string cmdString) {
    Command * cmd = new Command(cmdString);
    if(!validate(cmd->getCommand())) {
        std::string * effect = new std::string("Invalid effect");
        cmd->saveEffect(*effect);
    }
    commandList->push_back(*cmd);
}
bool CommandProcessor::validate(std::string& command) {
  command = toLower(command);
  int state = gameEngine->getState();

  if(command == "validatemap" && state == MAP_LOADED_STATE) return true;
  else if(command == "gamestart" && state == PLAYERS_ADDED_STATE) return true;
  else if(command == "replay" && state == WIN_STATE) return true;
  else if(command == "quit" && state == WIN_STATE) return true;
  else {
    std::size_t pos = command.find(" ");
    command = command.substr (0, pos);
    if(command == "loadmap" && (state == START_STATE || state == MAP_LOADED_STATE)) return true;
    else if(command == "addplayer" && (state == MAP_VALIDATED_STATE || state == PLAYERS_ADDED_STATE)) return true;
  }

  return false;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete fileLineReader;
    fileLineReader = NULL;
}

std::string FileLineReader::readLineFromFile() {
    std::string lineCommand;
    std::getline(*input, lineCommand); 
    return lineCommand;
}
FileLineReader::~FileLineReader() {
    input->close();
    delete input;
    input = NULL;
}