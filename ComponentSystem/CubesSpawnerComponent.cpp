#include "CubesSpawnerComponent.h"

REGISTER_COMPONENT(CubesSpawnerComponent);

void CubesSpawnerComponent::init()
{
	spawnActors();
}

void CubesSpawnerComponent::spawnActors()
{
	Unigine::Math::vec3 position(0.f);

	for (size_t i = 0; i < count_per_axis; i++)
		for (size_t j = 0; j < count_per_axis; j++)
			for (size_t k = 0; k < count_per_axis; k++)
				if (node)
					if (Unigine::NodePtr cube = Unigine::World::loadNode(node_to_spawn.get()))
					{
						float x = node->getWorldPosition().x + i * size.get().x;
						float y = node->getWorldPosition().y + j * size.get().y;
						float z = node->getWorldPosition().z + k * size.get().z;
						cube->setWorldPosition({ x, y, z });

						cube->setScale(size.get());
						cube->setEnabled(Unigine::Math::randInt(0, 2));
					}
}
