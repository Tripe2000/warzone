#include "PlayerStrategies.h"
#include "../GameEngine/GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include <vector>
#include <algorithm>

class Territory;

// Constant strategy names for subclasses
const string NeutralPlayerStrategy::strategyName = "Neutral";
const string CheaterPlayerStrategy::strategyName = "Cheater";
const string HumanPlayerStrategy::strategyName = "Human";
const string AggressivePlayerStrategy::strategyName = "Aggressive";
const string BenevolentPlayerStrategy::strategyName = "Benevolent";


// *****************************************************************************************************************
// PLAYER STRATEGY (ABSTRACT BASE CLASS)
// *****************************************************************************************************************

// default constructor
PlayerStrategy::PlayerStrategy() {
    this->player = nullptr;
};

// parametized constructor
PlayerStrategy::PlayerStrategy(Player *p) {
    this->player = p;
    player->setStrategy(this);
}

// copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy& ps) {
    this->player = ps.player;
    player->setStrategy(this);
}

PlayerStrategy::~PlayerStrategy() = default;

// assignment operator
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &ps) {
    if (&ps != this) {
        this->player = ps.player;
        player->setStrategy(this);
    }
    return *this;
}

// stream insertion operator
ostream& operator << (ostream& out,  const PlayerStrategy& ps) {
    cout <<  ps.getStrategyName();
    return out;
}

// player getter
Player *PlayerStrategy::getPlayer() {
    return player;
}

// player setter
void PlayerStrategy::setPlayer(Player* p) {
    this->player = p;
}

// *****************************************************************************************************************
// NEUTRAL PLAYER STRATEGY
// *****************************************************************************************************************

//default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy() : PlayerStrategy() {}

// parametized constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) {}

NeutralPlayerStrategy::~NeutralPlayerStrategy() = default;

// Copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &neutralPlayerStrategy) : PlayerStrategy(neutralPlayerStrategy){}

// Assignment operator
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &neutralPlayerStrategy) {
    PlayerStrategy::operator = (neutralPlayerStrategy);
    return *this;
}

// stream insertion operator
ostream& operator << (ostream& out,  const NeutralPlayerStrategy& ps) {
    cout <<  ps.getStrategyName();
    return out;
}

// clone method
NeutralPlayerStrategy* NeutralPlayerStrategy::clone() const {
    return new NeutralPlayerStrategy(*this);
}

// neutral player doesn't issue order
void NeutralPlayerStrategy::issueOrder() {
    cout << *player << " is done issuing orders" << endl;
    this->player->setIsDoneIssuingOrders(true);
}

// does not do anything - neutral player doesn't attack
vector<Territory *> NeutralPlayerStrategy::toAttack() {
    return player->getTerritories();
}

// return sorted list of owned territories from weskest to strongest
vector<Territory *> NeutralPlayerStrategy::toDefend() {
    vector<Territory *> territories = player->getTerritories();
    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs){
        return  (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return territories;
}

// strategy name getter
string NeutralPlayerStrategy::getStrategyName() const {
    return strategyName;
}

// *****************************************************************************************************************
// CHEATER PLAYER STRATEGY
// *****************************************************************************************************************

// default constructor
CheaterPlayerStrategy::CheaterPlayerStrategy() : PlayerStrategy(){}

// parametized constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player) {}

// copy constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &cps) : PlayerStrategy(cps) {}

// destructor
CheaterPlayerStrategy::~CheaterPlayerStrategy() = default;

// assignment operator
CheaterPlayerStrategy &CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy &cps) {
    PlayerStrategy::operator = (cps);
    return *this;
}

// clone method
CheaterPlayerStrategy* CheaterPlayerStrategy::clone() const {
    return new CheaterPlayerStrategy(*this);
}

// stream insertion operator
ostream &operator<<(ostream &os, const CheaterPlayerStrategy &cps) {
    os << cps.getStrategyName();
    return os;
}

// conquers all neighbouring territories
void CheaterPlayerStrategy::issueOrder() {
    vector<Territory*> enemy_adjacent_territories = this->toAttack();
    for (Territory* terr : enemy_adjacent_territories){
        //terr->set_owner(this->player);
        player->conquerTerritory(terr);
    }
    cout << "Cheater " << *player << " conquered every neighbouring territory!" << endl;
    this->player->setIsDoneIssuingOrders(true);
}

// return list of all enemy territories neighbouring player's own
vector<Territory *> CheaterPlayerStrategy::toAttack() {
    vector<Territory *> toAttackTerritories;
    for (Territory *ownedTerritory: player->getTerritories()) { //for each owned territory
        for (Territory *neighborTerritory: ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner() != player) {  //if the current player does not own the neighbor territory
                // check if territory is already in toAttackTerritories
                auto it = find_if(toAttackTerritories.begin(), toAttackTerritories.end(),
                                  [&neighborTerritory](Territory *t) {
                                      return t->get_id() == neighborTerritory->get_id();
                                  });
                if (it == toAttackTerritories.end()) { //if territory is not already in toAttackTerritories add it
                    toAttackTerritories.push_back(neighborTerritory);
                }
            }
        }
    }
    return toAttackTerritories;
}

// cheater does not defend
vector<Territory *> CheaterPlayerStrategy::toDefend() {
    return player->getTerritories();
}

// strategy name getter
string CheaterPlayerStrategy::getStrategyName() const {
    return strategyName;
}

// *****************************************************************************************************************
// HUMAN PLAYER STRATEGY
// *****************************************************************************************************************

//default constructor
HumanPlayerStrategy::HumanPlayerStrategy() : PlayerStrategy() {}

// parametrized constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {}

HumanPlayerStrategy::~HumanPlayerStrategy() = default;

// Copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &humanPlayerStrategy) : PlayerStrategy(humanPlayerStrategy){}

// Assignment operator
HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &humanPlayerStrategy) {
    PlayerStrategy::operator = (humanPlayerStrategy);
    return *this;
}

// stream insertion operator
ostream& operator << (ostream& out,  const HumanPlayerStrategy& ps) {
    cout <<  ps.getStrategyName();
    return out;
}

// clone method
HumanPlayerStrategy* HumanPlayerStrategy::clone() const {
    return new HumanPlayerStrategy(*this);
}

// prompts user for deploy and card orders parameters, then for a choice of attack/defend advance orders or do nothing
void HumanPlayerStrategy::issueOrder() {

    // Deploying
    if(player->getIssuableReinforcementPool() != 0) {

        vector<Territory*> territoriesToDeploy = player->getTerritories();

        cout << "\n==============================================================================================================\n" << endl;

        cout << "To deploy territories: " << endl;

        bool keep_asking = true;
        Territory* targetTerr;
        while(keep_asking) {
            int count = 0;
            for (Territory *t: territoriesToDeploy) {
                cout << count << ": " << *t << endl;
                count++;
            }
            cout << player->getName() << ", please enter a number corresponding to the territory where you wish to deploy armies." << endl;
            int choice;
            cin >> choice;

            if (choice >= territoriesToDeploy.size() or choice < 0) {
                cout << "invalid command, please try again. " << endl;
                continue;
            }

            targetTerr = territoriesToDeploy[choice];
            keep_asking = false;
        }

        int armiesToDeploy = player->getIssuableReinforcementPool();

        keep_asking = true;

        while(keep_asking) {

            cout << "You have " << armiesToDeploy << " armies to deploy. Please enter the number of armies you wish to deploy." << endl;
            int choice;
            cin >> choice;

            if (choice > armiesToDeploy or choice < 1) {
                cout << "Invalid command, please try again. " << endl;
                continue;
            }

            armiesToDeploy = choice;
            keep_asking = false;
        }

        player->getPlayerOrderList()->add(new Deploy(targetTerr, player, armiesToDeploy, player->getGame())); // deploy armies to the weakest territory
        player->setIssuableReinforcementPool(player->getIssuableReinforcementPool() - armiesToDeploy); // decrement player's reinforcement pool
        targetTerr->set_issued_army_units(targetTerr->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units
        cout << "\n==============================================================================================================\n" << endl;
        cout << *player << " issued a new deploy order of " << armiesToDeploy << " armies to " << targetTerr->get_name() << endl;
    }

        // Cards
    else if(!player->getHand()->getCards().empty()) {

        cout << "\n==============================================================================================================\n" << endl;
        int card_index;
        cout << "\nCards available: "<< endl;

        bool keep_asking = true;
        while(keep_asking) {
            int count = 0;
            for(Card* card : player->getHand()->getCards()){
                cout << count << ": " << card->getCardType() << endl;
                count++;
            }
            cout << player->getName() << ", please enter a number corresponding to the card you wish to play." << endl;

            int choice;
            cin >> choice;

            if (choice >= player->getHand()->getCards().size() or choice < 0) {
                cout << "invalid command, please try again. " << endl;
                continue;
            }

            card_index = choice;
            keep_asking = false;
        }
        cout << "\n==============================================================================================================\n" << endl;

        player->getHand()->play(*player->getGame()->getDeck(), player, card_index); // play every card in player's hand
    }

        // Advance
    else if (not this->player->getIsDoneIssuingOrders()) {
        bool isToAttack = false;
        bool doNothing = false;
        bool keep_asking = true;

        map<Territory*, int> availableArmies;
        for(Territory* t: player->getTerritories()){
            // add territories and currently available armies to advance
            availableArmies.insert(pair<Territory*, int> (t, t->get_army_units() + t->get_issued_army_units()));
        }

        while(keep_asking and not this->player->getIsDoneIssuingOrders()){
            int totalAvail = 0;
            for(pair<Territory*, int> t: availableArmies){
                totalAvail += t.second;
            }
            if(totalAvail == 0){
                cout << player->getName() << ", you have no more available armies to advance. " << endl;
                player->setIsDoneIssuingOrders(false);
            }


            // ask option (attack/ defend/ nothing)
            keep_asking = true;
            while(keep_asking) {
                int choice;

                if(player->getTerritories().size() < 2){
                    choice = 0;
                    keep_asking = false;
                    continue;
                }

                cout << "\n==============================================================================================================\n" << endl;

                cout << player->getName() << ", do you wish to attack opponents territories or to Defend your own? Enter <1> for attacking and <-1> for defending. Enter <0> to do nothing" << endl;

                cin >> choice;

                if (choice == -1) {
                    keep_asking = false;
                }
                else if(choice == 1){
                    isToAttack = true;
                    keep_asking = false;
                }
                else if(choice == 0){
                    doNothing = true;
                    keep_asking = false;
                }
                else{
                    cout << "invalid command, please try again. " << endl;
                    continue;
                }
            }

            // Attack
            if (isToAttack){ // issue at most 2 advance attack orders

                // choosing target
                vector<Territory*> possibleTargets = toAttack();
                cout << "To attack territories: " << endl;

                keep_asking = true;
                Territory* targetTerr;
                while(keep_asking) {
                    int count = 0;
                    for (Territory *t: possibleTargets) {
                        cout << count << ": " << *t << endl;
                        count++;
                    }
                    cout << player->getName() << ", please enter a number corresponding to the target territory you wish to attack." << endl;
                    int choice;
                    cin >> choice;

                    if (choice >= possibleTargets.size() or choice < 0) {
                        cout << "invalid command, please try again. " << endl;
                        continue;
                    }

                    targetTerr = possibleTargets[choice];
                    keep_asking = false;
                }

                // Choosing source
                vector<Territory*> targetNeighbours = targetTerr->get_neighbours();
                vector<Territory*> possibleSource;

                for(Territory* t : targetNeighbours){
                    if(t->get_owner() == player){
                        possibleSource.push_back(t);
                    }
                }

                if (possibleSource.empty()) {
                    cout << "You have no territory adjacent to this target territory!" << endl;
                    return;
                }

                cout << "Territories neighbouring the target: " << endl;

                keep_asking = true;
                Territory* sourceTerr;
                while(keep_asking) {
                    int count = 0;
                    for (Territory *t: possibleSource) {
                        cout << count << ": " << *t << "Available army units: " << t->get_army_units() + t->get_issued_army_units() << endl;
                        count++;
                    }
                    cout << player->getName() << ", please enter a number corresponding to the source territory that will attack the target." << endl;
                    int choice;
                    cin >> choice;

                    if (choice >= possibleSource.size() or choice < 0) {
                        cout << "invalid command, please try again. " << endl;
                        continue;
                    }

                    sourceTerr = possibleSource[choice];
                    keep_asking = false;
                }

                int available_units = availableArmies.at(sourceTerr);

                keep_asking = true;
                while(keep_asking) {

                    cout << "You have " << available_units << " armies to advance. Please enter the number of armies you wish to advance." << endl;
                    int choice;
                    cin >> choice;

                    if (choice > available_units or choice < 0) {
                        cout << "Invalid command, please try again. " << endl;
                        continue;
                    }

                    available_units = choice;
                    keep_asking = false;
                }

                player->getPlayerOrderList()->add(new Advance(sourceTerr, targetTerr, player, available_units, player->getGame()));
                availableArmies.at(sourceTerr) =  availableArmies.at(sourceTerr) - available_units;
                player->setAdvanceAttackOrdersIssued(player->getAdvanceAttackOrdersIssued()+1); // increment orders issued

                cout << "\n==============================================================================================================\n" << endl;

                cout << *player << " issued a new advance order from " << sourceTerr->get_name() << " to an enemy territory " << targetTerr->get_name() << endl;
            }

                // Defend
            else if (not isToAttack and not doNothing){
                // choosing target
                vector<Territory*> possibleTargets = toDefend();
                cout << "To defend territories: " << endl;

                keep_asking = true;
                Territory* targetTerr;
                while(keep_asking) {
                    int count = 0;
                    for (Territory *t: possibleTargets) {
                        cout << count << ": " << *t << endl;
                        count++;
                    }
                    cout << player->getName() << ", please enter a number corresponding to the target territory you wish to defend." << endl;
                    int choice;
                    cin >> choice;

                    if (choice >= possibleTargets.size() or choice < 0) {
                        cout << "invalid command, please try again. " << endl;
                        continue;
                    }

                    targetTerr = possibleTargets[choice];
                    keep_asking = false;
                }

                // Choosing source
                vector<Territory*> targetNeighbours = targetTerr->get_neighbours();
                vector<Territory*> possibleSource;

                for(Territory* t : targetNeighbours){
                    if(t->get_owner() == player){
                        possibleSource.push_back(t);
                    }
                }

                if (possibleSource.empty()) {
                    cout << "You have no territory adjacent to this target territory!" << endl;
                    return;
                }


                cout << "Territories neighbouring the target: " << endl;

                keep_asking = true;
                Territory* sourceTerr;
                while(keep_asking) {
                    int count = 0;
                    for (Territory *t: possibleSource) {
                        cout << count << ": " << *t << "Available army units: " << t->get_army_units() + t->get_issued_army_units() << endl;
                        count++;
                    }
                    cout << player->getName() << ", please enter a number corresponding to the source territory that will defend the target." << endl;
                    int choice;
                    cin >> choice;

                    if (choice >= possibleSource.size() or choice < 0) {
                        cout << "invalid command, please try again. " << endl;
                        continue;
                    }

                    sourceTerr = possibleSource[choice];
                    keep_asking = false;
                }

                int available_units = availableArmies.at(sourceTerr);

                keep_asking = true;
                while(keep_asking) {

                    cout << "You have " << available_units << " armies to advance. Please enter the number of armies you wish to advance." << endl;
                    int choice;
                    cin >> choice;

                    if (choice > available_units or choice < 0) {
                        cout << "Invalid command, please try again. " << endl;
                        continue;
                    }

                    available_units = choice;
                    keep_asking = false;
                }

                player->getPlayerOrderList()->add(new Advance(sourceTerr, targetTerr, player, available_units, player->getGame()));
                availableArmies.at(sourceTerr) =  availableArmies.at(sourceTerr) - available_units;
                player->setAdvanceDefendOrdersIssued(player->getAdvanceDefendOrdersIssued()+1); // increment orders issued
                cout << "\n==============================================================================================================\n" << endl;
                cout << *player << " issued a new advance order from " <<  sourceTerr->get_name() << " to their own territory " << targetTerr->get_name() << endl;
            }
            else if(doNothing){
                keep_asking = false;
                cout << "\n==============================================================================================================\n" << endl;
                cout << *player << " is done issuing orders" << endl;
                this->player->setIsDoneIssuingOrders(true);
                cout << "\n==============================================================================================================\n" << endl;
            }
        }

    }

        // Done issuing
    else {
        cout << "\n==============================================================================================================\n" << endl;
        cout << *player << " is done issuing orders" << endl;
        this->player->setIsDoneIssuingOrders(true);
        cout << "\n==============================================================================================================\n" << endl;
    }
}

// returns list of enemy territories neighbouring player's own
vector<Territory *> HumanPlayerStrategy::toAttack() {
    vector<Territory*> toAttackTerritories;
    for (Territory *ownedTerritory : player->getTerritories()){ //for each owned territory
        for (Territory *neighborTerritory : ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner() != player) {  //if the current player does not own the neighbor territory
                // check if territory is already in toAttackTerritories
                auto it = find_if(toAttackTerritories.begin(), toAttackTerritories.end(),
                                  [&neighborTerritory](Territory *t) {
                                      return t->get_id() == neighborTerritory->get_id();
                                  });
                if (it == toAttackTerritories.end()) { //if territory is not already in toAttackTerritories add it
                    toAttackTerritories.push_back(neighborTerritory);
                }
            }
        }
    }
    // sort toAttack territories by # of army units ascending
    sort(toAttackTerritories.begin(), toAttackTerritories.end(), [](Territory *lhs, Territory *rhs){
        return  lhs->get_army_units() < rhs->get_army_units();
    });

    return toAttackTerritories;
}

// return own territories sorted from weakest to strongest
vector<Territory *> HumanPlayerStrategy::toDefend() {
    vector<Territory*> territoriesToDefend = player->getTerritories();

    sort(territoriesToDefend.begin(), territoriesToDefend.end(), [](Territory *lhs, Territory *rhs){
        return  (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return territoriesToDefend;
}

// strategy name getter
string HumanPlayerStrategy::getStrategyName() const {
    return strategyName;
}

// *****************************************************************************************************************
// AGGRESSIVE PLAYER STRATEGY
// *****************************************************************************************************************

// default constructor
AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategy() {
    this->airliftCardIssued = 0;
}

// parametrized constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {
    this->airliftCardIssued = 0;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() = default;

// copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &aps) : PlayerStrategy(aps) {
    this->airliftCardIssued = aps.getAirliftCardIssued();
};

// assignment operator
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &aps) {
    PlayerStrategy::operator = (aps);
    this->airliftCardIssued = aps.getAirliftCardIssued();
    return *this;
}

// clone method
AggressivePlayerStrategy* AggressivePlayerStrategy::clone() const {
    return new AggressivePlayerStrategy(*this);
}

// stream insertion operator
ostream& operator << (ostream& out,  const AggressivePlayerStrategy& aps) {
    cout << aps.getStrategyName();
    return out;
}

// issue order method - either issue 1 deploy order, 1 card order, 1 advance defend, 1 advance attack or no order
void AggressivePlayerStrategy::issueOrder() {
    if (!player->getTerritories().empty()) {
        int issuableReinforcementPool = player->getIssuableReinforcementPool();
        int advanceAttackOrdersIssued = player->getAdvanceAttackOrdersIssued();
        int advanceDefendOrdersIssued = player->getAdvanceDefendOrdersIssued();
        int defendListSize = toDefend().size();
        int attackListSize = toAttack().size();

        // issue deploy order
        if (issuableReinforcementPool != 0) {
            int armiesToDeploy = issuableReinforcementPool;
            Territory *targetTerr;
            // in 1st turn, deploy to territory most surrounded by enemies
            if (player->getGame()->turn == 1) {
                targetTerr = terrMostSurroundedByEnemies();
            }
                // in other turns, deploy to territory with highest armies (actual + issued)
            else {
                targetTerr = this->toDefend().back();
            }
            player->getPlayerOrderList()->add(new Deploy(targetTerr, player, armiesToDeploy,
                                                         player->getGame())); // deploy entire reinforcement pool to the target territory
            player->setIssuableReinforcementPool(
                    player->getIssuableReinforcementPool() - armiesToDeploy); // decrement player's reinforcement pool
            targetTerr->set_issued_army_units(
                    targetTerr->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units
            cout << *player << " issued a new deploy order of " << armiesToDeploy << " armies to "
                 << targetTerr->get_name() << endl;
        }
            // or issue card order
        else if (!player->getHand()->getCards().empty()) {
            // issue any card orders
            player->getHand()->play(*player->getGame()->getDeck(), player, 0);
        }
            // or issue advance defend order - move armies from own territories
        else if (advanceDefendOrdersIssued < 1 && defendListSize > 1) {
            // if player owns >2 territories, move armies from 2nd strongest territory to strongest territory
            // if player owns <2 territories, move armies from one to the other
            vector<Territory *> ownedTers = toDefend();
            Territory *targetTerr = ownedTers.back();
            Territory *sourceTerr = ownedTers.front();
            if (defendListSize > 2) {
                sourceTerr = ownedTers.at(defendListSize - 2);
            }
            player->getPlayerOrderList()->add(new Advance(sourceTerr, targetTerr, player,
                                                          (sourceTerr->get_army_units() +
                                                           sourceTerr->get_issued_army_units()), player->getGame()));
            player->setAdvanceDefendOrdersIssued(++advanceDefendOrdersIssued); // increment orders issued
            cout << *player << " issued a new advance order from " << sourceTerr->get_name()
                 << " to their own territory " << targetTerr->get_name() << endl;
        }
            // or issue advance attack order - move armies to strongest terr to enemy terr
        else if (player->getAdvanceAttackOrdersIssued() < 1 &&
                 advanceAttackOrdersIssued < attackListSize) { // issue at most 1 advance attack orders
            // move armies from the strongest terr
            Territory *sourceTerr = toDefend().back();
            Territory *targetTerr = toAttack().front();
            int index = 0;
            bool found = false;
            // go down attack list to find weakest *neighbouring* enemy territory
            // if attack list is exhausted and no neighbouring enemy territory found, don't issue order
            while (index < attackListSize && !found) {
                if (targetIsAdjacent(sourceTerr, targetTerr)) {
                    found = true;
                } else if ((index + 1) < attackListSize) {
                    index++;
                    targetTerr = toAttack().at(index);
                } else {
                    break;
                }
            }
            if (found) {
                player->getPlayerOrderList()->add(new Advance(sourceTerr, targetTerr, player,
                                                              sourceTerr->get_army_units() +
                                                              sourceTerr->get_issued_army_units(), player->getGame()));
                player->setAdvanceAttackOrdersIssued(++advanceAttackOrdersIssued); // increment orders issued
                cout << *player << " issued a new advance order from " << sourceTerr->get_name()
                     << " to an enemy territory " << targetTerr->get_name() << endl;
            } else {
                player->setAdvanceAttackOrdersIssued(++advanceAttackOrdersIssued); // increment orders issued
                cout << *player << " cannot issue more advance order this turn. No neighbouring enemy territory found."
                     << endl;
            }

        }
            // no more order to issue
        else {
            cout << *player << " is done issuing orders" << endl;
            setAirliftCardIssued(0);
            player->setIsDoneIssuingOrders(true);
        }
    }
    else {
        cout << *player << " is done issuing orders" << endl;
        setAirliftCardIssued(0);
        player->setIsDoneIssuingOrders(true);
    }
}

// returns enemy territories from weakest to strongest
vector<Territory *> AggressivePlayerStrategy::toAttack() {
    vector<Territory*> territories = player->getTerritories();
    vector<Territory*> toAttackTerritories;
    for (Territory *ownedTerritory : territories){ //for each owned territory
        for (Territory *neighborTerritory : ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner()->getPlayerID() != player->getPlayerID()) {  //if the current player does not own the neighbor territory
                // check if territory is already in toAttackTerritories
                auto it = find_if(toAttackTerritories.begin(), toAttackTerritories.end(),
                                  [&neighborTerritory](Territory *t) {
                                      return t->get_id() == neighborTerritory->get_id();
                                  });
                if (it == toAttackTerritories.end()) { //if territory is not already in toAttackTerritories add it
                    toAttackTerritories.push_back(neighborTerritory);
                }
            }
        }
    }
    // sort toAttack territories by # of army units ascending
    sort(toAttackTerritories.begin(), toAttackTerritories.end(), [](Territory *lhs, Territory *rhs){
        return  lhs->get_army_units() < rhs->get_army_units();
    });
    return toAttackTerritories;
}

// returns own territories from weakest to strongest
vector<Territory *> AggressivePlayerStrategy::toDefend() {
    vector<Territory *> territories = player->getTerritories();
    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs) {
        return (lhs->get_army_units() + lhs->get_issued_army_units()) <
               (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return territories;
}

// find the territory most surrounded by enemy territories
Territory* AggressivePlayerStrategy::terrMostSurroundedByEnemies() const {
    vector<Territory*> territories = player->getTerritories();
    std::map<Territory*, int> enemyCount;
    for (Territory *t : territories) {
        vector<Territory*> neighbors = t->get_neighbours();
        for (Territory *neighbor : neighbors) {
            if (neighbor->get_owner()->getPlayerID() != player->getPlayerID()) {
                // enemy territory found, increment enemy count
                enemyCount[t]++;
            }
        }
    }
    std::map<Territory*, int>::iterator mostEnemy
            = std::max_element(enemyCount.begin(),enemyCount.end(),[] (const std::pair<Territory*, int>& a, const std::pair<Territory*, int>& b)->bool{ return a.second < b.second; } );
    return mostEnemy->first;
}

// check if target territory is adjacent to source territory
bool AggressivePlayerStrategy::targetIsAdjacent(Territory *source, Territory *target) const {
    vector<Territory*> neighbors = source->get_neighbours();
    for (Territory *neighbor : neighbors) {
        if (neighbor->get_id() == target->get_id()) {
            // return true, target territory IS adjacent
            return true;
        }
    }
    return false;
}

// strategy name getter
string AggressivePlayerStrategy::getStrategyName() const {
    return strategyName;
}

// airliftCardIssued getter
int AggressivePlayerStrategy::getAirliftCardIssued() const {
    return airliftCardIssued;
}

// airliftCardIssued setter
void AggressivePlayerStrategy::setAirliftCardIssued(int airliftCardIssued) {
    this->airliftCardIssued = airliftCardIssued;
}

// *****************************************************************************************************************
// BENEVOLENT PLAYER STRATEGY
// *****************************************************************************************************************

// Default constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy() : PlayerStrategy() {
}

// Parametrized constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p) {
}

// Destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() = default;

// Clone method
BenevolentPlayerStrategy* BenevolentPlayerStrategy::clone() const {
    return new BenevolentPlayerStrategy(*this);
}

// Assignment operator
BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &bps) {
    PlayerStrategy::operator = (bps);
    return *this;
}

// Stream insertion operator
ostream &operator<<(ostream &out, const BenevolentPlayerStrategy &bps) {
    cout << bps.getStrategyName();
    return out;
}

// Benevolent player issueOrder method
void BenevolentPlayerStrategy::issueOrder() {

    //Checks that cheater didn't take all his territories during issue order phase
    if (!player->getTerritories().empty()) {
        Hand *playerHand = player->getHand();
        vector<Card *> playerCards = playerHand->getCards();
        GameEngine *game = player->getGame();
        Deck *deck = game->getDeck();
        vector<Territory *> playerTerritories = player->getTerritories();
        Territory *weakestT = toDefend().front();
        Territory *strongestT = toDefend().back();

        if (player->getIssuableReinforcementPool() != 0) {
            vector<Territory *> toDefendTerritories = this->toDefend();
            int armiesToDeploy = player->getIssuableReinforcementPool();
            if (toDefendTerritories.size() != 1) {
                int armyUnitDifference = (strongestT->get_army_units() + strongestT->get_issued_army_units()) -
                                         (weakestT->get_army_units() + weakestT->get_issued_army_units());
                if (player->getIssuableReinforcementPool() - armyUnitDifference > 0) {
                    armiesToDeploy = player->getIssuableReinforcementPool() -
                                     armyUnitDifference; // only deploys the necessary amount
                } else {
                    armiesToDeploy = player->getIssuableReinforcementPool(); // deploys all issuable armies
                }
            }
            player->getPlayerOrderList()->add(
                    new Deploy(weakestT, player, armiesToDeploy,
                               player->getGame())); // deploy armies to the weakest territory
            player->setIssuableReinforcementPool(
                    player->getIssuableReinforcementPool() - armiesToDeploy); // decrement player's reinforcement pool
            weakestT->set_issued_army_units(
                    weakestT->get_issued_army_units() + armiesToDeploy); // increment territory's issued army units
            cout << *player << " issued a new deploy order of " << armiesToDeploy << " armies to "
                 << weakestT->get_name() << endl;
        } else if (!playerCards.empty()) {
            for (int i = 0; i < playerCards.size(); i++) {
                playerHand->play(*deck, player, i);
                break;
            }
        } else if (player->getAdvanceDefendOrdersIssued() < 1 &&
                   toDefend().size() > 1) { // issue at most 1 advance defend order
            // send half source territory army units
            player->getPlayerOrderList()->add(new Advance(strongestT, weakestT, player,
                                                          (strongestT->get_army_units() +
                                                           strongestT->get_issued_army_units()) / 2, game));
            player->setAdvanceDefendOrdersIssued(player->getAdvanceDefendOrdersIssued() + 1); // increment orders issued
            cout << *player << " issued a new advance order from " << strongestT->get_name() << " to their own territory "
                 << weakestT->get_name() << endl;
        } else {
            cout << *player << " is done issuing orders" << endl;
            return player->setIsDoneIssuingOrders(true);
        }
    }
    else {
        cout << *player << " is done issuing orders" << endl;
        return player->setIsDoneIssuingOrders(true);
    }
}

// Benevolent player toAttack method
// Only used to issue Negotiate orders. Player will prioritize the winning player to Negotiate with.
vector<Territory *> BenevolentPlayerStrategy::toAttack() {
    vector<Territory *> toAttackTerritories;
    for (Territory *ownedTerritory: player->getTerritories()) { //for each owned territory
        for (Territory *neighborTerritory: ownedTerritory->get_neighbours()) { //for each owned territory's neighbour
            if (neighborTerritory->get_owner() != player) {  //if the current player does not own the neighbor territory
                // check if territory is already in toAttackTerritories
                auto it = find_if(toAttackTerritories.begin(), toAttackTerritories.end(),
                                  [&neighborTerritory](Territory *t) {
                                      return t->get_id() == neighborTerritory->get_id();
                                  });
                if (it == toAttackTerritories.end()) { //if territory is not already in toAttackTerritories add it
                    toAttackTerritories.push_back(neighborTerritory);
                }
            }
        }
    }
    // sort toAttack territories by # of army units ascending
    sort(toAttackTerritories.begin(), toAttackTerritories.end(), [](Territory *lhs, Territory *rhs) {
        return lhs->get_army_units() < rhs->get_army_units();
    });
    return toAttackTerritories;
}

// Benevolent player toDefend method
// returns sorted vector of territories from weakest to strongest in army/issued army units
vector<Territory *> BenevolentPlayerStrategy::toDefend() {
    auto territories = player->getTerritories();
    sort(territories.begin(), territories.end(), [](Territory *lhs, Territory *rhs){
        return (lhs->get_army_units() + lhs->get_issued_army_units()) < (rhs->get_army_units() + rhs->get_issued_army_units());
    });
    return territories;
}

// getStrategyName method
string BenevolentPlayerStrategy::getStrategyName() const {
    return strategyName;
}