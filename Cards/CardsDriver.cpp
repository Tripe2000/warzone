#include "Cards.h"
#include "Cards.cpp"

int main () {
	Card::ctype bomb = Card::bomb;
	Card::ctype reinforcement = Card::reinforcement;
	Card::ctype blockade = Card::blockade;
	Card::ctype airlift = Card::airlift;
	Card::ctype diplomacy = Card::diplomacy;
	Deck* deck = new Deck();
	Hand* hand1 = new Hand();
	Hand* hand2 = new Hand();
	Card* card = new Card(bomb);
	deck->addCard(card);
	deck->addCard(new Card(bomb));
	deck->addCard(new Card(blockade));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(bomb));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(bomb));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(diplomacy));
	cout << "card type: 0 = bomb, 1 = reinforcement, 2 = blockade, 3 = airlift, 4 = diplomacy" << endl;
	cout << *deck;
	cout << "number of cards in deck: " << deck->size() << endl;
	cout << "number of cards in first hand: " << hand1->size() << endl;
	cout << "number of cards in second hand: " << hand2->size() << endl;

	cout << "hand 1 draws a card" << endl;
	deck->draw(hand1);
	cout << "number of cards in deck: " << deck->size() << endl;
	cout << "number of cards in first hand: " << hand1->size() << endl;
	cout << "number of cards in second hand: " << hand2->size() << endl;

	cout << "hand 1 draws a card" << endl;
	deck->draw(hand1);
	cout << "hand 2 draws a card" << endl;
	deck->draw(hand2);
	cout << "hand 1 draws a card" << endl;
	deck->draw(hand1);
	cout << "number of cards in deck: " << deck->size() << endl;
	cout << "number of cards in first hand: " << hand1->size() << endl;
	cout << "number of cards in second hand: " << hand2->size() << endl;

	cout << endl << "Hand 1: " << endl;
	cout << *hand1;

	cout << "hand 1 plays second card in deck (bomb)" << endl;
	hand1->getCards()[1]->play(1);
	cout << endl << "Hand 1: " << endl;
	cout << *hand1;
	cout << "number of cards in deck: " << deck->size() << endl;

	cout << "hand 1 plays second card in deck (airlift)" << endl;
	hand1->getCards()[1]->play(1);
	cout << endl << "Hand 1: " << endl;
	cout << *hand1;

	cout << endl << "deck: " << endl;
	cout << *deck;
	return 0;
}

