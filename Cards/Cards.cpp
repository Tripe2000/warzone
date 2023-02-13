#include "Cards.h"
#include <random>

using namespace std;
/// <summary>
/// Card Class implementation
/// </summary>
Deck Card::deck;

Card::Card() {
	cardType = EMPTY;
	handR = NULL;
	deckR = NULL;
}

Card::Card(ctype type) {
	cardType = type;
	handR = NULL;
	deckR = NULL;
}

Card::Card(ctype type, Hand* hand, Deck* deck) {
	cardType = type;
	this->handR = hand;
	this->deckR = deck;
}

Card::Card(const Card& card) {
	cardType = card.cardType;
	handR = card.handR;
	deckR = card.deckR;
}

Card::~Card() {}

Card::ctype Card::getCardType() {
	return cardType;
}

void Card::setDeck(Deck* deck) {
	this->deckR = deck;
}

void Card::setHand(Hand* hand) {
	this->handR = hand;
}

//Plays the card at index i in hand, then returns it to bottom of deck
void Card::play(int i) {
	if (handR != NULL) {
		handR->removeCard(i);
		deckR->addCard(this);
	}
}

void createRandomCards(Deck* deck, Hand* hand, int amount) {
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> dist(0, 4);
	for (int i = 0; i < amount; i++) {
		Card* card = new Card((Card::ctype)(dist(rng)), hand, deck);
		deck->addCard(card);
		if (hand) {
			hand->addCard(card);
		}
	}
}

ostream& operator << (ostream& out, const Card& c) {
	switch (c.cardType)
	{
	case Card::ctype::bomb:
		out << "Card type: Bomb.";
		break;
	case Card::ctype::reinforcement:
		out << "Card type: Reinforcement.";
		break;
	case Card::ctype::airlift:
		out << "Card type: Airlift.";
		break;
	case Card::ctype::blockade:
		out << "Card type: Blockade.";
		break;
	case Card::ctype::diplomacy:
		out << "Card type: Diplomacy";
		break;
  default:
    out << "Wrong choice of options";
	}
	return out;
}

/// <summary>
/// Hand class implementation
/// </summary>

Hand::Hand() {

}

Hand::Hand(const Hand& hand) {
	cards = hand.cards;
}

vector<Card*> Hand::getCards() {
	return cards;
}

int Hand::size() {
	return cards.size();
}

void Hand::removeCard(int i) {
	cards[i]->setHand(NULL);
	cards.erase(cards.begin()+i);
}

void Hand::addCard(Card* card) {
	cards.push_back(card);
	card->setHand(this);
}

ostream& operator << (ostream& out, const Hand& h) {
	out << "Hand size: " << h.cards.size() << "." << endl;
	out << "Cards in hand: " << endl;
	for (int i = 0; i < h.cards.size(); i++) {
		out << "Card " << i << "=" << *(h.cards[i]) << endl;
	}
	return out;
}

/// <summary>
/// Deck class implementation
/// </summary>
Deck::Deck() {
}

Deck::Deck(const Deck &deck) {
	cards = deck.cards;
}

Deck::~Deck() {
	for (Card* c: cards) delete c;
}

int Deck::size() {
	return cards.size();
}

vector<Card*> Deck::getCards() {
	return cards;
}

void Deck::removeCard(int i) {
	if (cards.size() == 0) {
		cout << "Deck is empty" << endl;
		return;
	}
	cards.erase(cards.begin() + i);
}

void Deck::addCard(Card* card) {
	cards.push_back(card);
	card->setDeck(this);
}

//Deck is a pile of card, and drawn card will be the top of the pile.
void Deck::draw(Hand* hand) {
	Card* drawnCard = new Card(*cards.front());
	this->removeCard(0);
	hand->addCard(drawnCard);
}

ostream& operator << (ostream& out, const Deck& d) {
	out << "Deck size: " << d.cards.size() << "." << endl;
	out << "Cards in deck: " << endl;
	for (int i = 0; i < d.cards.size(); i++) {
		out << "Card " << i << "=" << *(d.cards[i]) << endl;
	}
	return out;
}
