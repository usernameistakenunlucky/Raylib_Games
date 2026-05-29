#include "Ball.h"

Ball::Ball()
{

}

Ball::Ball(const Vector2& position)
	: _position(position)
{

}

void Ball::Update(std::vector<Brick>& bricks, Player& player, int& score, int& _currentLevel)
{
	if (this->_active) //if ball is active (moving)
	{
		CheckCollisionBricks(bricks, score);
		CheckCollisionPlayer(player);
		CheckCollisionBorder(player);

		_trail.push_back(_position);
		if (_trail.size() > TRAIL_LENGTH)
		{
			_trail.erase(_trail.begin());
		}
		_position += _speed;
	}
	else // follow player
	{
		_position = Vector2{ /*X*/ player.GetPos().x + player.GetSize().x / 2,
			/*             *//*Y*/ player.GetPos().y - _radius };

		if (IsKeyDown(KEY_SPACE))
		{
			_active = true;
			float speedMult = 1 + _currentLevel / 5;
			_speed = Vector2{ 0, BALL_SPEED * speedMult };
		}
	}
}

void Ball::CheckCollisionBricks(std::vector<Brick>& bricks, int& score)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		if (!bricks[i].IsActive()) continue;

		if (CheckCollisionCircleRec(this->_position, this->_radius, bricks[i].GetRect())) // hits a brick
		{
			bricks[i].Deactivate();
			score += 10;

			if (this->_position.y >= bricks[i].GetRect().y && this->_position.y <= bricks[i].GetRect().y + bricks[i].GetRect().height)
			{
				this->_speed.x *= -1;
			}
			else { this->_speed.y *= -1; }

			break;
		}
	}
}

void Ball::CheckCollisionPlayer(Player& player)
{
	if (CheckCollisionCircleRec(this->_position, this->_radius, player.GetRect()))
	{
		float hitOffset = (this->_position.x - player.GetCenter().x) / (player.GetRect().width / 2);

		float speed = Vector2Length(this->_speed);
		Vector2 normal = Vector2Normalize({ hitOffset, -1.0f });
		this->_speed = Vector2Scale(normal, speed);

		player.Bounce();
	}
}

void Ball::CheckCollisionBorder(Player& player)
{
	if (_position.x <= _radius || _position.x >= SCREEN_WIDTH - _radius)
	{
		_speed.x *= -1;
		if (_position.x < _radius) { _position.x = _radius + 1; }
		if (_position.x > SCREEN_WIDTH - _radius) { _position.x = SCREEN_WIDTH - _radius - 1; }
	}
	if (_position.y <= _radius)
	{
		_speed.y *= -1;
		if (_position.x < _radius) { _position.x = _radius + 1; }
	}

	if (_position.y >= SCREEN_HEIGHT)
	{
		this->Reset();
		player.LoseLife();
	}
}

void Ball::Render() const
{
	if (_active)
	{
		for (int i = 0; i < _trail.size(); i++)
		{
			int trailBrightness = 180 + (5 * i);
			Color trailColor{ trailBrightness, trailBrightness, trailBrightness, 255 };
			float trailRadius = _radius / 2.2 * (0.2f * (i + 1));
			DrawCircleV(_trail[i], trailRadius, trailColor);
		}
	}
	DrawCircleV(_position, _radius, Color{ 80,80,100,255 }); //dark outline
	DrawCircleV(_position, _radius * 0.9, Color{ 200,200,240,255 });  //main color
	DrawCircleV(Vector2{_position.x - 5, _position.y - 5}, _radius * 0.6, Color{ 255,255,255,255 }); //reflection
	DrawCircleV(_position, _radius * 0.7, Color{ 200,200,200,255 }); //reflection cut-out
}
void Ball::Reset()
{
	_active = false;
	_trail.clear();
}