
#ifndef BREAK_OUT_SHAPE
#define BREAK_OUT_SHAPE

#include "cocos2d.h"

USING_NS_CC;

class ShapeCache {

public:
	static ShapeCache* getInstance(void);

	void addShapesWithFile(const std::string &plist, PhysicsBody *body);

private:

	static ShapeCache* _ShapeCache;

	void initShapesWithDictionary(ValueMap&, PhysicsBody*);

	~ShapeCache();

};


#endif