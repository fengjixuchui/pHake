#include "NoWanted.hpp"

NoWanted::NoWanted(std::shared_ptr<pOverlay> ui, std::shared_ptr<World> world, std::shared_ptr<Settings> settings)
{
	this->ui = ui;
	this->world = world;
	
	name_ = "NoWanted";
	thread_intervals_ = 10;
	active_ = &settings->nowanted;
}

void NoWanted::Execute()
{
	if (!*active_)
		return;

	if (world->localplayer.playerinfo.wanted_level() != 0)
		world->localplayer.playerinfo.wanted_level(0);
}

void NoWanted::Restore()
{
	if (*active_)
		world->localplayer.playerinfo.wanted_level(0);
}