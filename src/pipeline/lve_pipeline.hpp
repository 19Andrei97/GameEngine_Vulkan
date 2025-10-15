#pragma once

#include "lve_device.hpp"

namespace lve
{

struct PipelineConfigInfo 
{ 
	PipelineConfigInfo(const PipelineConfigInfo&) = delete;
	PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

	VkViewport								viewport;
	VkRect2D								scissor;
	VkPipelineViewportStateCreateInfo		viewportInfo;
	VkPipelineInputAssemblyStateCreateInfo	inputAssemblyInfo;
	VkPipelineRasterizationStateCreateInfo	rasterizationInfo;
	VkPipelineMultisampleStateCreateInfo	multisampleInfo;
	VkPipelineColorBlendAttachmentState		colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo		colorBlendInfo;
	VkPipelineDepthStencilStateCreateInfo	depthStencilInfo;
	VkPipelineLayout						pipelineLayout = VK_NULL_HANDLE;
	VkRenderPass							renderPass = VK_NULL_HANDLE;
	uint32_t								subpass = 0;
};

class LvePipeline
{
	LveDevice&		lve_device;
	VkPipeline		graphics_pipeline;
	VkShaderModule	vert_shader_module;
	VkShaderModule	frag_shader_module;

	static std::vector<char> readFile(const std::string& filepath);
	
	void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& config_info);

	void createShaderModule(const std::vector<char>& code, VkShaderModule* shader_module);

public:

	LvePipeline(LveDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& config_info);

	~LvePipeline();

	LvePipeline(const LvePipeline&) = delete;
	void operator=(const LvePipeline&) = delete;

	static void defaultPipelineConfigInfo(PipelineConfigInfo& config_info, uint32_t width, uint32_t height);

	void bind(VkCommandBuffer command_buffer);

};

};