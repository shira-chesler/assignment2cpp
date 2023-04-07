#ifndef CARD_HPP
#define CARD_HPP

namespace ariel{
    enum type{EMPTY=0,HEART=1, DIAMOND=2, CLUB=3, SPADE=4};
class Card
{
private:
    type t;
    int value;
public:
    Card();
    Card(const Card &crd);
    Card(type cardType, int num);
    ~Card();
    Card& operator=(const Card&);
    Card& operator=(Card&&) noexcept;
    Card(Card&&) noexcept;
    void copyFrom(const Card &crd);
    void setType(type cardType);
    type getType() const;
    void setValue(int num);
    int getValue() const;
};
}
#endif