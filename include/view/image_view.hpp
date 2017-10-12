#ifndef VIEW_IMAGE_VIEW_HPP
#define VIEW_IMAGE_VIEW_HPP

#include <view/view.hpp>
#include <graphics/abstract/image.hpp>

namespace tung {

class ImageView: public View {
protected:
public:
    ImageView(float x, float y, float width, float height, 
            const IImagePtr& image);

};

} // namespace tung

#endif
