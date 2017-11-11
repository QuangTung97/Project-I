#ifndef GRAPHICS_GL_TEXT_MANAGER_HPP
#define GRAPHICS_GL_TEXT_MANAGER_HPP

#include <graphics/abstract/text_manager.hpp>
#include <graphics/abstract/object.hpp>
#include <tuple>
#include <unordered_map>
#include "text_factory.hpp"

namespace tung {

class TextManager: public ITextManager {
private:
    std::string font_;
    int size_;
    Color color_;

    ITextureFactory& texture_factory_;
    IVertexObjectBuilder& object_builder_;

    typedef std::tuple<std::string, unsigned char, 
        unsigned char, unsigned char> Key;
    typedef std::unique_ptr<TextFactory> Value;

    struct KeyHash {
        std::size_t operator() (const Key& k) const {
            std::hash<std::string> hash;
            return hash(std::get<0>(k)) 
                ^ std::get<1>(k) ^ std::get<2>(k) ^ std::get<3>(k);
        }
    };

    std::unordered_map<Key, Value, KeyHash> factories_;

    Key get_key() const ;

public:
    TextManager(ITextureFactory& texture_factory, 
        IVertexObjectBuilder& builder);

    void set_font(const std::string& font) override {
        font_ = font;
    }

    void set_font_size(int size) override {
        size_ = size;
    }

    void set_color(Color color) override {
        color_ = color;
    }

    void set_default_font() override;

    void set_default_font_size() override;
    
    void set_default_color() override;

    ITextPtr get_text(const std::string& text) override;

    virtual ~TextManager() {}
};

};

#endif