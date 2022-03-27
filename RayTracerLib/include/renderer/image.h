#pragma once

#include "../vector/vec3.h"

#include <vector>

namespace Renderer
{
    class Image
    {
    public:
        Image(int width, double aspect_ratio)
        : m_Colors(width * static_cast<int>(width / aspect_ratio), {0.0,0.0,0.0})
        {
            m_Width = width;
            m_Height = static_cast<size_t>(width / aspect_ratio);
        }

        inline size_t GetWidth() const { return m_Width; }
        inline size_t GetHeight() const { return m_Height; }
        inline size_t GetSize() const { return m_Width * m_Height; }
        inline const Color* Data() const { return m_Colors.data(); }
        inline void WriteColor(size_t x, size_t y, Color color) { m_Colors[x + y * m_Height] = color; }

        ~Image()
        {
            delete m_Buffer;
        }

        
    private:
        Color* m_Buffer;
        std::vector<Color> m_Colors;
        size_t m_Width;
        size_t m_Height;
    };
}