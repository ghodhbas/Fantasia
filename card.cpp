#include "card.h"
#include <iostream>

/** @brief Default Constructor - create a random card */
Card::Card()
{  
    //decide on the cost of the card
    mana_cost = rand()%11;
    //decide on the dmg --- dmg+health = mana_cost -2
    attack = rand()%(mana_cost+2);
    //attack and health can't be 0
    if(attack == 0){
        attack = rand()%(mana_cost+2);
    }
    health = (mana_cost + 2) - attack;
}

/** @brief create card
    @param mc - the mana cost of card*/
Card::Card(unsigned int mc)
{
    this->mana_cost= mc;
    //decide on the dmg --- dmg+health = mana_cost -2
    attack = rand() % (mana_cost+2);
    //attack and health can't be 0
    if(attack == 0){
        attack = rand()%(mana_cost+2);
    }
    health = (mana_cost + 2) - attack;
}

/** @brief attack the opponent's card - true = monster distroyed / false = still alive
    @param card - the attacked card*/
bool Card::attack_card(Card* card){
    //current attacker has dmg higher or equal to attacked health
    if(this->attack >= card->get_health()){
        return true;
    }

    card->set_health(card->get_health()-this->attack);
    return false;
}

/** @brief attack the opponent's health - true = player lost / false = player still alive
    @param card - the attacked card*/
bool Card::attack_opponent(Player *player){
    //current attacker has dmg higher or equal to attacked health
    if(this->attack >= player->get_health()){
        return true;
    }

    player->set_health(player->get_health()-this->attack);
    return false;
}
