#ifndef CARD_H
#define CARD_H

#include <stdlib.h>
#include <time.h>       /* time */
#include "player.h"

class Card
{
public:
    //constructors
    Card();
    Card(unsigned int mc);

    //attacking
    bool attack_card(Player* player);
    bool attack_opponent(Player* player);

    //getters - stters
    unsigned int get_attack(){return attack;}
    unsigned int get_health(){return health;}
    unsigned int get_mana_cost(){return mana_cost;}
    void set_health(unsigned int value){health=value;}

private:
    unsigned int mana_cost,attack,health;


};

#endif // CARD_H
