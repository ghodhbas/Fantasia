#include "card.h"
#include "player.h"
#include <iostream>

int main()
{
    //create random seed
    srand (time(nullptr));
    unsigned int p1wins = 0;
    unsigned int p2wins = 0;

    for (int rep =0; rep<10000;rep++) {


        Player* p1 = new Player();
        Player* p2 = new Player();
        int turn =0;



        // fix extra monster summoned
        while (p1->get_health()>0 && p2->get_health()>0) {
            turn++;
            if(turn % 2 ==1){
                p1->play_turn(p2,turn);
            }else {
                p2->play_turn(p1,turn);
            }
            //std::cout<<"Player1 health = "<< p1->get_health()<<std::endl;
            //std::cout<<"Player2 health = "<< p2->get_health()<<std::endl;
            //std::cout<<std::endl;
            if(p1->get_deck().size()==0) break;
        }


        if(p1->get_health()<=0){
            p2wins++;
        }else if(p1->get_deck().size()==0){
            p2wins++;
        }else{
            p1wins++;
        }


        std::cout<<"game "<<rep<<" over"<<std::endl;
        delete p1;
        delete p2;
    }

    std::cout<<"Player 1 Score = "<<p1wins<<std::endl;
    std::cout<<"Player 2 Score = "<<p2wins<<std::endl;
    return 0;
}


void testing(){
    //std::cout<<"NB cards in deck: "<<p1.get_deck().size()<<std::endl;
    //for (unsigned int i=0; i<p1.get_deck().size();i++) {
    //    Card* card = p1.get_deck()[i];
    //    std::cout<<"Monster "<<i<<": Attack = "<<card->get_attack()<<"; health = "<<card->get_health()<<"; mana cost = "<< card->get_mana_cost()<<std::endl;
    //}

    //test summon!!!!!

    //std::cout<<"NB cards in hand: "<<p1.get_hand().size()<<std::endl;
    //for (unsigned int i=0; i<p1.get_hand().size();i++) {
    //    Card* card = p1.get_hand()[i];
    //    std::cout<<"Monster "<<i<<": Attack = "<<card->get_attack()<<"; health = "<<card->get_health()<<"; mana cost = "<< card->get_mana_cost()<<std::endl;
    //}
    //std::cout<<std::endl;
    //std::cout<<std::endl;

    //p1.set_mana(10);

    //testing summoning
    //while(p1.summon()){
    //    std::cout<<"NB cards in hand: "<<p1.get_hand().size()<<std::endl;
    //    for (unsigned int i=0; i<p1.get_hand().size();i++) {
    //        Card* card = p1.get_hand()[i];
    //        std::cout<<"Monster "<<i<<": Attack = "<<card->get_attack()<<"; health = "<<card->get_health()<<"; mana cost = "<< card->get_mana_cost()<<std::endl;
    //    }
    //
    //    std::cout<<"cards in board: "<<std::endl;
    //    for (unsigned int i=0; i<p1.get_board().size();i++) {
    //        if(p1.get_board()[i] != nullptr){
    //            Card* card = p1.get_board()[i];
    //            std::cout<<"Monster "<<i<<": Attack = "<<card->get_attack()<<"; health = "<<card->get_health()<<"; mana cost = "<< card->get_mana_cost()<<std::endl;
    //        }
    //    }
    //
    //    if(p1.get_board()[1] != nullptr) p1.set_board(1,nullptr);
    //}

}

