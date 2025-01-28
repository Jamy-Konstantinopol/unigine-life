#pragma once

#include <Unigine.h>
#include <UnigineComponentSystem.h>

class LiveGameComponent : public Unigine::ComponentBase
{
public:
	COMPONENT(LiveGameComponent, ComponentBase);

	COMPONENT_UPDATE(update);

	PROP_NAME("live_game_component");

	PROP_PARAM(Int, neighbors_count_to_alive, 4);
	PROP_PARAM(Int, min_neighbors_count_to_resurrect, 5);
	PROP_PARAM(Int, max_neighbors_count_to_resurrect, 6);


private:
	Unigine::HashMap<Unigine::Math::vec3, Unigine::NodePtr> coordinate_cube_map;

	long long updateInterval = 500000;
	long long lastUpdateTime = 0;

protected:
	void update();

private:
	void initCubes();
	int getNeighborsCount(Unigine::NodePtr cube);
};

