#include "material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(const char* filename){
    int width, height, channels;
    unsigned char* data  = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //UPLOAD DATA
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //FREE MEMORY
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Material::~Material(){
    glDeleteTextures(1, &texture);
}

void Material::use(){
    glBindTexture(GL_TEXTURE_2D, texture);
}