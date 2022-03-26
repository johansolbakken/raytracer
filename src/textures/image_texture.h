//
// Created by Johan Solbakken on 26/03/2022.
//

#ifndef RAYTRACER_IMAGE_TEXTURE_H
#define RAYTRACER_IMAGE_TEXTURE_H

#include "common/core.h"
#include "texture.h"
#include "image/ray_tracer_stb_image.h"

#include <iostream>

namespace texture
{
    class ImageTexture : public Texture
    {
    public:
        ImageTexture() : m_Data(nullptr), m_Width(0), m_Height(0), m_BytesPerScanline(0)
        {}

        ImageTexture(const std::string& filename)
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

        ~ImageTexture()
        {
            delete m_Data;
        }

        Color Value(double u, double v, const Point3 &point) const override
        {
            // If we want no texture data, then return solid cyan as a debugging aid
            if (m_Data == nullptr)
                return {0,1,1};

            // Clamp input texture coordinates to [0,1] x [1,0]
            u = clamp(u, 0.0, 1.0);
            v = 1.0 - clamp(v, 0.0, 1.0);

            auto i = static_cast<int>(u * m_Width);
            auto j = static_cast<int>(v * m_Height);

            // Clamp integer mapping, since acutal coordinates should be less than 1.0
            if (i >= m_Width) i = m_Width - 1;
            if (j >= m_Height) i = m_Height - 1;

            constexpr auto color_scale = 1.0 / 255.0;
            auto pixel = m_Data + j * m_BytesPerScanline + i * s_BytesPerPixel;
            return {color_scale * pixel[0], color_scale * pixel[1], color_scale*pixel[2]};
        }

    private:
        uint8_t* m_Data;
        int32_t m_Width{}, m_Height{};
        int32_t m_BytesPerScanline{};

        constexpr static int s_BytesPerPixel = 3;
    };

}

#endif //RAYTRACER_IMAGE_TEXTURE_H
