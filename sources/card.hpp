#ifndef _CARD_HPP
#define _CARD_HPP

namespace ariel{
    enum type{HEART=1, DIAMOND=2, CLUB=3, SPADE=4};
class Card
{
private:
    type t;
    int value;
public:
    Card();
    Card(type t, int num);
    ~Card();
    void setType();
    type getType();
    void setValue();
    int getValue();
};
}
#endif