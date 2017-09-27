#ifndef TUNG_SOUND_H
#define TUNG_SOUND_H

#include "abstract/sound.hpp"
#include <fmod/fmod.hpp>

namespace tung {

class Sound: public ISound {
private:
    struct SoundRefCount {
        FMOD::Sound *sound_;

        ~SoundRefCount();
    };

    std::shared_ptr<SoundRefCount> sound_ref_count_;

    FMOD::Channel *channel_;
    FMOD::System *system_;
    bool paused_ = false;
    bool is_stream_;

    friend class SoundManager;

public:
    Sound();

    void play() override;

    void pause() override;
    
    void resume() override;

    void stop() override;

    void volume(float value) override;

    float volume() override;

    void loop(bool loop) override;

    bool loop() override;

    ISoundPtr clone() override;

    virtual ~Sound();
};

class SoundManager: public ISoundManager {
private:
    FMOD::System *system_;

public:
    SoundManager();

    ISoundPtr load(const std::string& filename) override;

    ISoundPtr stream(const std::string& filename) override;

    // update inside game loop
    void update();

    virtual ~SoundManager();
};

} // namespace tung

#endif
