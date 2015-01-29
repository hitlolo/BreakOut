#ifndef BREAK_OUT_PADDLE
#define BREAK_OUT_PADDLE

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameData.h"
#include "ShapeCache.h"
#include "PhysicsProtocol.h"
#include "PhysicsSprite.h"
#include "GB2ShapeCache-x.h"

USING_NS_CC;
USING_NS_UI;

#define NORMAL_SIZE Size(96,32)
#define MIN_SIZE Size(64,32)
#define MAX_SIZE Size(128,32)

class GamePaddle : virtual public Scale9Sprite, public PhysicsProtocol
{
public:
	static GamePaddle* create(b2World*,b2Body*);
	
	virtual bool init() override;

	virtual void update(float time) override;

	GamePaddle(b2World*, b2Body*);

	~GamePaddle();

private:
	std::string selectRandomFile();

	void initPhysicsAttributes();

	void initSelfImage();

public:
	/** Body accessor when using box2d */
	virtual bool isDirty() const;

	/** Keep the sprite's rotation separate from the body. */
	bool isIgnoreBodyRotation() const;
	void setIgnoreBodyRotation(bool bIgnoreBodyRotation);
	b2Body* getB2Body() const;
	void    setB2Body(b2Body *pBody);

	float getPTMRatio() const;
	void  setPTMRatio(float fPTMRatio);

	// overrides
	const Vec2& getPosFromPhysics() const;
	virtual const Vec2& getPosition() const override;
	virtual void getPosition(float* x, float* y) const override;
	virtual float getPositionX() const override;
	virtual float getPositionY() const override;
	virtual void setPosition(const Vec2 &position) override;
	virtual float getRotation() const override;
	virtual void setRotation(float fRotation) override;
	virtual void syncPhysicsTransform() const;
	virtual const Mat4& getNodeToParentTransform() const override;

	//virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	
private:
	b2World      *m_world;
	b2Body       *m_groundBody;
	b2Body       *m_body;
	b2MouseJoint *m_mouseJoint;
	float         m_ptm;
	bool          _ignoreBodyRotation;
	// box2d specific
	
public:
	void onBeginMove(const std::vector<Touch*>& touches);
	void onMove(const std::vector<Touch*>& touches);
	void onMoveEnd();
	void onMoveCancel();

};

#endif