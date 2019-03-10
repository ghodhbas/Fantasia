#include "player.h"
#include "card.h"

/** @brief Default Constructor - create a deck of 30 cards */
Player::Player()
{
    //init
    mana = 0;
    curr_mana=0;
    health = 30;
    nb_cards_hand =5;
    max_nb_summoned=5;
    nb_cards_deck = 25;

    //create deck
    for(unsigned int i =0; i<nb_cards_deck;i++){
        //create a card with random mana cost between 0-10 and add it to deck
        deck.push_back(new Card());
    }
    shuffle_deck();

    //draw 5 card;
    for (unsigned int j=0; j<nb_cards_hand;j++) {
        Card* card_drawn = new Card();
        hand.push_back(card_drawn);
    }

}

/** @brief Default Destructor */
Player::~Player(){
    //clear deck
    deck.clear();
    //clear hand
    hand.clear();
    //clear board;
    board.clear();
}

/** @brief Shuffles the deck */
void Player::shuffle_deck(){
    std::random_shuffle ( deck.begin(), deck.end() );
}


/** @brief the player plays a turn: draw, summon, attack */
void Player::play_turn(Player* opponent,int turn){
    //if(turn%2==1){
    //    std::cout<<"---------------PLAYER 1 ---------------"<<std::endl;
    //}else {
    //    std::cout<<"---------------PLAYER 2 ---------------"<<std::endl;
    //}

    //mana cap is 10
    if(mana<10) mana++;
    curr_mana=mana;
    draw();

    /*test head */
    //std::cout<<"NB cards in hand: "<<get_hand().size()<<std::endl;
    //for (unsigned int i=0; i<get_hand().size();i++) {
    //    Card* card = get_hand()[i];
    //    std::cout<<"Monster "<<i<<": Attack = "<<card->get_attack()<<"; health = "<<card->get_health()<<"; mana cost = "<< card->get_mana_cost()<<std::endl;
    //}
    //std::cout<<std::endl;


    //keep summoning while possible
    while(summon());
    //std::cout<<"NB cards in board: "<<std::endl;
    //for (unsigned int i=0; i<get_board().size();i++) {
    //
    //    Card* card = get_board()[i];
    //    std::cout<<"Monster "<<i<<": Attack = "<<card->get_attack()<<"; health = "<<card->get_health()<<"; mana cost = "<< card->get_mana_cost()<<std::endl;
    //
    //}
    //std::cout<<std::endl;

    if(turn>1)attack(opponent);
    //if(turn>1)attack_strat(opponent);

}

/** @brief draw a card from the deck */
void Player::draw(){
    Card* card_drawn = deck.at(nb_cards_deck-1);
    deck.pop_back();
    nb_cards_deck--;
    hand.push_back(card_drawn);
    nb_cards_hand++;
}

/** @brief summon a monster if possible
    returns true if summoning is succesful, false otherwise*/
bool Player::summon(){

    //board full
    if(board.size()==max_nb_summoned)return false;
    //empty hand
    if(nb_cards_hand==0) return false;
    //no mana
    //if(mana == 0 ) return false;

    //select card to be summoned
    for ( int i = curr_mana;i>=0;i--) {
        //find card with max mana cost
        for (unsigned int j = 0; j<nb_cards_hand;j++) {
            if(hand[j]->get_mana_cost() == i){
                return summon_card(hand[j],j);
            }
        }
    }

    //no card able to be summoned
    //std::cout<<"no cards with low enough mana to be summoned"<<std::endl;
    return false;

}


/** @brief utility function for summoning monster to board. This function shouldn't be explicitly called*/
bool Player::summon_card(Card *card, int hand_pos){

    if(board.size()<5){
        curr_mana = curr_mana - card->get_mana_cost();
        board.push_back(card);
        hand.erase(hand.begin()+hand_pos);
        nb_cards_hand--;
        return true;
    }

    //board is full
    //std::cout<<"can't summon board is full"<<std::endl;
    return false;
}


/** @brief attack method - all monsters on board attack opponent's monsters if none exists -> attack directly health points*/
void Player::attack(Player* p2){
    //for every owned monster
    for (unsigned int monster_pos=0 ; monster_pos < board.size();monster_pos++) {
         Card* attacker = board[monster_pos];
         //no monster on opponent's board - attack directly
         if(p2->get_board().size() == 0){
             attacker->attack_opponent(p2);
         }else{
             //if attack kills monster
             attacker->attack_card(p2);
         }
    }

}

/** @brief attack method with basic strategy- priorritize monsters that would be killed with the attack*/
void Player::attack_strat(Player* p2){
    //for every owned monster
    for (unsigned int monster_pos=0 ; monster_pos < board.size();monster_pos++) {





         Card* attacker = board[monster_pos];
         //no monster on opponent's board - attack directly
         if(p2->get_board().size() == 0){
             p2->set_health(p2->get_health() - board[monster_pos]->get_attack());
         }else{
             //if attack kills monster
             if(attacker->get_attack() >= p2->get_board()[0]->get_health()){
                 p2->destroy_monster();
             }else{
                 //damage monster
                 p2->get_board()[0]->set_health(p2->get_board()[0]->get_health()-attacker->get_attack());
             }
         }
    }

}


