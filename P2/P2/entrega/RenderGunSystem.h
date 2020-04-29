#pragma once
#include "System.h"
#include "Manager.h"
#include "GameState.h"
#include "ImageComponent.h"
#include "Transform.h"
#include "Texture.h"

class RenderGunSystem : public System
{
public:
	RenderGunSystem(): System(ecs::_sys_Render) {}
	~RenderGunSystem() {}

	// - dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego está parado (como en la
	// práctica 1: Press ENTER to start, Game Over, etc.)
	void update() override;
};

