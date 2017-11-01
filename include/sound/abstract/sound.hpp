#ifndef SOUND_ABSTRACT_HPP
#define SOUND_ABSTRACT_HPP

#include <memory>
#include <string>

namespace tung {

class SoundError: public std::exception {
private:
    std::string error_;

public:
    SoundError(std::string error): error_{std::move(error)} {}

    const char *what() const noexcept override {
        return error_.c_str(); 
    }
};

struct ISound;

typedef std::shared_ptr<ISound> ISoundPtr;

struct ISound {
    virtual void play() = 0;

    virtual void pause() = 0;
    
    virtual void resume() = 0;

    virtual void stop() = 0;

    virtual void volume(float value) = 0;

    virtual float volume() = 0;

    virtual void loop(bool value) = 0;

    virtual bool loop() = 0;

    virtual ISoundPtr clone() = 0;

    virtual ~ISound() {}
};

struct ISoundManager {
    virtual ISoundPtr load(const std::string& filename) = 0;

    virtual ISoundPtr stream(const std::string& filename) = 0;

    virtual void update() = 0;

    virtual ~ISoundManager() {}
};

} // namespace tung

#endif
