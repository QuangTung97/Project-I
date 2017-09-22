#include <sound/sound.h>

namespace tung {

// Sound

Sound::SoundRefCount::~SoundRefCount() {
    sound_->release();
}

void Sound::play() {
    system_->playSound(sound_ref_count_->sound_, 
            nullptr, false, &channel_);
}

void Sound::pause() {
    paused_ = true;
    channel_->setPaused(true);
}

void Sound::resume() {
    channel_->setPaused(false);
    paused_ = false;
}

void Sound::stop() {
    channel_->stop();
}

void Sound::volume(float value) {
    channel_->setVolume(value);
}

float Sound::volume() {
    float vol;
    channel_->getVolume(&vol);
    return vol;
}

void Sound::loop(bool loop) {
    if (loop) 
        channel_->setLoopCount(-1);
    else
        channel_->setLoopCount(0);
}

bool Sound::loop() {
    int loop;
    channel_->getLoopCount(&loop);;
    return loop != 0 ? true : false;
}

ISoundPtr Sound::clone() {
    if (is_stream_)
        throw SoundError("Can't clone stream");

    auto result = std::make_unique<Sound>();
    result->sound_ref_count_ = this->sound_ref_count_;
    result->system_ = this->system_;
    return std::move(result);
}

Sound::Sound() {}

Sound::~Sound() {
    channel_->stop();
}


// Sound Manager
SoundManager::SoundManager() {
    FMOD::System_Create(&system_);
    FMOD_RESULT ec = system_->init(100, FMOD_INIT_NORMAL, 0);
    if (ec != FMOD_OK)
        throw SoundError("Can't init system");
}

ISoundPtr SoundManager::load(const std::string& filename) {
    auto result = std::make_unique<Sound>();
    result->is_stream_ = false;
    result->sound_ref_count_ 
        = std::make_shared<Sound::SoundRefCount>();

    result->system_ = system_;

    FMOD_RESULT ec = system_->createSound(
            filename.c_str(), 
            FMOD_DEFAULT, 0, 
            &result->sound_ref_count_->sound_);

    if (ec != FMOD_OK)
        throw SoundError("Can't load");

    return std::move(result);
}

ISoundPtr SoundManager::stream(const std::string& filename) {
    auto result = std::make_unique<Sound>();
    result->is_stream_ = true;
    result->sound_ref_count_ 
        = std::make_shared<Sound::SoundRefCount>();

    result->system_ = system_;

    FMOD_RESULT ec = system_->createStream(
            filename.c_str(),
            FMOD_DEFAULT, 0, 
            &result->sound_ref_count_->sound_);

    if (ec != FMOD_OK)
        throw SoundError("Can't stream");

    return std::move(result);
}

void SoundManager::update() {
    system_->update();
}

SoundManager::~SoundManager() {
    system_->release();
}

} // namespace tung
