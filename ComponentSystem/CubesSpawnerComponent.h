#pragma once

#include <Unigine.h>
#include <UnigineComponentSystem.h>

class CubesSpawnerComponent : public Unigine::ComponentBase
{
public:
	COMPONENT(CubesSpawnerComponent, ComponentBase);

	COMPONENT_INIT(init);

	PROP_NAME("cubes_spawner_component");

	PROP_PARAM(File, node_to_spawn);
	PROP_PARAM(Vec3, size, Unigine::Math::vec3(1.f));
	PROP_PARAM(Int, count_per_axis, 20);

protected:
	void init();

private:
	void spawnActors();
};

