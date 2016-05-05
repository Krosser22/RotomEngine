/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/sound.h"
#include "general/time.h"
#include <stb_vorbis.h>
#include <AL/alext.h>

void sound::init() {
  int channels = -1, sample_rate = -1, size = -1;
  short *raw_sound_data;
  size = stb_vorbis_decode_filename("sound/example.ogg", &channels, &sample_rate, &raw_sound_data);

  printf("Audio loaded, size = %d, channels = %d, sample rate = %d\n", size, channels, sample_rate);

  ALuint buffer;
  alGenBuffers(1, &buffer);
  if (channels == 1) {
    alBufferData(buffer, AL_FORMAT_MONO16, (void*)raw_sound_data, size * channels * 2, sample_rate);
  } else if (channels == 2) {
    alBufferData(buffer, AL_FORMAT_STEREO16, (void*)raw_sound_data, size * channels * 2, sample_rate);
  }

  ALuint source;
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);

  alSourcePlay(source);
  ALfloat gain = 1.0f;
  alSourcef(source, AL_GAIN, gain);
}

void ROTOM::SOUND::init() {
  ALCdevice *device = alcOpenDevice(nullptr);
  ALCcontext *context = alcCreateContext(device, nullptr);
  alcMakeContextCurrent(context);
  if (!device || !context) {
    printf("No sound hardware detected\n");
  }
}

ROTOM::SOUND::Sound::Sound() {
  id_ = -1;
  duration_ = 0.0f;
  gain_ = 1.0f;
  loop_ = false;
  buffer_ = 0;
  channels_ = -1;
  sampleRate_ = -1;
  size_ = -1;
}

ROTOM::SOUND::Sound::Sound(char *soundPath) {
  id_ = -1;
  duration_ = 0.0f;
  gain_ = 1.0f;
  loop_ = false;
  buffer_ = 0;
  channels_ = -1;
  sampleRate_ = -1;
  size_ = -1;

  load(soundPath);
}

ROTOM::SOUND::Sound::~Sound() {}

unsigned int ROTOM::SOUND::Sound::load(char *soundPath) {
  size_ = stb_vorbis_decode_filename(soundPath, &channels_, &sampleRate_, &rawSoundData_);
  duration_ = ((float)size_ / (float)sampleRate_);

  if (size_ == -1) {
    printf("Audio NOT found\n");
    id_ = size_;
  } else {
    printf("Audio loaded, size = [%d], channels = [%d], sample rate = [%d]\n", size_, channels_, sampleRate_);
    //printf("Duration(Seconds): [%f]\n", duration_);

    alGenBuffers(1, &buffer_);
    if (channels_ == 1) {
      alBufferData(buffer_, AL_FORMAT_MONO16, (void*)rawSoundData_, size_ * channels_ * 2, sampleRate_);
    } else if (channels_ == 2) {
      alBufferData(buffer_, AL_FORMAT_STEREO16, (void*)rawSoundData_, size_ * channels_ * 2, sampleRate_);
    }

    alGenSources(1, &id_);
    alSourcei(id_, AL_BUFFER, buffer_);

    setLoop(loop_);
    setGain(gain_);
  }
  return id_;
}

void ROTOM::SOUND::Sound::release() {
  stop();
  alDeleteSources(1, &id_);
  alDeleteBuffers(1, &buffer_);
}

void ROTOM::SOUND::Sound::play() {
  alSourcePlay(id_);
  printf("Playing Sound: [%d]\n", id_);
}

bool ROTOM::SOUND::Sound::isPlaying() {
  ALint state = 0;
  bool playing = false;

  alGetSourcei(id_, AL_SOURCE_STATE, &state);
  if (state == AL_PLAYING) {
    playing = true;
  }
  return playing;
}

void ROTOM::SOUND::Sound::pause() {
  alSourcePause(id_);
}

void ROTOM::SOUND::Sound::stop() {
  alSourceStop(id_);
}

unsigned int ROTOM::SOUND::Sound::id() {
  return id_;
}

void ROTOM::SOUND::Sound::setGain(float newGain) {
  gain_ = newGain;
  alSourcef(id_, AL_GAIN, gain_);
}

float ROTOM::SOUND::Sound::gain() {
  return gain_;
}

float ROTOM::SOUND::Sound::duration() {
  return duration_;
}

void ROTOM::SOUND::Sound::setLoop(bool loop) {
  loop_ = loop;
  alSourcef(id_, AL_LOOPING, loop_);
}

bool ROTOM::SOUND::Sound::isLoop() {
  return loop_;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//|||||||||||||||||||||||||||||||||||||||||||||
//SOUND - SOUND - SOUND - SOUND - SOUND - SOUND
//---------------------------------------------
//
//---------------------------------------------
//Crossfading ---- Crossfading ---- Crossfading
//|||||||||||||||||||||||||||||||||||||||||||||
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

ROTOM::SOUND::Crossfading::Crossfading() {
  soundFadeOut_ = nullptr;
  soundFadeIn_ = nullptr;

  timeStarted_ = 0.0f;
  timeToCrossfading_ = defaultTimeToCrossfading_;

  crossfading_ = false;

  timeStartedTheFadeIn_ = TIME::appTime();
}

ROTOM::SOUND::Crossfading::~Crossfading() {}

void ROTOM::SOUND::Crossfading::start(Sound* soundFadeOut, Sound* soundFadeIn) {
  crossfading_ = false;

  soundFadeOut_ = soundFadeOut;
  soundFadeIn_ = soundFadeIn;

  soundFadeOut_->setGain(1.0f);
  soundFadeIn_->setGain(0.0f);

  timeToCrossfading_ = defaultTimeToCrossfading_; //Reset
  
  if (soundFadeIn_->duration() * 0.4f < timeToCrossfading_) {
    timeToCrossfading_ = soundFadeIn_->duration() * 0.4f;
  }

  if (soundFadeOut_->duration() * 0.4f < timeToCrossfading_) {
    timeToCrossfading_ = soundFadeOut_->duration() * 0.4f;
  }

  timeStarted_ = TIME::appTime() - (TIME::appTime() - timeStartedTheFadeIn_);
}

bool ROTOM::SOUND::Crossfading::update() {
  bool finished = false;

  if (!crossfading_) {
    if ((TIME::appTime() - timeStarted_) > soundFadeOut_->duration() - timeToCrossfading_) {
      crossfading_ = true;
      timeStartedTheFadeIn_ = TIME::appTime();
      soundFadeIn_->play();
      soundFadeIn_->setGain(0.0f);
      timeStartedCrossfading_ = TIME::appTime();
      printf("NOW CROSSFADING\n");
    } else {
      //printf("NO CROSSFADING\n");
    }
  } else {
    float actualTimeInSequence = (TIME::appTime() - timeStartedCrossfading_) / timeToCrossfading_;

    soundFadeOut_->setGain(1.0f - actualTimeInSequence);
    soundFadeIn_->setGain(actualTimeInSequence);

    if (actualTimeInSequence > 1.0f) {
      printf("CROSSFADING FINISHED\n");
      finished = true;
    } else {
      printf("CROSSFADING: [%f]\n", actualTimeInSequence);
    }
  }
  return finished;
}

void ROTOM::SOUND::Crossfading::setTimeToCrossfading(float time) {
  timeToCrossfading_ = time;
}

float ROTOM::SOUND::Crossfading::timeToCrossfadin() {
  return timeToCrossfading_;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//|||||||||||||||||||||||||||||||||||||||||||||
//CROSSFADING ---- CROSSFADING ---- CROSSFADING
//---------------------------------------------
//
//---------------------------------------------
//TRACKLIST - TRACKLIST - TRACKLIST - TRACKLIST
//|||||||||||||||||||||||||||||||||||||||||||||
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

ROTOM::SOUND::TrackList::TrackList() {
  loop_ = true;
  playing_ = false;
  actualSoundPlaying_ = 0;
  trackList_.clear();
}

ROTOM::SOUND::TrackList::~TrackList() {
  trackList_.clear();
}

void ROTOM::SOUND::TrackList::addSound(Sound *sound) {
  trackList_.push_back(sound);
}

void ROTOM::SOUND::TrackList::play() {
  playing_ = true;
  timeStarted_ = TIME::appTime();

  trackList_.at(actualSoundPlaying_)->play();

  if (trackList_.size() > 1) {
    crossfading_.start(trackList_.at(actualSoundPlaying_), trackList_.at(actualSoundPlaying_ + 1));
  }
}

void ROTOM::SOUND::TrackList::pause() {
  playing_ = false;
  trackList_.at(actualSoundPlaying_)->pause();
  timePaused_ = TIME::appTime();
}

void ROTOM::SOUND::TrackList::stop() {
  playing_ = false;
  for (unsigned int i = 0; i < trackList_.size(); ++i) {
    trackList_.at(i)->stop();
  }
  actualSoundPlaying_ = 0;
}

void ROTOM::SOUND::TrackList::update() {
  if (playing_) {
    if (crossfading_.update()) {
      ++actualSoundPlaying_;

      bool startNext = true;
      if (actualSoundPlaying_ == trackList_.size()) {
        actualSoundPlaying_ = 0;

        if (!loop_) {
          startNext = false;
        }
      }

      if (startNext) {
        if (actualSoundPlaying_ + 1 >= (int)trackList_.size()) {
          crossfading_.start(trackList_.at(actualSoundPlaying_), trackList_.at(0));
        } else {
          crossfading_.start(trackList_.at(actualSoundPlaying_), trackList_.at(actualSoundPlaying_ + 1));
        }
      }
    }
  }
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//|||||||||||||||||||||||||||||||||||||||||||||
//TRACKLIST - TRACKLIST - TRACKLIST - TRACKLIST
//---------------------------------------------
//
//---------------------------------------------
//AUTOLAYERING --- AUTOLAYERING -- AUTOLAYERING
//|||||||||||||||||||||||||||||||||||||||||||||
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

ROTOM::SOUND::AutoLayering::AutoLayering() {
  soundList_.clear();

  timeStarted_ = 0.0f;
  timePlaying_ = 0.0f;
  speed_ = 0.2f;

  playing_ = false;
}

ROTOM::SOUND::AutoLayering::~AutoLayering() {}

void ROTOM::SOUND::AutoLayering::addSound(Sound *sound) {
  soundList_.push_back(sound);
}

void ROTOM::SOUND::AutoLayering::play() {
  timeStarted_ = TIME::appTime();
  for (unsigned int i = 0; i < soundList_.size(); ++i) {
    soundList_.at(i)->play();
    soundList_.at(i)->setGain(0.0f);
    soundList_.at(i)->setLoop(true);
  }
  playing_ = true;
}

void ROTOM::SOUND::AutoLayering::update() {
  if (playing_) {
    timePlaying_ = (TIME::appTime() - timeStarted_) * speed_;
    bool isIncreasingGain = ((((int)(timePlaying_)) / soundList_.size()) % 2 == 0);
    float newGain = timePlaying_ - ((int)(timePlaying_));
    int atPos = (int)timePlaying_;
    while (atPos > (int)(soundList_.size()) - 1) {
      atPos -= soundList_.size();
    }

    if (isIncreasingGain) {
      soundList_.at((int)(atPos))->setGain(newGain);
      printf("Increasing: [%d]-[%f]\n", atPos, newGain);
    } else {
      soundList_.at(soundList_.size() - atPos - 1)->setGain(1.0f - newGain);
      printf("Decreasing: [%d]-[%f]\n", soundList_.size() - atPos - 1, 1.0f - newGain);
    }
  }
}

void ROTOM::SOUND::AutoLayering::pause() {
  for (unsigned int i = 0; i < soundList_.size(); ++i) {
    soundList_.at(i)->pause();
  }
  playing_ = false;
}

void ROTOM::SOUND::AutoLayering::stop() {
  for (unsigned int i = 0; i < soundList_.size(); ++i) {
    soundList_.at(i)->stop();
  }
  playing_ = false;
}

void ROTOM::SOUND::AutoLayering::setSpeed(float speed) {
  speed_ = speed;
}

float ROTOM::SOUND::AutoLayering::speed() {
  return speed_;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//|||||||||||||||||||||||||||||||||||||||||||||
//AUTOLAYERING --- AUTOLAYERING -- AUTOLAYERING
//---------------------------------------------
//
//---------------------------------------------
//LAYERING -- LAYERING --- LAYERING -- LAYERING
//|||||||||||||||||||||||||||||||||||||||||||||
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

ROTOM::SOUND::Layering::Layering() {
  soundList_.clear();

  timeStarted_ = 0.0f;
  timeToChange_ = 5.0f;

  action_ = Action_nothing;

  actualSound_ = -1;
}

ROTOM::SOUND::Layering::~Layering() {}

void ROTOM::SOUND::Layering::addSound(Sound *sound) {
  sound->stop();
  sound->setGain(0.0f);
  sound->setLoop(true);
  soundList_.push_back(sound);
}

void ROTOM::SOUND::Layering::update() {
  if (!action_ == Action_nothing) {
    float timeThisRound = (TIME::appTime() - timeStarted_);
    float newGain = timeThisRound / timeToChange_;

    if (newGain >= 1.0f) {
      newGain = 1.0f;
      action_ = Action_nothing;

      if (action_ == Action_decreasing) {
        soundList_.at(actualSound_ + 1)->stop();
      }
    }

    if (action_ == Action_increasing) {
      printf("Increasing[%d]: [%f]\n", actualSound_, newGain);
      soundList_.at(actualSound_)->setGain(newGain);
    } else if (action_ == Action_decreasing) {
      soundList_.at(actualSound_ + 1)->setGain(1.0f - newGain);
      printf("Decreasing[%d]: [%f]\n", actualSound_ + 1, 1.0f - newGain);
    }
  }
}

void ROTOM::SOUND::Layering::stop() {
  for (unsigned int i = 0; i < soundList_.size(); ++i) {
    soundList_.at(i)->stop();
  }
}

void ROTOM::SOUND::Layering::increase() {
  if (action_ == Action_nothing && actualSound_ < ((int)soundList_.size() - 1)) {
    action_ = Action_increasing;
    timeStarted_ = TIME::appTime();
    ++actualSound_;
    soundList_.at(actualSound_)->play();
    printf("Increased\n");
  }
}

void ROTOM::SOUND::Layering::decrease() {
  if (action_ == Action_nothing && actualSound_ > -1) {
    action_ = Action_decreasing;
    timeStarted_ = TIME::appTime();
    --actualSound_;
    printf("Decreased\n");
  }
}

void ROTOM::SOUND::Layering::setTimeToChange(float timeToChange) {
  timeToChange_ = timeToChange;
}

float ROTOM::SOUND::Layering::timeToChange() {
  return timeToChange_;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//|||||||||||||||||||||||||||||||||||||||||||||
//LAYERING -- LAYERING --- LAYERING -- LAYERING
//---------------------------------------------
//
//---------------------------------------------
//BRANCHING - BRANCHING - BRANCHING - BRANCHING
//|||||||||||||||||||||||||||||||||||||||||||||
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

ROTOM::SOUND::Branching::Branching() {
  soundList_.clear();
  action = Action_None;
  branch_ = Branch_None;
}

ROTOM::SOUND::Branching::~Branching() {}

void ROTOM::SOUND::Branching::addSound(Sound *sound) {
  sound->stop();
  sound->setGain(0.0f);
  sound->setLoop(true);
  soundList_.push_back(sound);
}

void ROTOM::SOUND::Branching::update() {
  if (action != Action_None) {
    if (action == Action_ChangingToTransition) {
      if (crossfading_.update()) {
        crossfading_.start(transitionSound, soundList_.at(branch_));
        action = Action_ChangingToSong;
      }
    } else if (action == Action_ChangingToSong) {
      if (crossfading_.update()) {
        action = Action_None;
        printf("Changing to sound: [%d]\n", soundList_.at(branch_)->id());
      }
    }
  }
}

void ROTOM::SOUND::Branching::stop() {
  for (unsigned int i = 0; i < soundList_.size(); ++i) {
    soundList_.at(i)->stop();
  }
  transitionSound->stop();
}

void ROTOM::SOUND::Branching::changeBranch(Branch newBranch) {
  if (action == Action_None) {
    if (branch_ == Branch_None) {
      crossfading_.start(new Sound(), transitionSound);
    } else {
      crossfading_.start(soundList_.at(branch_), transitionSound);
    }
    action = Action_ChangingToTransition;
    branch_ = newBranch;
  }
}

void ROTOM::SOUND::Branching::setTransitionSound(Sound *sound) {
  transitionSound = sound;
}
