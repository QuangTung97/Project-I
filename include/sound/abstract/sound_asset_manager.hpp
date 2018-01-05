#ifndef SOUND_ABSTRACT_SOUND_ASSET_MANAGER_HPP
#define SOUND_ABSTRACT_SOUND_ASSET_MANAGER_HPP

#include "sound.hpp"

namespace tung {

// Interface cho việc lấy âm thanh từ khối quản lý tài nguyên 
struct ISoundAssetManager {
    // Lấy con trỏ trỏ đến object đại diện cho âm thanh đã load 
    // @filename: Đường dẫn đến file âm thanh
    // Return: Con trỏ trỏ đến ISound 
    virtual ISoundPtr get_sound(const std::string& filename) = 0;

    // Destructor
    virtual ~ISoundAssetManager() {}
};

} // namespace tung

#endif
