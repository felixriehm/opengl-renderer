//
// Created by Felix on 13/10/2021.
//

#include "Texture.h"
#include <glew/glew.h>

Texture::Texture()
        : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::SetTextureWrapping(int i) {


    switch (i) {
        case 0:
            Wrap_T = GL_REPEAT;
            Wrap_S = GL_REPEAT;
            break;
        case 1:
            Wrap_T = GL_MIRRORED_REPEAT;
            Wrap_S = GL_MIRRORED_REPEAT;
            break;
        case 2:
            Wrap_T = GL_CLAMP_TO_EDGE;
            Wrap_S = GL_CLAMP_TO_EDGE;
            break;
        case 3:
            Wrap_T = GL_CLAMP_TO_BORDER;
            Wrap_S = GL_CLAMP_TO_BORDER;
            break;
        default:
            break;
    }

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
}

void Texture::SetTextureWrappingBorderColor(float borderColor[]){
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}

void Texture::SetTextureFiltering(int i) {

    switch (i) {
        case 0:
            Filter_Min = GL_LINEAR;
            Filter_Max = GL_LINEAR;
            break;
        case 1:
            Filter_Min = GL_NEAREST;
            Filter_Max = GL_NEAREST;
            break;
        default:
            break;
    }

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
}
