/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __TIME_H__
#define __TIME_H__

namespace ROTOM {
  namespace TIME {
    //Return the time since the application started
    float appTime();

    class Countdown {
    public:
      Countdown();
      Countdown(const double timeAmount);
      ~Countdown();

      void startTimer(const double timeAmount);

      bool finish();

    private:
      double timeToEnd_ = 0.0;
    };

    class Chronometer {
    public:
      Chronometer();
      ~Chronometer();

      void start();
      const double end();

    private:
      double timeWhenStarted_ = 0.0;
    };
  }
}

#endif //__TIME_H__