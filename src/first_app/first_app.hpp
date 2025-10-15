#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"

namespace lve
{

class FirstApp
{
	LveWindow	lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
	LveDevice	lveDevice{ lveWindow };
	LveSwapChain lveSwapChain{ lveDevice, lveWindow.getExtent() };
	std::unique_ptr<LvePipeline> lvePipeline;
	VkPipelineLayout pipelineLayout;
	std::vector<VkCommandBuffer> commandBuffers;

	void createPipelineLayout();
	void createPipeline();
	void createCommandBuffers();
	void drawFrame();

public:

	FirstApp();
	~FirstApp();

	// DELETE COPY CONSTRUCTORS
	FirstApp(const FirstApp&) = delete;
	FirstApp& operator= (const FirstApp&) = delete;

	static constexpr int WIDTH{ 800 };
	static constexpr int HEIGHT{ 600 };

	void run();
};

};