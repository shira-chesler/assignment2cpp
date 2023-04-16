#include "card.hpp"
using namespace ariel;

/// @brief Creating an Empty Card
Card::Card(){
    this->t=EMPTY;
    this->value=0;
}

/// @brief Copy Constructor
/// @param crd Card to copy values from
Card::Card(const Card &crd){
    this->t=crd.getType();
    this->value=crd.getValue();
}

/// @brief Creating a card with values
/// @param cardType type of card
/// @param num number value of card
Card::Card(type cardType, int num){
    this->t=cardType;
    this->value=num;
}

/// @brief destructor
Card::~Card(){
}

/// @brief copy assignment operator
/// @param crd card to assign values from
/// @return reference to current card
Card& Card::operator=(const Card& crd){
    this->t = crd.t;
    this->value = crd.value;
    return *this;
}

/// @brief move assignment operator
/// @param crd card to assign values from
/// @return reference to current card
Card& Card::operator=(Card&& crd) noexcept{
    this->t = crd.t;
    this->value = crd.value;
    return *this;
}

/// @brief move constructor
/// @param crd card to assign values from
Card::Card(Card&& crd) noexcept{
    this->t = crd.t;
    this->value = crd.value;
}

/// @brief copying values from another card to current one
/// @param crd card to copy vales from
void Card::copyFrom(const Card &crd){
    this->t=crd.getType();
    this->value=crd.getValue();
}

/// @brief setting type of existing card
/// @param cardType type to set to
void Card::setType(type cardType){
    this->t=cardType;
}

/// @brief getting type of current card
/// @return type of current card
type Card::getType() const{
    return this->t;
}

/// @brief setting value of existing card
/// @param num value (number) to set to
void Card::setValue(int num){
    this->value=num;
}

/// @brief getting value of existing card
/// @return number ofncurrent card
int Card::getValue() const{
    return this->value;
}