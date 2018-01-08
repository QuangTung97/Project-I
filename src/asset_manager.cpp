#include <asset_manager.hpp>

namespace tung {

// Constructor
// Khởi tạo các tham chiếu đến ImageLoader, TextureFactory, SoundManager
AssetManager::AssetManager(
    IImageLoader& image_loader,
    ITextureFactory& texture_factory, 
    ISoundManager& sound_manager)
: image_loader_{image_loader}, texture_factory_{texture_factory},
    sound_manager_{sound_manager}
{}

IImagePtr AssetManager::get_image(const std::string& filename) {
    // Tìm iterator của ảnh chứa filename 
    auto find_it = images_.find(filename);
    // Nếu chưa có 
    if (find_it == images_.end()) {
        // Load hình ảnh lên từ file 
        auto image = image_loader_.load(filename);
        // Lưu trữ vào cache 
        images_[filename] = image;
        // Trả về ảnh 
        return image;
    }
    else {
        // Trả về ảnh 
        return find_it->second;
    }
}

ITexturePtr AssetManager::get_texture(const std::string& filename) {
    // Tìm iterator của texture chứa filename 
    auto find_it = textures_.find(filename);
    // Nếu chưa có 
    if (find_it == textures_.end()) {
        // Tạo texture từ ảnh 
        auto texture = texture_factory_.create(this->get_image(filename));
        // Lưu vào cache 
        textures_[filename] = texture;
        // Trả về
        return texture;
    }
    else {
        // Trả về texture 
        return find_it->second;
    }
}

ISoundPtr AssetManager::get_sound(const std::string& filename) {
    // Tìm iterator từ cache 
    auto find_it = sounds_.find(filename);
    // Nếu chưa tồn tại 
    if (find_it == sounds_.end()) {
        // Load nó lên từ file 
        auto sound = sound_manager_.load(filename);
        // Tạo một bản clone từ sound hiện tại 
        auto new_sound = sound->clone();
        // move bản vừa load vào cache 
        sounds_[filename] = std::move(sound);
        // Trả về bản vừa clone 
        return new_sound;
    }
    else {
        // Trả về bản clone của sound hiện tại 
        return find_it->second->clone();
    }
}

AssetManager::~AssetManager() {
}

} // namespace tung
