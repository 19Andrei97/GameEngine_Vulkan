#pragma once

#include "lve_device.hpp"

namespace lve
{

	class LveModel
	{
	public:
		struct Vertex
		{
			glm::vec2 position;

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};

	private:

		LveDevice&		lve_device;
		VkBuffer		vertex_buffer;
		VkDeviceMemory	vertex_buffer_memory;
		uint32_t		vertex_count;

		void createVertexBuffers(const std::vector<Vertex>& vertices);

	public:

		LveModel(LveDevice& device, const std::vector<Vertex>& vertices);
		~LveModel();

		// DELETE COPY CONSTRUCTORS
		LveModel(const LveModel&) = delete;
		LveModel& operator= (const LveModel&) = delete;

		void bind(VkCommandBuffer command_buffer);
		void draw(VkCommandBuffer command_buffer);

	};


};