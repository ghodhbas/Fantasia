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
    void play_turn(Player* opponent, int turn);
    void draw();
    bool summon();
    void attack(Player* p2);
    void attack_strat(Player* p2);

    //getters - setters
    int get_health(){return health;}
    void set_health(int value){health = value;}
    unsigned int get_mana(){return mana;}
    std::vector<Card*> get_deck(){return deck;}
    std::vector<Card*> get_hand(){return hand;}
    std::vector<Card*> get_board(){return board;}
    void set_board(int pos,Card* v){board[pos]=v;}
    void destroy_monster(){board.erase(board.begin());}
    void destroy_monster(int pos){board.erase(board.begin()+pos);}


    /** testing func*/
    void set_mana(unsigned int v){mana = v; curr_mana=mana;}


private:
    int health;
    unsigned int mana,curr_mana;

    unsigned int nb_cards_hand;
    std::vector<Card*> hand;

    unsigned int nb_cards_deck;
    std::vector<Card*> deck;

    unsigned int max_nb_summoned;
    std::vector<Card*> board;

    void attack_routine(Player* player, Card* attacker);
    bool summon_card(Card* card, int hand_pos);


};

#endif // PLAYER_H
