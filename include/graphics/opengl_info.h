#ifndef GL_INFO
#define GL_INFO

#include <string>
#include <iostream>

namespace tung {

class OpenGLInfo {
private:
    std::string renderer;
    std::string version;

public:
    OpenGLInfo();

    const std::string &get_renderer() const;
    const std::string &get_version() const;
};

std::ostream& operator << (std::ostream& out, 
        const OpenGLInfo& info);

} // namespace tung

#endif // GL_INFO
