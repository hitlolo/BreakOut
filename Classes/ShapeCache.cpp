#include "ShapeCache.h"

ShapeCache* ShapeCache::_ShapeCache = nullptr;

ShapeCache* ShapeCache::getInstance(void)
{
	if (!_ShapeCache)
	{
		_ShapeCache = new ShapeCache();

		return _ShapeCache;
	}
	else
		return _ShapeCache;

}

ShapeCache::~ShapeCache()
{
	CC_SAFE_DELETE(_ShapeCache);
}

void ShapeCache::addShapesWithFile(const std::string &plist, PhysicsBody *body)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
	
	initShapesWithDictionary(dict, body);

}



void ShapeCache::initShapesWithDictionary(ValueMap &dictionary, PhysicsBody *body)
{
	//decode the plist file
	int format = 0;
	// get the format
	if (dictionary.find("metadata") != dictionary.end())
	{
		ValueMap& metadataDict = dictionary["metadata"].asValueMap();
		format = metadataDict["format"].asInt();
	}
	// check the format
	CCASSERT(format == 1, "format is not supported for #addShapesWithDictionary#:");

	ValueMap& bodyDict = dictionary["bodies"].asValueMap();

	for (auto iter = bodyDict.begin(); iter != bodyDict.end(); ++iter)
	{
		ValueMap& dataDict = iter->second.asValueMap();

		/****************not used yet!***********************/
		//set anchorpoint	
		//Point anchorPoint = PointFromString(dataDict["anchorpoint"].asString());
	
		ValueVector& fixtureVector = dataDict["fixtures"].asValueVector();

		for (auto iter = fixtureVector.begin(); iter != fixtureVector.end(); ++iter)
		{
			ValueMap& fixtureDict =(ValueMap&)(*iter).asValueMap();
	/*		float friction    = fixtureDict["friction"].asFloat();
			float density     = fixtureDict["density"].asFloat();
			float restitution = fixtureDict["restitution"].asFloat();*/
			/****************not used yet!***********************/

			/* //body->setCategoryBitmask(fixtureDict["filter_categoryBits"].asInt);
			/* //body->setCollisionBitmask(fixtureDict["filter_maskBits"].asInt);
			/* //body->setGroup(fixtureDict["filter_groupIndex"].asInt);

			
			/* //int   isSensor    = fixtureDict["isSensor"].asInt;
			/* //std::string userdata = fixtureDict["userdataCbValue"].asString;
			/* 
			/* //
			/* 
			
			/****************not used yet!***********************/
		/*	std::string fixtureType = fixtureDict["fixture_type"].asString();
			if (fixtureType == "POLYGON")
			{*/
				ValueVector& polygonsVector = (fixtureDict["polygons"].asValueVector());

				for (auto iter = polygonsVector.begin(); iter != polygonsVector.end(); ++iter)
				{
					int vertexNum = (*iter).asValueVector().size();;
					ValueVector polygonArray = (*iter).asValueVector();
					Point *polyVertex = new Point[vertexNum];
					int i = 0;
					for (auto piter = polygonArray.begin(); piter != polygonArray.end(), i < vertexNum; ++piter, i++)
					{
						Point vertex = PointFromString((*piter).asString());
						polyVertex[i] = vertex;
					}
					body->addShape(PhysicsShapePolygon::create(polyVertex, vertexNum));
					CC_SAFE_DELETE_ARRAY(polyVertex);
				}
			}
		//}
		//	else if (fixtureType == "CIRCLE") 
		//	{

		//		continue;
		//		//ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");

		//		//b2CircleShape *circleShape = new b2CircleShape();

		//		//circleShape->m_radius = static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
		//		//CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
		//		//circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
		//		//fix->fixture.shape = circleShape;

		//		//// create a list
		//		//*nextFixtureDef = fix;
		//		//nextFixtureDef = &(fix->next);

		//	}
		//	else 
		//	{
		//		CCAssert(0, "Unknown fixtureType");
		//	}
		//}
	}
}