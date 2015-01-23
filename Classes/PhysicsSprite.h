#ifndef BREAK_OUT_PHY_SPRITE
#define BREAK_OUT_PHY_SPRITE

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameData.h"

#define PTM_RATIO 32.0

USING_NS_CC;
class b2Body;
class PhysicsSprite :public Sprite
{
public:

	static PhysicsSprite* create();
	/** Creates an sprite with a texture.
	The rect used will be the size of the texture.
	The offset will be (0,0).
	*/
	static PhysicsSprite* createWithTexture(Texture2D *pTexture);

	/** Creates an sprite with a texture and a rect.
	The offset will be (0,0).
	*/
	static PhysicsSprite* createWithTexture(Texture2D *pTexture, const Rect& rect);

	/** Creates an sprite with an sprite frame. */
	static PhysicsSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);

	/** Creates an sprite with an sprite frame name.
	An SpriteFrame will be fetched from the SpriteFrameCache by name.
	If the SpriteFrame doesn't exist it will raise an exception.
	@since v0.9
	*/
	static PhysicsSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

	/** Creates an sprite with an image filename.
	The rect used will be the size of the image.
	The offset will be (0,0).
	*/
	static PhysicsSprite* create(const char *pszFileName);

	/** Creates an sprite with an image filename and a rect.
	The offset will be (0,0).
	*/
	static PhysicsSprite* create(const char *pszFileName, const Rect& rect);

	PhysicsSprite();

	virtual bool isDirty() const;

	/** Keep the sprite's rotation separate from the body. */
	bool isIgnoreBodyRotation() const;
	void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

	//
	// Box2d specific
	//
	/** Body accessor when using box2d */
	b2Body* getB2Body() const;
	void setB2Body(b2Body *pBody);

	float getPTMRatio() const;
	void setPTMRatio(float fPTMRatio);

	// overrides
	virtual const Vec2& getPosition() const override;
	virtual void getPosition(float* x, float* y) const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
	virtual void setPosition(const Vec2 &position) override;
	virtual float getRotation() const override;
	virtual void setRotation(float fRotation) override;
	virtual void syncPhysicsTransform() const;
	virtual const Mat4& getNodeToParentTransform() const override;

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
	const Vec2& getPosFromPhysics() const;

protected:
	bool    _ignoreBodyRotation;
	// box2d specific
	b2Body  *_pB2Body;
	float   _PTMRatio;
	
};






#endif