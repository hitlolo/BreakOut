#include "PolySprite.h"

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

/// MARK: create, init, dealloc
PolySprite* PolySprite::create()
{
	PolySprite *sprite = new (std::nothrow) PolySprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


PolySprite* PolySprite::createWithTexture(Texture2D *texture)
{
	PolySprite *sprite = new (std::nothrow) PolySprite();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

PolySprite* PolySprite::createWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
	PolySprite *sprite = new (std::nothrow) PolySprite();
	if (sprite && sprite->initWithTexture(texture, rect, rotated))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

PolySprite* PolySprite::create(const std::string& filename)
{
	PolySprite *sprite = new (std::nothrow) PolySprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

PolySprite* PolySprite::create(const std::string& filename, const Rect& rect)
{
	PolySprite *sprite = new (std::nothrow) PolySprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

PolySprite* PolySprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	PolySprite *sprite = new (std::nothrow) PolySprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

PolySprite* PolySprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}


///init
bool PolySprite::init(void)
{
	return initWithTexture(nullptr, Rect::ZERO);
}

bool PolySprite::initWithTexture(Texture2D *texture)
{
	CCASSERT(texture != nullptr, "Invalid texture for sprite");

	Rect rect = Rect::ZERO;
	rect.size = texture->getContentSize();

	return initWithTexture(texture, rect);
}

bool PolySprite::initWithTexture(Texture2D *texture, const Rect& rect)
{
	return initWithTexture(texture, rect, false);
}

bool PolySprite::initWithFile(const std::string& filename)
{
	CCASSERT(filename.size()>0, "Invalid filename for sprite");

	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
	if (texture)
	{
		Rect rect = Rect::ZERO;
		rect.size = texture->getContentSize();
		return initWithTexture(texture, rect);
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release();
	return false;
}

bool PolySprite::initWithFile(const std::string &filename, const Rect& rect)
{
	CCASSERT(filename.size()>0, "Invalid filename");

	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
	if (texture)
	{
		return initWithTexture(texture, rect);
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release();
	return false;
}

bool PolySprite::initWithSpriteFrameName(const std::string& spriteFrameName)
{
	CCASSERT(spriteFrameName.size() > 0, "Invalid spriteFrameName");

	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
	return initWithSpriteFrame(frame);
}

bool PolySprite::initWithSpriteFrame(SpriteFrame *spriteFrame)
{
	CCASSERT(spriteFrame != nullptr, "");

	bool bRet = initWithTexture(spriteFrame->getTexture(), spriteFrame->getRect());
	this->setSpriteFrame(spriteFrame);

	return bRet;
}

// designated initializer
bool PolySprite::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
	bool result;
	if (Node::init())
	{
		_batchNode        = nullptr;
		_recursiveDirty   = false;
		_dirty            = false;
		_opacityModifyRGB = true;

		_blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

		_flippedX = _flippedY = false;

		// default transform anchor: center
		setAnchorPoint(Vec2(0.5f, 0.5f));

		// zwoptex default values
		_offsetPosition = Vec2::ZERO;
		
		///need modified
		// clean the Quad
		memset(&_quad, 0, sizeof(_quad));

		// Atlas: Color
		_quad.bl.colors = Color4B::WHITE;
		_quad.br.colors = Color4B::WHITE;
		_quad.tl.colors = Color4B::WHITE;
		_quad.tr.colors = Color4B::WHITE;

		// shader state
		setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));

		// update texture (calls updateBlendFunc)
		setTexture(texture);
		setTextureRect(rect, rotated, rect.size);

		// by default use "Self Render".
		// if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
		setBatchNode(nullptr);
		result = true;
	}
	else
	{
		result = false;
	}
	_recursiveDirty = true;
	_dirty = true;
	return result;
}

PolySprite::PolySprite(void)
	: _batchNode(nullptr)
	, _shouldBeHidden(false)
	, _texture(nullptr)
	, _spriteFrame(nullptr)
	, _insideBounds(true)
{
#if CC_SPRITE_DEBUG_DRAW
	_debugDrawNode = DrawNode::create();
	addChild(_debugDrawNode);
#endif //CC_SPRITE_DEBUG_DRAW
}

PolySprite::~PolySprite(void)
{
	CC_SAFE_RELEASE(_spriteFrame);
	CC_SAFE_RELEASE(_texture);
}


/*
* Texture methods
*/

/*
* This array is the data of a white image with 2 by 2 dimension.
* It's used for creating a default texture when sprite's texture is set to nullptr.
* Supposing codes as follows:
*
*   auto sp = new (std::nothrow) Sprite();
*   sp->init();  // Texture was set to nullptr, in order to make opacity and color to work correctly, we need to create a 2x2 white texture.
*
* The test is in "TestCpp/SpriteTest/Sprite without texture".
*/
static unsigned char cc_2x2_white_image[] = {
	// RGBA8888
	0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_2x2_WHITE_IMAGE_KEY  "/cc_2x2_white_image"

// MARK: texture
void PolySprite::setTexture(const std::string &filename)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
	setTexture(texture);

	Rect rect = Rect::ZERO;
	if (texture)
		rect.size = texture->getContentSize();
	setTextureRect(rect);
}

void PolySprite::setTexture(Texture2D *texture)
{
	// If batchnode, then texture id should be the same
	CCASSERT(!_batchNode || texture->getName() == _batchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
	// accept texture==nil as argument
	CCASSERT(!texture || dynamic_cast<Texture2D*>(texture), "setTexture expects a Texture2D. Invalid argument");

	if (texture == nullptr)
	{
		// Gets the texture by key firstly.
		texture = Director::getInstance()->getTextureCache()->getTextureForKey(CC_2x2_WHITE_IMAGE_KEY);

		// If texture wasn't in cache, create it from RAW data.
		if (texture == nullptr)
		{
			Image* image = new (std::nothrow) Image();
			bool isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
			CC_UNUSED_PARAM(isOK);
			CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");

			texture = Director::getInstance()->getTextureCache()->addImage(image, CC_2x2_WHITE_IMAGE_KEY);
			CC_SAFE_RELEASE(image);
		}
	}

	if (!_batchNode && _texture != texture)
	{
		CC_SAFE_RETAIN(texture);
		CC_SAFE_RELEASE(_texture);
		_texture = texture;
		updateBlendFunc();
	}
}

Texture2D* PolySprite::getTexture() const
{
	return _texture;
}

void PolySprite::setTextureRect(const Rect& rect)
{
	setTextureRect(rect, false, rect.size);
}

void PolySprite::setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)
{
	_rectRotated = rotated;

	setContentSize(untrimmedSize);
	setVertexRect(rect);
	setTextureCoords(rect);

	Vec2 relativeOffset = _unflippedOffsetPositionFromCenter;

	// issue #732
	if (_flippedX)
	{
		relativeOffset.x = -relativeOffset.x;
	}
	if (_flippedY)
	{
		relativeOffset.y = -relativeOffset.y;
	}

	_offsetPosition.x = relativeOffset.x + (_contentSize.width - _rect.size.width) / 2;
	_offsetPosition.y = relativeOffset.y + (_contentSize.height - _rect.size.height) / 2;

	// rendering using batch node
	if (_batchNode)
	{
		// update dirty_, don't update recursiveDirty_
		setDirty(true);
	}
	else
	{
		// self rendering

		// Atlas: Vertex
		float x1 = 0 + _offsetPosition.x;
		float y1 = 0 + _offsetPosition.y;
		float x2 = x1 + _rect.size.width;
		float y2 = y1 + _rect.size.height;



		///¶¥µã
		///modified needed
		// Don't update Z.
		_quad.bl.vertices = Vec3(x1, y1, 0);
		_quad.br.vertices = Vec3(x2, y1, 0);
		_quad.tl.vertices = Vec3(x1, y2, 0);
		_quad.tr.vertices = Vec3(x2, y2, 0);
	}
}

// override this method to generate "double scale" sprites
void PolySprite::setVertexRect(const Rect& rect)
{
	_rect = rect;
}


///modified  needed
void PolySprite::setTextureCoords(Rect rect)
{
	rect = CC_RECT_POINTS_TO_PIXELS(rect);

	Texture2D *tex = _batchNode ? _textureAtlas->getTexture() : _texture;
	if (!tex)
	{
		return;
	}

	float atlasWidth = (float)tex->getPixelsWide();
	float atlasHeight = (float)tex->getPixelsHigh();

	float left, right, top, bottom;

	if (_rectRotated)
	{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
		left = (2 * rect.origin.x + 1) / (2 * atlasWidth);
		right = left + (rect.size.height * 2 - 2) / (2 * atlasWidth);
		top = (2 * rect.origin.y + 1) / (2 * atlasHeight);
		bottom = top + (rect.size.width * 2 - 2) / (2 * atlasHeight);
#else
		left = rect.origin.x / atlasWidth;
		right = (rect.origin.x + rect.size.height) / atlasWidth;
		top = rect.origin.y / atlasHeight;
		bottom = (rect.origin.y + rect.size.width) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

		if (_flippedX)
		{
			std::swap(top, bottom);
		}

		if (_flippedY)
		{
			std::swap(left, right);
		}

		///ÎÆÀí×ø±ê
		_quad.bl.texCoords.u = left;
		_quad.bl.texCoords.v = top;
		_quad.br.texCoords.u = left;
		_quad.br.texCoords.v = bottom;
		_quad.tl.texCoords.u = right;
		_quad.tl.texCoords.v = top;
		_quad.tr.texCoords.u = right;
		_quad.tr.texCoords.v = bottom;
	}
	else
	{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
		left = (2 * rect.origin.x + 1) / (2 * atlasWidth);
		right = left + (rect.size.width * 2 - 2) / (2 * atlasWidth);
		top = (2 * rect.origin.y + 1) / (2 * atlasHeight);
		bottom = top + (rect.size.height * 2 - 2) / (2 * atlasHeight);
#else
		left = rect.origin.x / atlasWidth;
		right = (rect.origin.x + rect.size.width) / atlasWidth;
		top = rect.origin.y / atlasHeight;
		bottom = (rect.origin.y + rect.size.height) / atlasHeight;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

		if (_flippedX)
		{
			std::swap(left, right);
		}

		if (_flippedY)
		{
			std::swap(top, bottom);
		}

		_quad.bl.texCoords.u = left;
		_quad.bl.texCoords.v = bottom;
		_quad.br.texCoords.u = right;
		_quad.br.texCoords.v = bottom;
		_quad.tl.texCoords.u = left;
		_quad.tl.texCoords.v = top;
		_quad.tr.texCoords.u = right;
		_quad.tr.texCoords.v = top;
	}
}



// MARK: visit, draw, transform

void PolySprite::updateTransform(void)
{
	CCASSERT(_batchNode, "updateTransform is only valid when Sprite is being rendered using an SpriteBatchNode");

	// recalculate matrix only if it is dirty
	if (isDirty()) {

		// If it is not visible, or one of its ancestors is not visible, then do nothing:
		if (!_visible || (_parent && _parent != _batchNode && !(static_cast<cocos2d::Sprite*>(_parent)->isVisible())))
		{
			_quad.br.vertices = _quad.tl.vertices = _quad.tr.vertices = _quad.bl.vertices = Vec3(0, 0, 0);
			_shouldBeHidden = true;
		}
		else
		{
			_shouldBeHidden = false;

			if (!_parent || _parent == _batchNode)
			{
				_transformToBatch = getNodeToParentTransform();
			}
			else
			{
				CCASSERT(dynamic_cast<cocos2d::Sprite*>(_parent), "Logic error in Sprite. Parent must be a Sprite");
				const Mat4 &nodeToParent = getNodeToParentTransform();
				Mat4 &parentTransform = static_cast<cocos2d::Sprite*>(_parent)->_transformToBatch;
				_transformToBatch = parentTransform * nodeToParent;
			}

			//
			// calculate the Quad based on the Affine Matrix
			//

			Size &size = _rect.size;

			float x1 = _offsetPosition.x;
			float y1 = _offsetPosition.y;

			float x2 = x1 + size.width;
			float y2 = y1 + size.height;
			float x = _transformToBatch.m[12];
			float y = _transformToBatch.m[13];

			float cr = _transformToBatch.m[0];
			float sr = _transformToBatch.m[1];
			float cr2 = _transformToBatch.m[5];
			float sr2 = -_transformToBatch.m[4];
			float ax = x1 * cr - y1 * sr2 + x;
			float ay = x1 * sr + y1 * cr2 + y;

			float bx = x2 * cr - y1 * sr2 + x;
			float by = x2 * sr + y1 * cr2 + y;

			float cx = x2 * cr - y2 * sr2 + x;
			float cy = x2 * sr + y2 * cr2 + y;

			float dx = x1 * cr - y2 * sr2 + x;
			float dy = x1 * sr + y2 * cr2 + y;

			_quad.bl.vertices = Vec3(RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _positionZ);
			_quad.br.vertices = Vec3(RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _positionZ);
			_quad.tl.vertices = Vec3(RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _positionZ);
			_quad.tr.vertices = Vec3(RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _positionZ);
		}

		// MARMALADE CHANGE: ADDED CHECK FOR nullptr, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
		if (_textureAtlas)
		{
			_textureAtlas->updateQuad(&_quad, _atlasIndex);
		}

		_recursiveDirty = false;
		setDirty(false);
	}

	// MARMALADE CHANGED
	// recursively iterate over children
	/*    if( _hasChildren )
	{
	// MARMALADE: CHANGED TO USE Node*
	// NOTE THAT WE HAVE ALSO DEFINED virtual Node::updateTransform()
	arrayMakeObjectsPerformSelector(_children, updateTransform, Sprite*);
	}*/
	Node::updateTransform();
}

