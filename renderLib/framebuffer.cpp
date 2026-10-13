#include "vec3.h"
#include "framebuffer.h"
#include "png++/png.hpp"
#include "color.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>


Framebuffer::Framebuffer()
    : imageWidth(0), imageHeight(0)
{
}

Framebuffer::Framebuffer(int width, int height)
{
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Framebuffer dimensions must be positive");
    }

    const auto storageWidth = static_cast<std::size_t>(width);
    const auto storageHeight = static_cast<std::size_t>(height);
    if (storageWidth > fbStorage.max_size() / storageHeight) {
        throw std::length_error("Framebuffer dimensions exceed storage capacity");
    }

    imageWidth = width;
    imageHeight = height;
    fbStorage.resize(storageWidth * storageHeight);
}

int Framebuffer::getImageWidth() const
{
    return imageWidth;
}

int Framebuffer::getImageHeight() const
{
    return imageHeight;
}

void Framebuffer::clear(Vec3 c)
{
    std::fill(fbStorage.begin(), fbStorage.end(), c);
}

Vec3 Framebuffer::lerp(const Vec3& c1, const Vec3& c2, double t)
{
    Vec3 c = (1-t) * c1 + t * c2;
    return c;
}


void Framebuffer::gradientTB(const Vec3& c1,const  Vec3& c2)
{
    for (int y = 0; y < imageHeight; ++y) {
        const double t = static_cast<double>(y) / imageHeight;
        const Vec3 color = lerp(c1, c2, t);
        const auto rowStart = fbStorage.begin() + static_cast<std::size_t>(y) * imageWidth;
        std::fill_n(rowStart, imageWidth, color);
    }
}

void Framebuffer::gradientLR(const Vec3& c1,const  Vec3& c2)
{
    for (int y = 0; y < imageHeight; ++y) {
        const auto rowStart = static_cast<std::size_t>(y) * imageWidth;
        for (int x = 0; x < imageWidth; ++x) {
            const double t = static_cast<double>(x) / imageWidth;
            fbStorage[rowStart + x] = lerp(c1, c2, t);
        }
    }
}


void Framebuffer::colorArrayTB(std::vector<Vec3> cArr)
{
    if (cArr.empty()) {
        return;
    }

    const std::size_t colorCount = cArr.size();
    for (int y = 0; y < imageHeight; ++y) {
        const std::size_t colorIndex =
            static_cast<std::size_t>(y) * colorCount / static_cast<std::size_t>(imageHeight);
        const auto rowStart = fbStorage.begin() + static_cast<std::size_t>(y) * imageWidth;
        std::fill_n(rowStart, imageWidth, cArr[colorIndex]);
    }
}

void Framebuffer::setPixelColor(int width, int height, const Vec3 &c)
{
    if (width < 0 || width >= imageWidth || height < 0 || height >= imageHeight) {
        throw std::out_of_range("Pixel coordinates are outside the framebuffer");
    }
    fbStorage[static_cast<std::size_t>(height) * imageWidth + width] = c;
}


void Framebuffer::exportAsPNG(std::string filename)
{
    if (imageWidth <= 0 || imageHeight <= 0) {
        throw std::logic_error("Cannot export an empty framebuffer");
    }

    png::image<png::rgb_pixel> imageData(imageWidth, imageHeight);
    const auto toByte = [](double component) {
        if (!std::isfinite(component)) {
            return static_cast<png::byte>(0);
        }
        return static_cast<png::byte>(255.999 * std::clamp(component, 0.0, 1.0));
    };
    for (int y = 0; y < imageHeight; ++y) {
        const auto rowStart = static_cast<std::size_t>(y) * imageWidth;
        for (int x = 0; x < imageWidth; ++x) {
            const Vec3& color = fbStorage[rowStart + x];
            imageData[y][x] = png::rgb_pixel(
                toByte(color.x()),
                toByte(color.y()),
                toByte(color.z())
            );
        }
    }
    imageData.write(filename);
}