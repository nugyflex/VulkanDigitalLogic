#pragma once
#include "Vertex.h"
enum blockType { wire, inverter, andGate, orGate, xorGate };
enum blockDirection { positiveX, negativeX, positiveY, negativeY, positiveZ, negativeZ };
class Block {
public:
	Block(int x, int y, int z, blockType _type, blockDirection _direction) { position = glm::vec3(x, y, z); type = _type; direction = _direction; };
	~Block(){};
	glm::vec3 position;
	blockType type;
	blockDirection direction;
	glm::vec3 colour;
	bool state = false;
private:

};