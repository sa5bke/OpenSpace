/*****************************************************************************************
*                                                                                       *
* OpenSpace                                                                             *
*                                                                                       *
* Copyright (c) 2014-2016                                                               *
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

#ifndef __CHUNK_LOD_GLOBE__
#define __CHUNK_LOD_GLOBE__

#include <memory>


#include <ghoul/logging/logmanager.h>


// open space includes
#include <openspace/rendering/renderengine.h>
#include <openspace/rendering/renderable.h>
#include <openspace/properties/stringproperty.h>
#include <openspace/util/updatestructures.h>



#include <modules/globebrowsing/datastructures/chunknode.h>
#include <modules/globebrowsing/rendering/patchrenderer.h>

namespace ghoul {
	namespace opengl {
		class ProgramObject;
	}
}

namespace openspace {

	class ChunkLodGlobe : 
		public Renderable, public std::enable_shared_from_this<ChunkLodGlobe>{
	public:
		ChunkLodGlobe(const ghoul::Dictionary& dictionary);
		~ChunkLodGlobe();

		PatchRenderer& getPatchRenderer();

		bool initialize() override;
		bool deinitialize() override;
		bool isReady() const override;

		void render(const RenderData& data) override;
		void update(const UpdateData& data) override;

		double minDistToCamera;

		const Scalar globeRadius;

		const int minSplitDepth;
		const int maxSplitDepth;


	private:		

		// Covers all negative longitudes
		std::unique_ptr<ChunkNode> _leftRoot;

		// Covers all positive longitudes
		std::unique_ptr<ChunkNode> _rightRoot;

		// the patch used for actual rendering
		std::unique_ptr<PatchRenderer> _patchRenderer;

		
		static const LatLonPatch LEFT_HEMISPHERE;
		static const LatLonPatch RIGHT_HEMISPHERE;

		properties::IntProperty _rotation;

		glm::dmat3 _stateMatrix;
		std::string _frame;
		std::string _target;
		double _time;
	};

}  // namespace openspace

#endif  // __CHUNK_LOD_GLOBE__