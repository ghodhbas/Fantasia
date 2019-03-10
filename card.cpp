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
bool Card::attack_card(Player* player){
    if(this->get_attack() >= player->get_board()[0]->get_health()){
        player->destroy_monster();
    }else{
        //damage monster
        player->get_board()[0]->set_health(player->get_board()[0]->get_health()-this->get_attack());
    }
    return true;
}

/** @brief attack the opponent's health - true = player lost / false = player still alive
    @param card - the attacked card*/
bool Card::attack_opponent(Player *player){

    player->set_health(player->get_health()-this->attack);
    return true;
}
