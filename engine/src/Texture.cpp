#include "Texture.h"

Texture::Texture() {
    index = 0;
}

Texture::~Texture() {
    if (index != 0)
        glDeleteTextures( 1, &index);
}

GLuint Texture::createTexture(GLenum target, int w, int h, void *data) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(target, tex);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps(target, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
    return tex;
}
