#include "BuffTimer.hpp"

Bomberman::BuffTimer::BuffTimer(IBuff *buff)
  : Timer(), _buff(buff)
{

}

Bomberman::BuffTimer::~BuffTimer()
{
  delete _buff;
}

Bomberman::IBuff const	*Bomberman::BuffTimer::getBuff()
{
  return _buff;
}
