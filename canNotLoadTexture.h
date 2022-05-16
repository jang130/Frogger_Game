#ifndef WRONG_POINTS_FOR_RHOMB_H
#define WRONG_POINTS_FOR_RHOMB_H

#include <stdexcept>

class CanNotLoadTexture : public std::invalid_argument
{
    public:
        CanNotLoadTexture();

};

#endif