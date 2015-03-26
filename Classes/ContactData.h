#pragma once

typedef enum class collide_bit
{
	BOTTOM = 8,
	BALL = 1,
	PADDLE = 2,
	BRICK = 4,
	WALL = 16,

}COLLIDE_BIT;

typedef enum class collide_type
{
	BALL_WALL = 0,
	BALL_BOTTOM,
	BALL_BRICK,
	BALL_PADDLE,
	UNKNOWN

}COLLIDE_TYPE;