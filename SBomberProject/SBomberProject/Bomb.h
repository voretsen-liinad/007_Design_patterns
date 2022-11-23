#pragma once

#include <iostream>
#include "MyTools.h"

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

private:

};

class BombDecorator : public DynamicObject {
public:
	
	void Move(uint16_t time) override {
		bomb.Move(time * 1.6);
	}

	void Draw() const override {
		bomb.Draw();
		MyTools::ScreenSingleton::getInstance().GotoXY(bomb.GetX(), bomb.GetY() - 1);
		std::cout << "|";
	}

	inline void SetPos(double nx, double ny) override { bomb.SetPos(nx, ny); }

	inline double GetY() const override { return bomb.GetY(); }
	
	inline double GetX() const override { return bomb.GetX();; }

	inline void SetWidth(uint16_t widthN) override { bomb.SetWidth(widthN); }

	inline uint16_t GetWidth() const override { return bomb.GetWidth(); }

	inline void SetSpeed(double sp) override { bomb.SetSpeed(sp); }
	
	inline void SetDirection(double dx, double dy) override { bomb.SetDirection(dx, dy); }

private:
	Bomb bomb;
};