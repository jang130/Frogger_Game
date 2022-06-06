/**
 * @file canNotLoadTexture.h
 *
 * @brief class for failure texture loading
 *
 * @authors Kamil Kośnik, Adam Moszczyński
 * @contact: kamilkosnik@gmail.com, adm.moszczynski@gmail.com
 *
 */


#ifndef WRONG_POINTS_FOR_RHOMB_H
#define WRONG_POINTS_FOR_RHOMB_H

#include <stdexcept>

class CanNotLoadTexture : public std::invalid_argument
{
    public:
        CanNotLoadTexture();

};

#endif