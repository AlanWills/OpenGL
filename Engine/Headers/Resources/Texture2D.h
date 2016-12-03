#pragma once

#include "GLHeaders.h"
#include "DllExport.h"

#include <string>

namespace Engine
{

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class DllExport Texture2D
{
  public:
    // Constructor (sets default texture modes)
    Texture2D();
    ~Texture2D();

    // Generates texture from image data
    void generate(GLuint width, GLuint height, unsigned char* data);

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;
    void unbind() const;

    void setInternalFormat(GLuint internalFormat) { m_internalFormat = internalFormat; }
    void setImageFormat(GLuint imageFormat) { m_imageFormat = imageFormat; }

  private:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint m_textureHandle;

    // Texture image dimensions
    GLuint m_width, m_height;   // Width and height of loaded image in pixels

    // Texture Format
    GLuint m_internalFormat;     // Format of texture object
    GLuint m_imageFormat;        // Format of loaded image

    // Texture configuration
    GLuint m_wrap_S;              // Wrapping mode on S axis
    GLuint m_wrap_T;              // Wrapping mode on T axis
    GLuint m_filter_Min;          // Filtering mode if texture pixels < screen pixels
    GLuint m_filter_Max;          // Filtering mode if texture pixels > screen pixels
};

};