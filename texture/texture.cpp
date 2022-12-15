#include "texture.h"

void Texture::readImage(const char *path, int &image_w, int &image_h, int &pixel_l) {
    GLubyte *pixel_data;
    FILE *p_file;
    p_file = fopen(path, "rb");
    if (p_file == nullptr) {
        exit(0);
    }
    fseek(p_file, 0x0012, SEEK_SET);
    fread(&image_w, sizeof(image_w), 1, p_file);
    fread(&image_h, sizeof(image_h), 1, p_file);
    pixel_l = image_w * 3;
    while (pixel_l % 4 != 0) {
        pixel_l++;
    }
    pixel_l *= image_h;
    pixel_data = (GLubyte *) malloc(pixel_l);
    if (pixel_data == nullptr) {
        exit(0);
    }
    fseek(p_file, 54, SEEK_SET);
    fread(pixel_data, pixel_l, 1, p_file);
    p.push_back(pixel_data);
    fclose(p_file);
}

void Texture::loadTexture() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    glEnable(GL_TEXTURE_2D);
    this->readImage("../cloth.bmp", this->image_width, this->image_height, this->pixel_length);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]); // target to which texture is bound and name of a texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image_width, image_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}
