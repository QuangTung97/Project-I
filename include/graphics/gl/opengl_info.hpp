#ifndef GL_INFO
#define GL_INFO

#include <string>
#include <iostream>

namespace tung {

// Class nhằm lấy thông tin OpengGL của hệ thống 
class OpenGLInfo {
private:
    std::string renderer;
    std::string version;

public:
    // Constructor
    OpenGLInfo();

    // Return: lấy renderer của hệ thống. 
    const std::string &get_renderer() const;

    // Return: lấy OpenGL version của hệ thống. 
    const std::string &get_version() const;
};

// @info: object OpenGLInfo. 
// In ra renderer và version. 
std::ostream& operator << (std::ostream& out, 
        const OpenGLInfo& info);

} // namespace tung

#endif // GL_INFO
