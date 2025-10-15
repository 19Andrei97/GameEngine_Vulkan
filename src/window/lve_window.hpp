#pragma once

namespace lve
{

class LveWindow
{
	GLFWwindow*		window;

	std::string		window_name;
	const int		width;
	const int		height;

	void initWindow();

public:

	LveWindow(int w, int h, std::string name);
	~LveWindow();

	// DELETE COPY CONSTRUCTORS
	LveWindow(const LveWindow&) = delete;
	LveWindow& operator= (const LveWindow&) = delete;

	bool shouldClose() { return glfwWindowShouldClose(window); };
	VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; };

	void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
};

};