#include "card.hpp"
using namespace ariel;

Card::Card(){
    this->t=EMPTY;
    this->value=0;
}

Card::Card(const Card &crd){
    this->t=crd.getType();
    this->value=crd.getValue();
}

Card::Card(type cardType, int num){
    this->t=cardType;
    this->value=num;
}

Card::~Card(){
}

Card& Card::operator=(const Card& crd){
    this->t = crd.t;
    this->value = crd.value;
    return *this;
}

Card& Card::operator=(Card&& crd) noexcept{
    this->t = crd.t;
    this->value = crd.value;
    return *this;
}

Card::Card(Card&& crd) noexcept{
    this->t = crd.t;
    this->value = crd.value;
}

void Card::copyFrom(const Card &crd){
    this->t=crd.getType();
    this->value=crd.getValue();
}

void Card::setType(type cardType){
    this->t=cardType;
}

type Card::getType() const{
    return this->t;
}

void Card::setValue(int num){
    this->value=num;
}

int Card::getValue() const{
    return this->value;
}