#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <memory>
#include "image.h"

namespace tung {

struct ITexture {
    virtual void bind(
            unsigned int active_number, int location) = 0;

    virtual ~ITexture() {}
};

typedef std::shared_ptr<ITexture> ITexturePtr;

struct ITextureFactory {
    // Create bindable texture
    // @image: image had read
    virtual ITexturePtr create(const IImagePtr& image) = 0;

    virtual ~ITextureFactory() {}
};

} // namespace tung

#endif
