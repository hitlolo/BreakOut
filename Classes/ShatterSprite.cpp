#include "ShatterSprite.h"

ShatterSprite* ShatterSprite::create(b2Body* body, Sprite* originSprite)
{
	ShatterSprite *shatter = new (std::nothrow) ShatterSprite(body, originSprite);
	if (shatter && shatter->init(body,originSprite))
	{
		shatter->autorelease();
		return shatter;
	}
	CC_SAFE_DELETE(shatter);

	
	
	return nullptr;
}



ShatterSprite::ShatterSprite(b2Body* body, Sprite* originSprite)
{
	this->originSprite = originSprite;

}

ShatterSprite::~ShatterSprite()
{
	delete[] vertices;
}


//left = rect.origin.x / atlasWidth;
//right = (rect.origin.x + rect.size.width) / atlasWidth;
//top = rect.origin.y / atlasHeight;
//bottom = (rect.origin.y + rect.size.height) / atlasHeight;
bool ShatterSprite::init(b2Body* body, Sprite* originSprite)
{
	if (!PhysicsSprite::initWithSpriteFrame(originSprite->getSpriteFrame()))
	{
		return false;
	}
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
	this->setB2Body(body);
	this->initTextureRect(originSprite);
	this->setVerticesAndCoords(body);
	return true;
}
void ShatterSprite::initTextureRect(Sprite* originSprite)
{
	textureRect = originSprite->getTextureRect();
	//textureRect_Rotated = originSprite->_rectRotated;
	//CCLOG("%f,%f,texture _rect .this->_rect.size.w,.h", textureRect.size.width, textureRect.size.height);
	//CCLOG("%d,texture _rotated", this->_rectRotated);
	//CCLOG("%f,%f,texture _rect .origin", textureRect.origin.x, textureRect.origin.y);

}

void ShatterSprite::setVerticesAndCoords(b2Body* body)
{
	Texture2D* texture = this->getTexture();
	float atlasWidth = (float)texture->getPixelsWide();
	float atlasHeight = (float)texture->getPixelsHigh();

	float left;
	float right;
	float top;
	float bottom;


	if (_rectRotated)
	{

		left = textureRect.origin.x ;
		right = textureRect.origin.y + textureRect.size.height;
		top = textureRect.origin.y;		
		bottom = (textureRect.origin.x + textureRect.size.width);


		if (_flippedX)
		{
			std::swap(top, bottom);
		}

		if (_flippedY)
		{
			std::swap(left, right);
		}
	}
	else
	{

		left = textureRect.origin.x;
		right = (textureRect.origin.x + textureRect.size.width);
		top = textureRect.origin.y; 
		bottom = textureRect.origin.y + textureRect.size.height;

		if (_flippedX)
		{
			std::swap(left, right);
		}

		if (_flippedY)
		{
			std::swap(top, bottom);
		}

	}

	b2Fixture* fixture = body->GetFixtureList();
	b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
	poly_count = poly->GetVertexCount();

	float scalex = originSprite->getScaleX();
	float scaley = originSprite->getScaleY();
	CCPoint anchor_point = originSprite->getAnchorPoint();
	float resetX = originSprite->getContentSize().width * anchor_point.x;
	float resetY = originSprite->getContentSize().height * anchor_point.y;

	vertices = new V2F_C4F_T2F[poly_count];

	for (int i = 0; i < poly_count; i++)
	{
		b2Vec2 v = poly->GetVertex(i);
		float x = mtp(v.x) / scalex + resetX;
		float y = mtp(v.y) / scaley + resetY;
		vertices[i].vertices.x = x;
		vertices[i].vertices.y = y;
		if (_rectRotated)
		{
			vertices[i].texCoords.u = (left + y) / atlasWidth;
			vertices[i].texCoords.v = (top + x) / atlasHeight;
		}
		if (!_rectRotated)
		{
			vertices[i].texCoords.u = (left + x) / atlasWidth;
			vertices[i].texCoords.v = (bottom - y) / atlasHeight;
		}
		
		vertices[i].colors.r = 255;
		vertices[i].colors.g = 255;
		vertices[i].colors.b = 255;
		vertices[i].colors.a = 255;

	}
	
}


void ShatterSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (isDirty())
	{
		syncPhysicsTransform();
	}

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
	glDrawArrays(GL_TRIANGLE_FAN, 0, poly_count);
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

void ShatterSprite::bomb(b2Vec2 velocity)
{
	this->getB2Body()->SetLinearVelocity(velocity);
	auto action = Sequence::createWithTwoActions(DelayTime::create(2.5f), CallFunc::create(CC_CALLBACK_0(ShatterSprite::cleanUp, this)));
	this->runAction(action);
}

void ShatterSprite::cleanUp()
{
	auto body = this->getB2Body();
	auto world = body->GetWorld();
	world->DestroyBody(body);
	this->_pB2Body = NULL;
	this->removeFromParentAndCleanup(true);
}