#ifndef SOUND_ABSTRACT_H
#define SOUND_ABSTRACT_H

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

struct ISound {
    virtual void play() = 0;

    virtual void pause() = 0;
    
    virtual void resume() = 0;

    virtual void stop() = 0;

    virtual void volume(float value) = 0;

    virtual float volume() = 0;

    virtual void loop(bool value) = 0;

    virtual bool loop() = 0;

    virtual std::unique_ptr<ISound> clone() = 0;

    virtual ~ISound() {}
};

typedef std::unique_ptr<ISound> ISoundPtr;

struct ISoundManager {
    virtual ISoundPtr load(const std::string& filename) = 0;

    virtual ISoundPtr stream(const std::string& filename) = 0;

    virtual ~ISoundManager() {}
};

} // namespace tung

#endif
