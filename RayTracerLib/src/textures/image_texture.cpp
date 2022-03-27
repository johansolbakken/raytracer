//
// Created by Johan Solbakken on 26/03/2022.
//

#include "textures/image_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace texture
{
    ImageTexture::ImageTexture(const std::string& filename)
    {
        auto components_per_pixel = s_BytesPerPixel;

        m_Data = stbi_load(filename.c_str(), &m_Width, &m_Height, &components_per_pixel, components_per_pixel);

        if (!m_Data)
        {
            std::cerr << "ERROR: Failed to load image!" << std::endl;
            m_Width = m_Height = 0;
        }

        m_BytesPerScanline = s_BytesPerPixel * m_Width;
    }
}