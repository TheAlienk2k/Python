#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <string>

class Snake;

class Food
{
protected:
	const sf::Texture* texture = nullptr;
	std::array<int, 2> coordinates{};

	int scoreValue;
	float effectDurration;
	bool stackable;
	int id;

public:
	virtual ~Food() = default;
	static inline int rngWeight = 0;

	float getEffectDurration() { return effectDurration; }
	bool isStackable() { return stackable; }
	int getId() { return id; }
	int getScoreValue() { return scoreValue; }
	std::array<int, 2> getCoordinates() { return coordinates; }
	const sf::Texture& getTexture() const { return *texture; }
	void setCoordinates(int x, int y) { coordinates[0] = x; coordinates[1] = y; }

	virtual void applyEffect(Snake& snake) = 0;
	virtual void expireEffect(Snake& snake) = 0;
};

class BasicFood : public Food
{
public:
	static inline int rngWeight = 20;

	BasicFood(int x = 0, int y = 0);
	void applyEffect(Snake& snake) override;
	void expireEffect(Snake& snake) override;
};

class SpicyFood : public Food
{
public:
	static inline int rngWeight = 10;

	SpicyFood(int x = 0, int y = 0);
	void applyEffect(Snake& snake) override;
	void expireEffect(Snake& snake) override;
};