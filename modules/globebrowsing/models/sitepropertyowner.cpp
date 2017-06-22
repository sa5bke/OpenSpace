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

#include <modules/globebrowsing/models/sitepropertyowner.h>
#include <modules/globebrowsing/models/drivepropertyowner.h>

namespace {
	const std::string _loggerCat = "SitePropertyOwner";
}

namespace openspace {
namespace globebrowsing {
SitePropertyOwner::SitePropertyOwner(SiteWithDrives swd) 
	: properties::PropertyOwner("Site" + swd._site)
	, _enabled(properties::BoolProperty("siteEnabled", "Site enabled", false))
{
	_site = swd._site;
	int i = 0;
	for (auto k : swd._drives) {
		_drivePropertyOwner.push_back(std::make_shared<DrivePropertyOwner>(k, swd.sols.at(i), swd._driveCoords.at(i)));
		i++;
	}

	for (auto k : _drivePropertyOwner) {
		addPropertySubOwner(k.get());
	}

	addProperty(_enabled);	
}

void SitePropertyOwner::addDrive(std::string drive) {
	_drives.push_back(drive);
}

}
}
