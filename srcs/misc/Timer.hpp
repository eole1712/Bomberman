#ifndef TIMER_H_
# define TIMER_H_

# include <ctime>
# include <chrono>

namespace PlazzaTime
{

class Timer
{
public:
  Timer(uintmax_t time);
  virtual ~Timer();
  void				start();
  void				stop();
  void				reset();
  bool				isFinished();
  uintmax_t			getElapsedTime();

private:
  Timer(const Timer &);
  Timer &operator=(const Timer &);
  std::chrono::microseconds	getCurTime();

private:
  std::chrono::microseconds				_time;
  std::chrono::microseconds				_saveTime;
  std::chrono::time_point<std::chrono::system_clock>	_clock;
};

}
#endif /* !TIMER_H_ */
