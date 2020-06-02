#pragma once
#include "System.h"
class AudioSystem :	public System
{
public:
	AudioSystem() :System(ecs::_sys_Audio) {}
	void init() override;
	void recieve(const msg::Message& msg);
};

