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
    nb_cards_deck = 30;
    turn =0;
    //inot board
    for (int k = 0;k<max_nb_summoned;k++) {
        board.push_back(nullptr);
    }

    //create random seed
    srand (time(NULL));
    //create deck
    for(unsigned int i =0; i<nb_cards_deck;i++){
        //create a card with random mana cost between 0-10 and add it to deck
        deck.push_back(new Card());
    }
    shuffle_deck();

    //draw 5 card;
    for (unsigned int j=0; j<nb_cards_hand;j++) {
        draw();
    }

}

/** @brief Default Destructor */
Player::~Player(){
    //clear deck
    for(unsigned int i =0; i<nb_cards_deck;i++){
        //create a card with random mana cost between 0-10 and add it to deck
        delete deck.at(i);
    }
    deck.clear();

    //clear hand
    for(unsigned int i =0; i<hand.size();i++){
        //create a card with random mana cost between 0-10 and add it to deck
        delete hand.at(i);
    }
    hand.clear();
}

/** @brief Shuffles the deck */
void Player::shuffle_deck(){
    std::random_shuffle ( deck.begin(), deck.end() );
}


/** @brief the player plays a turn: draw, summon, attack */
void Player::play_turn(){
    turn++;
    //mana cap is 10
    if(mana<10) mana++;
    curr_mana=mana;
    draw();
    //keep summoning while possible
    while(summon());

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
    if(nb_summoned==max_nb_summoned)return false;
    //empty hand
    if(nb_cards_hand==0) return false;
    //no mana
    if(mana == 0 ) return false;

    //select card to be summoned
    for ( int i = mana;i>=0;i--) {
        //find card with max mana cost
        for (unsigned int j = 0; j<nb_cards_hand;j++) {
            if(hand[j]->get_mana_cost() == i){
                return summon_card(hand[j],j);
            }
        }
    }

    //no card able to be summoned
    std::cout<<"no cards with low enough mana to be summoned"<<std::endl;
    return false;

}


/** @brief utility function for summoning monster to board. This function shouldn't be explicitly called*/
bool Player::summon_card(Card *card, int hand_pos){

    for (unsigned long i =0 ;i<board.size();i++) {
        //find empty board case
        if(board.at(i)==nullptr){
            curr_mana = curr_mana - card->get_mana_cost();
            board[i]=card;
            nb_summoned++;
            hand.erase(hand.begin()+hand_pos);
            nb_cards_hand--;
            return true;
        }
    }

    //board is full
    std::cout<<"can't summon board is full"<<std::endl;
    return false;
}




