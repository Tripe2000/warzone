#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//Super class, all loggable object that inherit ILoggable class must implement stringToLog method
class ILoggable{
    public:
    ILoggable();
    //pure virtual method stringToLog() that write updated state to output file
    virtual string stringToLog() = 0;
    ~ILoggable();
    //copy constructor
    ILoggable(const ILoggable& logObj);
    //assignment operator 
    ILoggable& operator=(const ILoggable& s);
	//stream insertion operator (unused)
	friend ostream& operator<<(ostream& os, const ILoggable& s);
};

class Observer{
    public:
    Observer(); 
    ~Observer();
    //update() method that will call string to lod to update new states into logfile
    //will be define by subclass LogObserver
    virtual void Update(ILoggable* log) = 0;
    //copy constructor
	Observer(const Observer& s);
	//assignment operator
	Observer& operator=(const Observer& s);
	//stream insertion operator
	friend ostream& operator<<(ostream& os, const Observer& s);
};

class Subject{
    public:
    //default constructor
     Subject();
    //attach this class to observer object (add o to mumber of Subject class: list of observers)
    virtual void Attach(Observer* o);
    //detach this class to observer object 
    virtual void Detach(Observer* o);
    //once the notify is called on a loggable object, the update method will be called on every
    //observer objects in observer class, and then invoke stringToLod to write update state into files
    virtual void Notify(ILoggable* log);
    ~Subject();
    //copy constructor
	Subject(const Subject &s);
	//assignment operator
	Subject& operator=(const Subject& s);
	//stream insertion operator
	friend ostream& operator<<(ostream& os, const Subject& s);

    private:
    list<Observer*> *observers;
};

class LogObserver: public Observer{
    public:
    LogObserver();
    //will call stringToLog to output the implementation state code into output file
    void Update(ILoggable* log);
    ~LogObserver();
    //copy constructor
	LogObserver(const LogObserver& s);
	//assignment operator
	LogObserver& operator=(const LogObserver& s);
	//stream insertion operator
	friend ostream& operator<<(ostream& os, const LogObserver& s);

};
