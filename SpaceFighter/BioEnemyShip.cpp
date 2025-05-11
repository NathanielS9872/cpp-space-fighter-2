
#include "BioEnemyShip.h"
#include "Level.h"


BioEnemyShip::BioEnemyShip(int i)
{
	srand(3698+(i*i*56982)-time(NULL));
	int random = rand() % 10;
	//0-1-2-3-4 Common enemy (default stats)
	//5-6 Fast enemy (higher speed)
	//7-8 Tank enemy (higher max hp but lower speed)
	//9 Boss (significantly higher max hp, but significantly lower speed)
	//Values can be adjusted as needed (probably not collisionradius except on the boss)

	//Increase speed/attack speed of player ship or decrease enemy stats a bit to balance it out?
	if (random <= 4) {
		SetSpeed(150);
		SetMaxHitPoints(1);
		SetCollisionRadius(20);
		m_enemyType = 'C';
		m_color = Color::WHITE;
	}
	if (random == 5 || random == 6) {
		SetSpeed(200);
		SetMaxHitPoints(1);
		SetValue(75);
		SetCollisionRadius(20);
		m_enemyType = 'F';
		m_color = Color::YELLOW;
	}
	if (random == 7 || random == 8) {
		SetSpeed(65);
		SetValue(75);
		SetMaxHitPoints(5);
		SetCollisionRadius(20);
		m_enemyType = 'T';
		m_color = Color::AQUA;
	}
	if (random == 9) {
		SetSpeed(20);
		SetValue(150);
		SetMaxHitPoints(20);
		SetCollisionRadius(100);
		m_enemyType = 'B';
		m_color = Color::WHITE;
	}
}


void BioEnemyShip::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		float x = sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
		x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f;
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());

		if (!IsOnScreen()) Deactivate();
	}

	EnemyShip::Update(gameTime);
}


void BioEnemyShip::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), m_color * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
