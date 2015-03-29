#include "ShatterSprite.h"

ShatterSprite* ShatterSprite::create(std::vector<b2Vec2> vertices, Sprite *sprite)
{
	ShatterSprite *shatter = new (std::nothrow) ShatterSprite(vertices, sprite);
	if (shatter && shatter->init(sprite))
	{
		shatter->autorelease();
		return shatter;
	}
	CC_SAFE_DELETE(shatter);

	
	
	return nullptr;
}

bool ShatterSprite::init(Sprite *sprite)
{
	if (!Sprite::initWithSpriteFrame(sprite->getSpriteFrame()))
	{
		return false;
	}
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
//	auto action = RotateBy::create(1.0f, -90);
//	auto s = RepeatForever::create(action);
//	this->runAction(s);

	setVerticesAndCoords();
	return true;
}

ShatterSprite::ShatterSprite(std::vector<b2Vec2> vertices, Sprite* sprite)
{
	this->poly_data = vertices;
	this->poly_count = vertices.size();
	this->originSprite = sprite;
}

ShatterSprite::~ShatterSprite()
{

}

void ShatterSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	
	//Sprite::draw(renderer, transform, flags);
#if CC_USE_CULLING
	// Don't do calculate the culling if the transform was not updated
	_insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;

	if (_insideBounds)
#endif
	{
		_transformUpdated = _transformDirty = _inverseDirty = true;
		//setDirtyRecursively(true);
		//setNodeToParentTransform(_transform);
		_transform.set(transform);
		command.init(_globalZOrder, transform, flags);
		command.func = std::bind(&ShatterSprite::onDraw, this);
		renderer->addCommand(&command);

#if CC_SPRITE_DEBUG_DRAW
		_debugDrawNode->clear();
		Vec2 vertices[4] = {
			Vec2(_quad.bl.vertices.x, _quad.bl.vertices.y),
			Vec2(_quad.br.vertices.x, _quad.br.vertices.y),
			Vec2(_quad.tr.vertices.x, _quad.tr.vertices.y),
			Vec2(_quad.tl.vertices.x, _quad.tl.vertices.y),
		};
		_debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
#endif //CC_SPRITE_DEBUG_DRAW
	}
}

void ShatterSprite::setVerticesAndCoords()
{
	float vertercies[] =
	{
		0, 0,
		49, 0,   //第二个点的坐标
		0, 49,
		0, 49,
		49, 49,
		49, 0
	};

	float coord[] = {
		0.214844, 0.838867,    //第一个点的颜色，绿色
		0.406250, 0.838867,  //第二个点的颜色, 红色
		0.214844, 0.791016,
		0.214844, 0.791016,
		0.406250, 0.791016,
		0.406250, 0.838867
	};

	vertices = new V2F_C4F_T2F[poly_data.size()];
	for (int i = 0, j = 0, k = 0; i < poly_data.size(); i++)
	{
		//vertices[i].vertices.x = vertercies[j++];
		//vertices[i].vertices.y = vertercies[j++];
		vertices[i].vertices.x = poly_data[i].x *PTM_RATIO;
		vertices[i].vertices.y = poly_data[i].y *PTM_RATIO;

		vertices[i].texCoords.u = coord[k++];
		vertices[i].texCoords.v = coord[k++];
	}

	//CCPoint ap = originSprite->getAnchorPoint();
	//unsigned long ow = csx->getTexture()->getContentSize().width;
	//ow *= ap.x;
	//unsigned long oh = csx->getTexture()->getContentSize().height;
	//oh *= ap.y;
	//for (int i = 0; i<numVertices; i++)
	//{
	//	b2Vec2 v = poly->GetVertex(i);
	//	points[i].x = v.x*metor / scalex + ow;
	//	points[i].y = v.y*metor / scaley + oh;
	//}
}

void ShatterSprite::onDraw()
{
	
	auto glProgram = getGLProgram();	
	glProgram->use();
	//glProgram->setUniformsForBuiltins(_modelViewTransform);
	glProgram->setUniformsForBuiltins(_transform);

	//激活名字为position和color的vertex attribute
	//Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	//分别给position和color指定数据源
	glBindTexture(GL_TEXTURE_2D, this->_texture->getName());
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4F_T2F), &vertices->vertices);
//	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4F_T2F), &vertices->texCoords);
//	glVertexPointer(2, GL_FLOAT, 0, vertercies);
//glTexCoordPointer(2, GL_FLOAT, 0, coord);

	//绘制三角形，所谓的draw call就是指这个函数调用
	glDrawArrays(GL_TRIANGLE_FAN, 0, poly_data.size());
	//通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令
//	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
	//如果出错了，可以使用这个函数来获取出错信息
//	CHECK_GL_ERROR_DEBUG();
//	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	//CCLOG("%f,%f bl vertices", this->_quad.bl.vertices.x, this->_quad.bl.vertices.y);
	//CCLOG("%f,%f bl coords", this->_quad.bl.texCoords.u, this->_quad.bl.texCoords.v);

	//CCLOG("%f,%f br vertices", this->_quad.br.vertices.x, this->_quad.br.vertices.y);
	//CCLOG("%f,%f br coords", this->_quad.br.texCoords.u, this->_quad.br.texCoords.v);
/*
	CCLOG("%f,%f tl vertices", this->_quad.tl.vertices.x, this->_quad.tl.vertices.y);
	CCLOG("%f,%f tl coords", this->_quad.tl.texCoords.u, this->_quad.tl.texCoords.v);

	CCLOG("%f,%f tr vertices", this->_quad.tr.vertices.x, this->_quad.tr.vertices.y);
	CCLOG("%f,%f tr coords", this->_quad.tr.texCoords.u, this->_quad.tr.texCoords.v);

	CCLOG("%f,%f position", this->getPositionX(), this->getPositionY());*/
}