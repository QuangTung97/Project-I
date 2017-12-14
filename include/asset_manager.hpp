#ifndef GAME_ASSET_MANAGER_HPP
#define GAME_ASSET_MANAGER_HPP

#include <unordered_map>
#include <graphics/abstract/graphics_asset_manager.hpp>
#include <sound/abstract/sound_asset_manager.hpp>

namespace tung {

// Quản lý tài nguyên của hệ thống, Giúp cho việc dùng chung các tài nguyên. 
class AssetManager: public IGraphicsAssetManager, public ISoundAssetManager {
private:
    std::unordered_map<std::string, IImagePtr> images_;
    std::unordered_map<std::string, ITexturePtr> textures_;
    std::unordered_map<std::string, ISoundPtr> sounds_;

    IImageLoader& image_loader_;
    ITextureFactory& texture_factory_;
    ISoundManager& sound_manager_;

public:
    // Constructor
    // @image_loader: Image loader cần thiết để load ảnh 
    // @texture_factory: Texture Factory cần thiết để load texture. 
    // @sound_manager: Sound Manager cần thiết để load âm thanh. 
    AssetManager(IImageLoader& image_loader, 
        ITextureFactory& texture_factory, 
        ISoundManager& sound_manager);

    IImagePtr get_image(const std::string& filename) override;

    ITexturePtr get_texture(const std::string& filename) override;

    ISoundPtr get_sound(const std::string& filename) override;

    // Destructor 
    ~AssetManager();
};

}

#endif