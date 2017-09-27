#include "../abstract/texture.hpp"
#include "../abstract/shader.hpp"

namespace tung {

class Texture: public ITexture {
private:
    unsigned int texture_;

    friend class TextureFactory;

public:
    void bind(
            unsigned int active_number, int location) override;

    virtual ~Texture();
};

class TextureFactory: public ITextureFactory {
public:
    TextureFactory();

    ITexturePtr create(const IImagePtr& image) override;

    virtual ~TextureFactory();
};

} // namespace tung
