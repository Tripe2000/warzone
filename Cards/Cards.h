#pragma once
#include <vector>
#include <iostream>

using namespace std;
class Card;

class Hand {
public:
	Hand();
	~Hand() {
		delete this;
	}
	Hand(const Hand &hand);
	Hand& operator=(const Hand& other);

	friend ostream& operator << (ostream& out, const Hand& c);

	int size();

	void removeCard(int i);
	void addCard(Card* card);

	vector<Card*> getCards();
private:
	vector<Card*> cards;
};

class Deck {
public:
	Deck();
	~Deck();
	Deck(const Deck &deck);
	//Deck& operator=(const Deck& other);

	friend ostream& operator << (ostream& out, const Deck& c);

	int size();

	void draw(Hand* hand);
	void removeCard(int i);
	void addCard(Card* card);

	vector<Card*> getCards();
	vector<Card*> cards;

private:
	
};

class Card {
public:
	static Deck deck;
	typedef enum{
		bomb = 0,
		reinforcement = 1,
		blockade = 2,
		airlift = 3,
		diplomacy = 4,
		EMPTY
	} ctype;
	Card();
	~Card();
	Card(ctype type);
	Card(ctype type, Hand* hand, Deck* deck);
	Card(const Card& card);
	Card& operator=(const Card& other);
	friend ostream& operator << (ostream& out, const Card& c);

	void play(int i);
	Card::ctype getCardType();

	void setDeck(Deck* deck);
	void setHand(Hand* hand);

private:
	Hand* handR;
	Deck* deckR;
	Card::ctype cardType;
};

void createRandomCards(Deck* deck, Hand* hand, int amount);