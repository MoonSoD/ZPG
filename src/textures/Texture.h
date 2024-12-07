#include <GL/glew.h>
#include <string>


class Texture {
private:
    GLuint id;
public:
    Texture(const std::string& fileName);

    void bind();
};