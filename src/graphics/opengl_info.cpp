#include <graphics/opengl_info.h>
#include <GL/glew.h>

tung::OpenGLInfo::OpenGLInfo() {
	// get version info
	renderer = (const char *)glGetString(GL_RENDERER);
	version = (const char *)glGetString(GL_VERSION);
	// printf("Renderer: %s\n", renderer);
	// printf("OpenGL version supported %s\n", version);
}

const std::string& tung::OpenGLInfo::get_renderer() const {
    return renderer;
}

const std::string& tung::OpenGLInfo::get_version() const {
    return version;
}

std::ostream& tung::operator << (std::ostream& out, 
        const OpenGLInfo& info) {
    out << "Renderer: " << info.get_renderer() << "\n";
    out << "OpenGL version supported: " 
        << info.get_version();
    return out;
}
