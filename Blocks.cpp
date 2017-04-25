#include "Blocks.h"

Blocks::Blocks() {}
void Blocks::correctCameraWithBlocks(glm::vec3* cameraMin, glm::vec3* cameraMax, glm::vec3* cameraVel) {
	glm::vec3 test = glm::vec3(cameraMin->x, cameraMin->y, cameraMin->y);
	for (int i = 0; i < blocks.size(); i++) {
		correctBoundingBox(cameraMin, cameraMax, &blocks[i]->position, &glm::vec3(blocks[i]->position.x + 1, blocks[i]->position.y + 1, blocks[i]->position.z + 1), cameraVel);
	}
}
void Blocks::init(std::vector<Vertex>* _vertices, std::vector<uint32_t>* _indices) {
	vertices = _vertices;
	indices = _indices;
		addBlock(((double)rand() / (RAND_MAX)) * 120, ((double)rand() / (RAND_MAX)) * 120, ((double)rand() / (RAND_MAX)) * 120, inverter);
}
void Blocks::addBlock(int x, int y, int z, blockType type) {
	if (!doesBlockExist(x, y, z)) {
		blocks.push_back(new Block(x, y, z, type, positiveY));
	}
}
void Blocks::addBlock(int x, int y, int z, blockType type, blockDirection direction) {
	if (!doesBlockExist(x, y, z)) {
		blocks.push_back(new Block(x, y, z, type, direction));
	}
}
int Blocks::getVectorSize() {
	return blocks.size();
}
bool Blocks::removeBlock(int x, int y, int z) {
	if (doesBlockExist(x, y, z)) {
		int index = getBlock(x, y, z);
		blocks.erase(blocks.begin() + index);
		return true;
	}
	return false;
}
bool Blocks::doesBlockExist(int x, int y, int z) {
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->position == glm::vec3(x, y, z)) {
			return true;
		}
	}
	return false;
}
int Blocks::getBlock(int x, int y, int z) {
	for (int i = 0; i < blocks.size(); i++) {
		//int x = 0;
		if (blocks[i]->position == glm::vec3(x, y, z)) {
			return i;
		}
	}
	return NULL;
}

void Blocks::correctBoundingBox(glm::vec3* min1, glm::vec3* max1, glm::vec3* min2, glm::vec3* max2, glm::vec3* vel) {
	/**
	if (!(max1->x > min2->x && min1->x < max2->x)) { return; }
	if (!(max1->y > min2->y && min1->y < max2->y)) { return; }
	if (!(max1->z > min2->z && min1->z < max2->z)) { return; }*/
	float buffer = 0.001;
	if (max1->x > min2->x && min1->x < max2->x) {
		if (max1->y > min2->y && min1->y < max2->y) {
			//XY
			if (max1->z < min2->z  && max1->z + vel->z > min2->z) {
				min1->z = min2->z - buffer - (max1->z - min1->z);
				max1->z = min2->z - buffer;
				vel->z = 0;
			}
			if (min1->z > max2->z && min1->z + vel->z < max2->z) {
				max1->z = max2->z + buffer + (max1->z - min1->z);
				min1->z = max2->z + buffer;
				vel->z = 0;
			}
		}
		if (max1->z > min2->z && min1->z < max2->z) {
			//XZ
			if (max1->y < min2->y  && max1->y + vel->y > min2->y) {
				min1->y = min2->y - buffer - (max1->y - min1->y);
				max1->y = min2->y - buffer;
				vel->y = 0;
			}
			if (min1->y > max2->y && min1->y + vel->y < max2->y) {
				max1->y = max2->y + buffer + (max1->y - min1->y);
				min1->y = max2->y + buffer;
				vel->y = 0;
			}
		}
	}
	else {
		if (max1->y > min2->y && min1->y < max2->y && max1->z > min2->z && min1->z < max2->z) {
			//YZ
			if (max1->x < min2->x  && max1->x + vel->x > min2->x) {
				min1->x = min2->x - buffer - (max1->x - min1->x);
				max1->x = min2->x - buffer;
				vel->x = 0;
			}
			if (min1->x > max2->x && min1->x + vel->x < max2->x) {
				max1->x = max2->x + buffer + (max1->x - min1->x);
				min1->x = max2->x + buffer;
				vel->x = 0;
			}
		}
	}
}
void Blocks::checkSurroundingBlocks(glm::vec3 block) {
	if (blocks[getBlock(block.x, block.y, block.z)]->state == true) {
		if (doesBlockExist(block.x, block.y, block.z) && blocks[getBlock(block.x, block.y, block.z)]->type == wire) {
			if (doesBlockExist(block.x + 1, block.y, block.z) && blocks[getBlock(block.x + 1, block.y, block.z)]->type == wire && blocks[getBlock(block.x + 1, block.y, block.z)]->state == false) {
				blocks[getBlock(block.x + 1, block.y, block.z)]->state = true;
				checkSurroundingBlocks(glm::vec3(block.x + 1, block.y, block.z));
			}
			if (doesBlockExist(block.x - 1, block.y, block.z) && blocks[getBlock(block.x - 1, block.y, block.z)]->type == wire && blocks[getBlock(block.x - 1, block.y, block.z)]->state == false) {
				blocks[getBlock(block.x - 1, block.y, block.z)]->state = true;
				checkSurroundingBlocks(glm::vec3(block.x - 1, block.y, block.z));
			}
			if (doesBlockExist(block.x, block.y + 1, block.z) && blocks[getBlock(block.x, block.y + 1, block.z)]->type == wire && blocks[getBlock(block.x , block.y + 1, block.z)]->state == false) {
				blocks[getBlock(block.x, block.y + 1, block.z)]->state = true;
				checkSurroundingBlocks(glm::vec3(block.x, block.y + 1, block.z));
			}
			if (doesBlockExist(block.x, block.y - 1, block.z) && blocks[getBlock(block.x, block.y - 1, block.z)]->type == wire && blocks[getBlock(block.x, block.y - 1, block.z)]->state == false) {
				blocks[getBlock(block.x, block.y - 1, block.z)]->state = true;
				checkSurroundingBlocks(glm::vec3(block.x, block.y - 1, block.z));
			}
			if (doesBlockExist(block.x, block.y, block.z + 1) && blocks[getBlock(block.x, block.y, block.z + 1)]->type == wire && blocks[getBlock(block.x, block.y, block.z + 1)]->state == false) {
				blocks[getBlock(block.x, block.y, block.z + 1)]->state = true;
				checkSurroundingBlocks(glm::vec3(block.x, block.y, block.z + 1));
			}
			if (doesBlockExist(block.x, block.y, block.z - 1) && blocks[getBlock(block.x, block.y, block.z - 1)]->type == wire && blocks[getBlock(block.x, block.y, block.z - 1)]->state == false) {
				blocks[getBlock(block.x, block.y, block.z - 1)]->state = true;
				checkSurroundingBlocks(glm::vec3(block.x, block.y, block.z - 1));
			}
		}
	}
}
void Blocks::getInput(int blockIndex, glm::vec3 * input)
{
	switch (blocks[blockIndex]->direction) {
	case positiveX:
		*input = blocks[blockIndex]->position + glm::vec3(1, 0, 0);
		break;
	case negativeX:
		*input = blocks[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	case positiveY:
		*input = blocks[blockIndex]->position + glm::vec3(0, 1, 0);
		break;
	case negativeY:
		*input = blocks[blockIndex]->position + glm::vec3(0, -1, 0);
		break;
	case positiveZ:
		*input = blocks[blockIndex]->position + glm::vec3(0, 0, 1);
		break;
	case negativeZ:
		*input = blocks[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	}
}
void Blocks::getOutput(int blockIndex, glm::vec3 * output)
{
	switch (blocks[blockIndex]->direction) {
	case positiveX:
		*output = blocks[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	case negativeX:
		*output = blocks[blockIndex]->position + glm::vec3(1, 0, 0);
		break;
	case positiveY:
		*output = blocks[blockIndex]->position + glm::vec3(0, -1, 0);
		break;
	case negativeY:
		*output = blocks[blockIndex]->position + glm::vec3(0, 1, 0);
		break;
	case positiveZ:
		*output = blocks[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case negativeZ:
		*output = blocks[blockIndex]->position + glm::vec3(0, 0, 1);
		break;
	}
}
void Blocks::getInputs(int blockIndex, glm::vec3* input1, glm::vec3* input2)
{
	switch (blocks[blockIndex]->direction) {
	case positiveX:
		*input1 = blocks[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = blocks[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case negativeX:
		*input1 = blocks[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = blocks[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case positiveY:
		*input1 = blocks[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = blocks[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case negativeY:
		*input1 = blocks[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = blocks[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case positiveZ:
		*input1 = blocks[blockIndex]->position + glm::vec3(1, 0, 0);
		*input2 = blocks[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	case negativeZ:
		*input1 = blocks[blockIndex]->position + glm::vec3(1, 0, 0);
		*input2 = blocks[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	}
}
void Blocks::runLogic()
{
	glm::vec3 input;
	glm::vec3 input2;
	glm::vec3 output;
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->type == wire) {
			blocks[i]->state = false;
		}	
	}
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < blocks.size(); i++) {
			getOutput(i, &output);
			switch (blocks[i]->type) {
			case inverter:
				getInput(i, &input);
				if (doesBlockExist(input.x, input.y, input.z) && blocks[getBlock(input.x, input.y, input.z)]->type == wire  && blocks[getBlock(input.x, input.y, input.z)]->state) {
					blocks[i]->state = false;
				}
				else {
					if (blocks[i]->state && doesBlockExist(output.x, output.y, output.z) && blocks[getBlock(output.x, output.y, output.z)]->type == wire) {
						blocks[getBlock(output.x, output.y, output.z)]->state = true;
						checkSurroundingBlocks(output);
					}
					blocks[i]->state = true;
				}
				break;
			case andGate:
				getInputs(i, &input, &input2);
				if (blocks[i]->state) {
					blocks[getBlock(output.x, output.y, output.z)]->state = true;
					checkSurroundingBlocks(output);
				}
				if (doesBlockExist(input.x, input.y, input.z) && blocks[getBlock(input.x, input.y, input.z)]->type == wire  && blocks[getBlock(input.x, input.y, input.z)]->state && doesBlockExist(input2.x, input2.y, input2.z) && blocks[getBlock(input2.x, input2.y, input2.z)]->type == wire  && blocks[getBlock(input2.x, input2.y, input2.z)]->state) {
					blocks[i]->state = true;
				}
				else {
					blocks[i]->state = false;
				}
				break;
			case orGate:
				getInputs(i, &input, &input2);
				if (blocks[i]->state) {
					blocks[getBlock(output.x, output.y, output.z)]->state = true;
					checkSurroundingBlocks(output);
				}
				if ((doesBlockExist(input.x, input.y, input.z) && blocks[getBlock(input.x, input.y, input.z)]->type == wire  && blocks[getBlock(input.x, input.y, input.z)]->state) || (doesBlockExist(input2.x, input2.y, input2.z) && blocks[getBlock(input2.x, input2.y, input2.z)]->type == wire  && blocks[getBlock(input2.x, input2.y, input2.z)]->state)) {
					blocks[i]->state = true;
				}
				else {
					blocks[i]->state = false;
				}
				break;
			case xorGate:
				getInputs(i, &input, &input2);
				if (blocks[i]->state) {
					blocks[getBlock(output.x, output.y, output.z)]->state = true;
					checkSurroundingBlocks(output);
				}
				if (((doesBlockExist(input.x, input.y, input.z) && blocks[getBlock(input.x, input.y, input.z)]->type == wire  && blocks[getBlock(input.x, input.y, input.z)]->state) && (doesBlockExist(input2.x, input2.y, input2.z) && blocks[getBlock(input2.x, input2.y, input2.z)]->type == wire  && !blocks[getBlock(input2.x, input2.y, input2.z)]->state)) || ((doesBlockExist(input.x, input.y, input.z) && blocks[getBlock(input.x, input.y, input.z)]->type == wire  && !blocks[getBlock(input.x, input.y, input.z)]->state) && (doesBlockExist(input2.x, input2.y, input2.z) && blocks[getBlock(input2.x, input2.y, input2.z)]->type == wire && blocks[getBlock(input2.x, input2.y, input2.z)]->state))) {
					blocks[i]->state = true;
				}
				else {
					blocks[i]->state = false;
				}
				break;
			}
		}
	}
}