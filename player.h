#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <stdlib.h>
#include <time.h>       /* time */
#include <algorithm>    // std::random_shuffle
#include <iostream>

class Card;

class Player
{
public:
    Player();
    ~Player();

    //utility
    void shuffle_deck();
    void play_turn();
    void draw();
    bool summon();
    void attack();

    //getters - setters
    int get_health(){return health;}
    void set_health(int value){health = value;}
    unsigned int get_mana(){return mana;}
    std::vector<Card*> get_deck(){return deck;}
    std::vector<Card*> get_hand(){return hand;}
    std::vector<Card*> get_board(){return board;}

private:
    int health;
    unsigned int mana,curr_mana;
    unsigned int turn;

    unsigned int nb_cards_hand;
    std::vector<Card*> hand;

    unsigned int nb_cards_deck;
    std::vector<Card*> deck;

    unsigned int max_nb_summoned;
    unsigned int nb_summoned;
    std::vector<Card*> board;

    bool summon_card(Card* card, int hand_pos);


};

#endif // PLAYER_H
