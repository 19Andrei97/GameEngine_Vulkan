#include <pch.h>

#include "first_app.hpp"

namespace lve
{

FirstApp::FirstApp()
{
	createPipelineLayout();
	createPipeline();
	createCommandBuffers();
}

FirstApp::~FirstApp()
{
	vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
}

void FirstApp::run()
{
	while (!lveWindow.shouldClose())
	{
		glfwPollEvents();
		drawFrame();
	}

	vkDeviceWaitIdle(lveDevice.device());
}

void FirstApp::createPipelineLayout()
{
	VkPipelineLayoutCreateInfo pipeline_layout_info{};
	pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipeline_layout_info.setLayoutCount = 0;
	pipeline_layout_info.pSetLayouts = nullptr;
	pipeline_layout_info.pushConstantRangeCount = 0;
	pipeline_layout_info.pPushConstantRanges = nullptr;

	if (vkCreatePipelineLayout(lveDevice.device(), &pipeline_layout_info, nullptr, &pipelineLayout) != VK_SUCCESS)
		throw std::runtime_error("failed to create pipeline layout.");
}

void FirstApp::createPipeline()
{
	PipelineConfigInfo pipeline_config{};
	LvePipeline::defaultPipelineConfigInfo(pipeline_config, lveSwapChain.width(), lveSwapChain.height());

	pipeline_config.renderPass = lveSwapChain.getRenderPass();
	pipeline_config.pipelineLayout = pipelineLayout;

	lvePipeline = std::make_unique<LvePipeline>(lveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipeline_config);
}

void FirstApp::createCommandBuffers()
{
	commandBuffers.resize(lveSwapChain.imageCount());

	VkCommandBufferAllocateInfo alloc_info{};
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandPool = lveDevice.getCommandPool();
	alloc_info.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

	if (vkAllocateCommandBuffers(lveDevice.device(), &alloc_info, commandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate command buffers.");

	for (int i{ 0 }; i < commandBuffers.size(); ++i)
	{
		VkCommandBufferBeginInfo begin_info{};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		
		if(vkBeginCommandBuffer(commandBuffers[i], &begin_info) != VK_SUCCESS)
			throw std::runtime_error("failed to begin recording command buffer.");

		VkRenderPassBeginInfo render_pass_info{};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		render_pass_info.renderPass = lveSwapChain.getRenderPass();
		render_pass_info.framebuffer = lveSwapChain.getFrameBuffer(i);

		std::array<VkClearValue, 2> clear_values{};
		clear_values[0].color = { 0.1f, 0.1f, 0.1f, 1.f };
		clear_values[1].depthStencil = { 1.f, 0 };
		render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
		render_pass_info.pClearValues = clear_values.data();

		render_pass_info.renderArea.offset = { 0, 0 };
		render_pass_info.renderArea.extent = lveSwapChain.getSwapChainExtent();

		vkCmdBeginRenderPass(commandBuffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

		lvePipeline->bind(commandBuffers[i]);
		vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);

		if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
			throw std::runtime_error("failed to record command buffer.");
	}
}


void FirstApp::drawFrame()
{
	uint32_t image_index;
	auto result = lveSwapChain.acquireNextImage(&image_index);

	if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("failed to aquire swap chain image.");

	result = lveSwapChain.submitCommandBuffers(&commandBuffers[image_index], &image_index);

	if(result != VK_SUCCESS)
		throw std::runtime_error("failed to present swap chain image.");
}

};