#include "BuffTimer.hpp"

Bomberman::BuffTimer::BuffTimer(IBuff *buff)
  : Timer(buff->getDuration() * 1000000), _buff(buff)
{

}

Bomberman::BuffTimer::BuffTimer(IBuff *buff, unsigned int time)
  : Timer(buff->getDuration() * 1000000 - time), _buff(buff)
{

}

Bomberman::BuffTimer::~BuffTimer()
{
  //  delete _buff; << SE CORDONNER AVEC LA MAP
}

Bomberman::IBuff const	*Bomberman::BuffTimer::getBuff()
{
  return _buff;
}
