#include "pngWriter.h"

void Png::WritePngToFile(std::string location, std::string fileName)
{
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (unsigned y = 0; y < height; y++)
        for (unsigned x = 0; x < width; x++) {
            image[4 * width * y + 4 * x + 0] = (char)img[x + width * y].r;
            image[4 * width * y + 4 * x + 1] = (char)img[x + width * y].g;
            image[4 * width * y + 4 * x + 2] = (char)img[x + width * y].b;
            image[4 * width * y + 4 * x + 3] = (char)img[x + width * y].a;
        }
    std::string endLoc = location + fileName;
    lodepng::encode(endLoc.c_str(), image, width, height);
}

Png::Png(unsigned int _width, unsigned int _height)
{
    width = _width;
    height = _height;
    img.resize(width * height);
}