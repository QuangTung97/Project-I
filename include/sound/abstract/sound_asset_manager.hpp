#ifndef SOUND_ABSTRACT_SOUND_ASSET_MANAGER_HPP
#define SOUND_ABSTRACT_SOUND_ASSET_MANAGER_HPP

#include "sound.hpp"

namespace tung {

struct ISoundAssetManager {
    virtual ISoundPtr get_sound(const std::string& filename) = 0;

    virtual ~ISoundAssetManager() {}
};

} // namespace tung

#endif