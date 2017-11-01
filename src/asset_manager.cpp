#include <asset_manager.hpp>

namespace tung {

AssetManager::AssetManager(
    IImageLoader& image_loader,
    ITextureFactory& texture_factory, 
    ISoundManager& sound_manager)
: image_loader_{image_loader}, texture_factory_{texture_factory},
    sound_manager_{sound_manager}
{}

IImagePtr AssetManager::get_image(const std::string& filename) {
    auto find_it = images_.find(filename);
    if (find_it == images_.end()) {
        auto image = image_loader_.load(filename);
        images_[filename] = image;
        return std::move(image);
    }
    else {
        return find_it->second;
    }
}

ITexturePtr AssetManager::get_texture(const std::string& filename) {
    auto find_it = textures_.find(filename);
    if (find_it == textures_.end()) {
        auto texture = texture_factory_.create(this->get_image(filename));
        textures_[filename] = texture;
        return std::move(texture);
    }
    else {
        return find_it->second;
    }
}

ISoundPtr AssetManager::get_sound(const std::string& filename) {
    auto find_it = sounds_.find(filename);
    if (find_it == sounds_.end()) {
        auto sound = sound_manager_.load(filename);
        auto new_sound = sound->clone();
        sounds_[filename] = std::move(sound);
        return std::move(new_sound);
    }
    else {
        return find_it->second->clone();
    }
}

AssetManager::~AssetManager() {
}

} // namespace tung