#pragma once
#include "Vertex.h"
#include <vector>
#include "Block.h"
class Blocks {
public:
	Blocks();
	VkDevice* device;
	void correctCameraWithBlocks(glm::vec3* cameraMin, glm::vec3* cameraMax, glm::vec3* cameraVel);
	void init(std::vector<Vertex>* _vertices, std::vector<uint32_t>* _indices);
	void addBlock(int x, int y, int z, blockType type);
	void addBlock(int x, int y, int z, blockType type, blockDirection direction);
	int getVectorSize();
	bool removeBlock(int x, int y, int z);
	bool doesBlockExist(int x, int y, int z);
	int getBlock(int x, int y, int z);
	void correctBoundingBox(glm::vec3* min1, glm::vec3* max1, glm::vec3* min2, glm::vec3* max2, glm::vec3* vel);
	void runLogic();
	void checkSurroundingBlocks(glm::vec3 block);
	void getInput(int blockIndex, glm::vec3* input);
	void getOutput(int blockIndex, glm::vec3* output);
	void getInputs(int blockIndex, glm::vec3* input1, glm::vec3* input2);
	std::vector<Block*> blocks;
private:
	std::vector<Vertex>* vertices;
	std::vector<uint32_t>* indices;
};