/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SOUND_H__
#define __SOUND_H__

#include <vector>

namespace ROTOM {
  namespace Sound {
    void init();

    class Sound {
    public:
      Sound();
      Sound(char *soundPath);
      ~Sound();

      unsigned int load(char *soundPath);

      void release();

      void play();

      bool isPlaying();

      void pause();

      void stop();

      unsigned int id();

      void setGain(float newGain);

      float gain();

      float duration();

      void setLoop(bool loop);

      bool isLoop();

    private:
      unsigned int id_;

      float duration_;

      float gain_;

      bool loop_;

      unsigned int buffer_;

      int channels_;
      
      int sampleRate_;
      
      int size_;

      short *rawSoundData_;
    };

    ////////////////////////////////////////////

    class Crossfading {
    public:
      Crossfading();
      ~Crossfading();

      void start(Sound* soundFadeOut, Sound* soundFadeIn);

      //Return true if finished
      bool update();

      void setTimeToCrossfading(float time);

      float timeToCrossfadin();

    private:
      const float defaultTimeToCrossfading_ = 5.0f;

      Sound* soundFadeOut_;
      Sound* soundFadeIn_;

      float timeStarted_;
      float timeStartedCrossfading_;
      float timeToCrossfading_;

      bool crossfading_;

      float timeStartedTheFadeIn_;
    };

    ////////////////////////////////////////////

    class TrackList {
    public:
      TrackList();
      ~TrackList();

      void addSound(Sound *sound);

      void play();

      void pause();

      void stop();

      void update();

    private:
      bool loop_;

      bool playing_;

      int actualSoundPlaying_;

      std::vector<Sound *> trackList_;

      float timeStarted_;

      float timePaused_;

      Crossfading crossfading_;
    };

    ////////////////////////////////////////////

    class AutoLayering {
    public:
      AutoLayering();
      ~AutoLayering();

      void addSound(Sound *sound);

      void play();

      void update();

      void pause();

      void stop();

      void setSpeed(float speed);

      float speed();

    private:
      std::vector<Sound *> soundList_;

      float timeStarted_;

      float timePlaying_;

      float speed_;

      bool playing_;
    };

    ////////////////////////////////////////////

    class Layering {
    public:
      Layering();
      ~Layering();

      void addSound(Sound *sound);

      void update();

      void stop();

      void increase();

      void decrease();

      void setTimeToChange(float timeToChange);

      float timeToChange();
    private:
      enum Action {
        Action_nothing,
        Action_increasing,
        Action_decreasing
      };

      std::vector<Sound *> soundList_;

      float timeStarted_;

      float timeToChange_;

      Action action_;

      int actualSound_;
    };

    ////////////////////////////////////////////

    enum Branch {
      Branch_None = -1,
      Branch_A = 0,
      Branch_B = 1,
      Branch_C = 2,
    };

    class Branching {
    public:
      Branching();
      ~Branching();

      void addSound(Sound *sound);

      void update();

      void stop();

      void changeBranch(Branch newBranch);

      void setTransitionSound(Sound *sound);

    private:
      enum Action {
        Action_None,
        Action_ChangingToTransition,
        Action_ChangingToSong,
      } action;

      std::vector<Sound *> soundList_;
      Sound *transitionSound;
      
      Branch branch_;

      Crossfading crossfading_;
    };
  }
}

#endif //__SOUND_H__