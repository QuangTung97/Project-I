#ifndef TUNG_SOUND_HPP
#define TUNG_SOUND_HPP

#include "abstract/sound.hpp"
#include <fmod/fmod.hpp>

namespace tung {

// Một implementation của các Interface thao tác với âm thanh. 
// Ở đây sử dụng FMOD 
class Sound: public ISound {
private:
    struct SoundRefCount {
        FMOD::Sound *sound_;

        ~SoundRefCount();
    };

    std::shared_ptr<SoundRefCount> sound_ref_count_;

    FMOD::Channel *channel_ = nullptr;
    FMOD::System *system_ = nullptr;
    bool paused_ = false;
    bool is_stream_;

    friend class SoundManager;

public:
    // Constructor
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

    // Destructor
    virtual ~Sound();
};

class SoundManager: public ISoundManager {
private:
    FMOD::System *system_;

public:
    // Constructor
    SoundManager();

    ISoundPtr load(const std::string& filename) override;

    ISoundPtr stream(const std::string& filename) override;

    void update() override;

    // Destructor
    virtual ~SoundManager();
};

} // namespace tung

#endif
