#ifndef VIEW_ABSTRACT_KEY_BUTTON_HPP
#define VIEW_ABSTRACT_KEY_BUTTON_HPP

#include <bitset>

namespace tung {

// enum đại diện nút trên bàn phím đã ấn 
enum class KeyButton {
    ENTER,
    SPACE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// enum đại diện cách ấn nút trên bàn phím 
enum class KeyType {
    UP,
    DOWN
};

typedef std::bitset<4> KeyModifier;

// enum đại diện cho từng loại nút modifier đã ấn
enum class KeyMod {
    SHIFT = 0,
    CONTROL = 1, 
    ALT = 2,
    SUPER = 3,
};

// Một sự kiện bàn phím bao gồm nút đã ấn, cách ấn nút và các nút modifier 
class KeyEvent {
private:
    const KeyButton button_;
    const KeyType type_;
    const KeyModifier mods_;

public:
    KeyEvent(KeyButton button, KeyType type, KeyModifier mods) 
    : button_{button}, type_{type}, mods_{mods} {}

    KeyButton button() const { return button_; }
    
    KeyType type() const { return type_; }

    bool shift() const { return mods_[static_cast<size_t>(KeyMod::SHIFT)]; }

    bool ctrl() const { return mods_[static_cast<size_t>(KeyMod::CONTROL)]; }

    bool alt() const { return mods_[static_cast<size_t>(KeyMod::ALT)]; }

    bool super() const { return mods_[static_cast<size_t>(KeyMod::SUPER)]; }
};

} // namespace tung

#endif