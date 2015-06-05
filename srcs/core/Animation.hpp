#ifndef ANIMATION_H_
# define ANIMATION_H_

# include <string>
# include <list>
# include "Timer.hpp"

class Animation
{
public:
  Animation(unsigned int const & frames, unsigned int const & speed);

virtual ~Animation();

  void		setAnim(unsigned int const startframe,
			unsigned int const endframe,
			bool loop);
  void		setAnim(unsigned int const startframe,
			unsigned int const endframe,
			bool loop,
			unsigned int const speed);

  void		setSpeed(unsigned int const speed);

  unsigned int	getFrame();
  std::string	getFrameName();

  void		setFrameCount(unsigned int const framecount);

private:
  Timer		_timer;
  unsigned int	_frameCount;
  unsigned int	_defaultSpeed;

  typedef struct
  {
    unsigned int	start;
    unsigned int	end;
    unsigned int	total;
    bool		loop;
    unsigned int	speed;
  }			Queue;

  std::list<Queue> _animationQueue;
};

#endif /* !ANIMATION_H_ */
