#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <graphics/abstract/shader_program.hpp>
#include <vector>

namespace tung {

// class chứa thông tin lỗi khi load chương trình shader
class ShaderException: public std::exception {
private:
    std::string message_;
public:
    // Constructor
    // @message: Thông tin chi tiết của lỗi 
    ShaderException(std::string message) {
        message_ = std::move(message);
    }

    // Return: thông tin chi tiết của lỗi. 
    virtual const char *what() const noexcept override {
        return message_.c_str();
    }
};

// Base class
// Kế thừa từ graphics/abstract/shader_program.hpp
class ShaderProgram: public IShaderProgram {
public:
    void predraw(float width, float height) override;

    void draw() override;

    void postdraw() override;

    void set_drawable(const IDrawablePtr& drawable) override;

    std::vector<glm::mat4>& model_matrix_stack() override;

protected:
    std::unordered_map<std::string, int> locations_;
    GLuint program_ = -1;

protected:
    ShaderProgram();

    // input streams for read vertex shader and fragment shader
    // @vs: input stream tới file chứa vertex shader
    // @fs: input stream tới file chứa fragment shader
    // Tạo chương trình shader. 
    void make_program(std::istream& vs, std::istream& fs);

    ~ShaderProgram();

private:
    // @vs: nội dung (dưới dạng code) của vertex shader
    // @fs: nội dung (dưới dạng code) của fragment shader
    // Linh vertex shader với fragment shader để tạo nên chương trình shader. 
    void create_and_link(const char *vs, const char *fs);

    IDrawablePtr drawable_;
    std::vector<glm::mat4> model_matrix_stack_;
};

} // namespace tung

#endif
