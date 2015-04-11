//
//  GB2ShapeCache-x.cpp
//  
//  Loads physics sprites created with http://www.PhysicsEditor.de
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//      http://www.PhysicsEditor.de
//      http://texturepacker.com
//      http://www.code-and-web.de
//  
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "GB2ShapeCache-x.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
    : next(NULL) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }
    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
	BodyDef()
	: fixtures(NULL) {}
	
	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}
	
	FixtureDef *fixtures;
	Point anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::getInstance(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}
	
	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *so = (*pos).second;

	FixtureDef *fix = so->fixtures;
    while (fix) {
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

cocos2d::Point GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

typedef ValueMap ObjectDict;

void GB2ShapeCache::addShapesWithFile(const std::string &plist)
{
	std::string fullName = FileUtils::getInstance()->fullPathForFilename(plist.c_str());
	ObjectDict dictionary = FileUtils::getInstance()->getValueMapFromFile(fullName);
	CCAssert(&dictionary != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
  
	
	//decode the plist file
	int format = 0;
	// get the format
	if (dictionary.find("metadata") != dictionary.end())
	{
		ValueMap& metadataDict = dictionary["metadata"].asValueMap();
		format = metadataDict["format"].asInt();
		ptmRatio = metadataDict["ptm_ratio"].asFloat();
	}
   
	CCAssert(format == 1, "Format not supported");

	ObjectDict& bodyDict = dictionary["bodies"].asValueMap();

    b2Vec2 vertices[b2_maxPolygonVertices];

	std::string bodyName;

	for (auto iter = bodyDict.begin(); iter != bodyDict.end(); ++iter)
	{
		bodyName = iter->first;
		ValueMap& dataDict = iter->second.asValueMap();
		BodyDef *bodyDef = new BodyDef();
		bodyDef->anchorPoint = PointFromString(dataDict["anchorpoint"].asString());

		ValueVector& fixtureVector = dataDict["fixtures"].asValueVector();

		FixtureDef **nextFixtureDef = &(bodyDef->fixtures);
		//fixture
		for (auto iter = fixtureVector.begin(); iter != fixtureVector.end(); ++iter)
		{
			ValueMap& fixtureDict = (ValueMap&)(*iter).asValueMap();
			b2FixtureDef basicData;
			basicData.filter.categoryBits = fixtureDict["filter_categoryBits"].asInt();
			basicData.filter.maskBits = fixtureDict["filter_maskBits"].asInt(); 
			basicData.filter.groupIndex = fixtureDict["filter_groupIndex"].asInt();
			basicData.friction = fixtureDict["friction"].asFloat();
			basicData.density = fixtureDict["density"].asFloat();
			basicData.restitution = fixtureDict["restitution"].asFloat();
			basicData.isSensor = fixtureDict["isSensor"].asBool();
			int callbackData = fixtureDict["userdataCbValue"].asInt();

	
			std::string fixtureType = fixtureDict["fixture_type"].asString();
			if (fixtureType == "POLYGON")
			{
				ValueVector& polygonsVector = (fixtureDict["polygons"].asValueVector());
				for (auto iter = polygonsVector.begin(); iter != polygonsVector.end(); ++iter)
				{
					FixtureDef *fix = new FixtureDef();
					fix->fixture = basicData; // copy basic data
					fix->callbackData = callbackData;
					b2PolygonShape *polyshape = new b2PolygonShape();
					int vindex = 0;

					ValueVector polygonArray = (*iter).asValueVector();
					
					for (auto piter = polygonArray.begin(); piter != polygonArray.end(); ++piter) 
					{
						Point offset = PointFromString(piter->asString());
						vertices[vindex].x = (offset.x / ptmRatio);
						vertices[vindex].y = (offset.y / ptmRatio);
						vindex++;
					}
					polyshape->Set(vertices, vindex);
					fix->fixture.shape = polyshape;
					// create a list
					*nextFixtureDef = fix;
					nextFixtureDef = &(fix->next);
				}
			}
			else if (fixtureType == "CIRCLE") 
			{
				FixtureDef *fix = new FixtureDef();
				fix->fixture = basicData; // copy basic data
				fix->callbackData = callbackData;

				ValueMap& circleData = (fixtureDict["circle"].asValueMap());

				b2CircleShape *circleShape = new b2CircleShape();

				circleShape->m_radius = circleData["radius"].asFloat() / ptmRatio;
				Point p = PointFromString(circleData["position"].asString());
				circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
				fix->fixture.shape = circleShape;

				// create a list
				*nextFixtureDef = fix;
				nextFixtureDef = &(fix->next);

			}
			else 
			{
				CCAssert(0, "Unknown fixtureType");
			}

			// add the body element to the hash
			shapeObjects[bodyName] = bodyDef;

		}
	}
				
}