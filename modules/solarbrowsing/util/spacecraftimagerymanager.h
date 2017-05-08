/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2017                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __OPENSPACE_MODULE_SOLARBROWSING___SPACECRAFTIMAGERYMANAGER___H__
#define __OPENSPACE_MODULE_SOLARBROWSING___SPACECRAFTIMAGERYMANAGER___H__

#include <ghoul/designpattern/singleton.h>
#include <memory>
#include <vector>
#include <valarray>
#include <unordered_map>

#define IMG_PRECISION unsigned char

// TODO List:
// 1. Read headerinfo properly
// 2. Test with 4k images
// 3. Colorize

namespace ghoul { namespace opengl { class Texture; }}

namespace openspace {

class TransferFunction;

// struct ImageMetadata {
//     std::string filename;
//     int min;
//     int max;
//     int waveLength;
//     float expTime;
//     double timeObserved;
// };

// struct ImageDataObject {
//     ImageMetadata metaData;
//     std::valarray<IMG_PRECISION> contents;

//     bool operator<(const double val) const {
//         return (metaData.timeObserved < val);
//     }
// };

struct ImageMetadata {
    double timeObserved;
    std::string filename;

    bool operator<(const double val) const {
        return timeObserved < val;
    }
};


class SpacecraftImageryManager : public ghoul::Singleton<SpacecraftImageryManager> {
    friend class ghoul::Singleton<SpacecraftImageryManager>;

public:
    SpacecraftImageryManager();
    void ConvertTileJ2kImages(const std::string& path, const unsigned int tileWidth,
                              const unsigned int tileHeight);
    // std::vector<ImageDataObject> loadImageData(const std::string& path, int&
    // imageSize);
    void loadTransferFunctions(
    const std::string& path,
    std::unordered_map<std::string, std::unique_ptr<TransferFunction>>& _tfMap);
    std::vector<ImageMetadata> loadImageMetadata(const std::string& path);
    void loadImageMetadata(
          const std::string& path,
          std::unordered_map<std::string, std::vector<ImageMetadata>>&
                _imageMetadataMap);  // std::vector<std::unique_ptr<ghoul::opengl::Texture>>
    // loadTextures(std::vector<ImageDataObject>& imageData);
    std::unique_ptr<ghoul::opengl::Texture> createLUT();
    //void scaleImageData(std::vector<ImageDataObject>& _imageData, const std::string& type, const int& channel);
private:
    void fetchServerImages(std::string type);
    void fillImageryInfo(std::string buffer, std::string type);
    //void fetchLatestImage(std::string& url);
    //fetchLocalPlaneTexturesAndStoreInMap();
    //preProcessImageData();
    //postProcessTexture();
    //startFetchingCycle();
};

} //namespace openspace

#endif // __OPENSPACE_MODULE_SOLARBROWSING___SPACECRAFTIMAGERYMANAGER___H__
