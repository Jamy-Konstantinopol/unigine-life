#include "LiveGameComponent.h"

REGISTER_COMPONENT(LiveGameComponent);

void LiveGameComponent::update()
{
	if (!coordinate_cube_map.size())
		initCubes();

	float currentTime = Unigine::Time::get();

	if (currentTime - lastUpdateTime >= updateInterval)
	{
		for (const auto& pair : coordinate_cube_map)
		{
			const auto cube = pair.data;
			const int neighbors_count = getNeighborsCount(cube);

			const bool is_may_be_lived = neighbors_count >= neighbors_count_to_alive.get()
				&& neighbors_count <= max_neighbors_count_to_resurrect.get()
				&& cube->isEnabled();

			if (neighbors_count >= min_neighbors_count_to_resurrect.get() && neighbors_count <= max_neighbors_count_to_resurrect.get())
				cube->setEnabled(true);
			else if (!is_may_be_lived)
				cube->setEnabled(false);
		}

		lastUpdateTime = currentTime;
	}
}

void LiveGameComponent::initCubes()
{
	Unigine::Vector<Unigine::NodePtr> cubes{};
	Unigine::World::getNodesByName("box", cubes);

	for (const auto& cube : cubes)
		coordinate_cube_map.append(cube->getPosition(), cube);
}

int LiveGameComponent::getNeighborsCount(Unigine::NodePtr cube)
{
	const auto position = cube->getPosition();
	const auto scale = cube->getScale();

	int result = 0;
	Unigine::Vector<Unigine::Vector<float>> offsets =
	{
	{1, 1, 1},
	{1, 1, 0},
	{1, 1, -1},
	{1, 0, 1},
	{1, 0, 0},
	{1, 0, -1},
	{1, -1, 1},
	{1, -1, 0},
	{1, -1, -1},
	{0, 1, 1},
	{0, 1, 0},
	{0, 1, -1},
	{0, 0, 1},
	{0, 0, -1},
	{0, -1, 1},
	{0, -1, 0},
	{0, -1, -1},
	{-1, 1, 1},
	{-1, 1, 0},
	{-1, 1, -1},
	{-1, 0, 1},
	{-1, 0, 0},
	{-1, 0, -1},
	{-1, -1, 1},
	{-1, -1, 0},
	{-1, -1, -1}
	};

	for (const auto& offset : offsets)
	{
		const float dx = offset[0];
		const float dy = offset[1];
		const float dz = offset[2];

		if (dx == 0 && dy == 0 && dz == 0)
			continue;

		Unigine::Math::vec3 key = { position.x + dx, position.y + dy, position.z + dz };
		if (coordinate_cube_map.contains(key))
		{
			const auto nerbour = coordinate_cube_map.get(key);
			result += nerbour ? !!nerbour->isEnabled() : 0;
			const auto a = !!nerbour->isEnabled();
		}
	}

	return result;
}
