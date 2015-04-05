#pragma once

typedef enum class collide_bit
{

	BALL = 1,
	PADDLE = 2,
	BRICK = 4,
	BOTTOM = 8,
	WALL = 16,
	SHATTER = 32

}COLLIDE_BIT;

typedef enum class collide_type
{
	BALL_WALL = 0,
	BALL_BOTTOM,
	BALL_BRICK,
	BALL_PADDLE,
	UNKNOWN

}COLLIDE_TYPE;