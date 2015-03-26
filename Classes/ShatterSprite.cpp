#include "ShatterSprite.h"

ShatterSprite* ShatterSprite::create(V3F_C4B_T2F_POLY poly, std::string file)
{
	ShatterSprite *sprite = new (std::nothrow) ShatterSprite(poly);
	if (sprite && sprite->init(file))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);

	
	
	return nullptr;
}

bool ShatterSprite::init(std::string file)
{
	if (!Sprite::initWithSpriteFrameName(file))
	{
		return false;
	}
	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
	auto action = RotateBy::create(1.0f, -90);
	auto s = RepeatForever::create(action);
	this->runAction(s);
	return true;
}

ShatterSprite::ShatterSprite(V3F_C4B_T2F_POLY poly)
{
	this->poly_data = poly;
}

ShatterSprite::~ShatterSprite()
{
	delete[] poly_data.vertice;
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
		command.init(_globalZOrder,_transform,flags);
		command.func = std::bind(&ShatterSprite::onDraw, this);
		renderer->addCommand(&command);
		//CCLOG("%f,%f,%f,%f,transform1", _transform.m[0], _transform.m[1], _transform.m[2], _transform.m[3]);
		//CCLOG("%f,%f,%f,%f,transform2", _transform.m[4], _transform.m[5], _transform.m[6], _transform.m[7]);
		//CCLOG("%f,%f,%f,%f,transform3", _transform.m[8], _transform.m[9], _transform.m[10], _transform.m[11]);
		//CCLOG("%f,%f,%f,%f,transform4", _transform.m[12], _transform.m[13], _transform.m[14], _transform.m[15]);

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
	//��õ�ǰHelloWorld��shader
	//Node::draw();
	
	auto glProgram = getGLProgram();
	//ʹ�ô�shader
	glProgram->use();
	//���ø�shader��һЩ����uniform,��Ҫ��MVP����model-view-project����
	glProgram->setUniformsForBuiltins(_transform);

	

	auto size = Director::getInstance()->getWinSize();
	//ָ����Ҫ���Ƶ������ε��������㣬�ֱ�λ����Ļ���½ǣ����½Ǻ����м�Ķ���
	float vertercies[] = 
	{
		0,0,
		49, 0,   //�ڶ����������
		0, 49,
		0,49,
		49,49,
		49,0
	}; 

	//ָ��ÿһ���������ɫ����ɫֵ��RGBA��ʽ�ģ�ȡֵ��Χ��0-1
	float color[] = {
		0, 1, 0, 1,    //��һ�������ɫ����ɫ
		1, 0, 0, 1,  //�ڶ��������ɫ, ��ɫ
		0, 0, 1, 1 };  //�����������ɫ�� ��ɫ
	float coord[] = {
		0.214844, 0.838867,    //��һ�������ɫ����ɫ
		0.406250, 0.838867,  //�ڶ��������ɫ, ��ɫ
		0.214844, 0.791016,
		0.214844, 0.791016,
		0.406250, 0.791016,
		0.406250, 0.838867
	};  //
	//��������Ϊposition��color��vertex attribute
	//Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	//�ֱ��position��colorָ������Դ
	glBindTexture(GL_TEXTURE_2D, this->_texture->getName());
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
//	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coord);
//	glTexCoordPointer(2, GL_FLOAT, sizeof(coord), coord);

	//���������Σ���ν��draw call����ָ�����������
	glDrawArrays(GL_POLYGON, 0, 4);
	//֪ͨcocos2d-x ��renderer�������ں��ʵ�ʱ�������ЩOpenGL����
//	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
	//��������ˣ�����ʹ�������������ȡ������Ϣ
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