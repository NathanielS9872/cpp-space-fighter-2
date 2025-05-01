#pragma once
#include "BioEnemyShip.h"
#include "Level.h"
//In Ships folder because inheriting from a ship
//Does not harm the player ship
//Theres probably a couple unnecessary changes related to this class, but it seemed to not work without them
class Item : public BioEnemyShip
{
public:
	Item();
	void Activate(const Vector2 position, const float scale);
	void Draw(SpriteBatch& spriteBatch);
	void Update(const GameTime& gameTime);
	virtual CollisionType GetCollisionType() const { return CollisionType::Item; }
private:
	int m_scale;
	int m_rotation;
	bool m_Active = false;
	bool m_isActive = false;
	Texture* m_pTexture = nullptr;

};