#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct keyValues { bool w = false; bool a = false; bool s = false; bool d = false; bool f = false; bool shift = false; bool space = false; bool ctrl = false; bool tab = false; bool n1 = false; bool n2 = false; bool n3 = false; bool n4 = false; bool n5 = false; bool n6 = false; bool n7 = false; bool n8 = false; bool n9 = false; bool n0 = false;   bool mouseLeft = false; bool mouseRight = false; };
keyValues keys;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		keys.n1 = true;
	}
	if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
		keys.n1 = false;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		keys.n2 = true;
	}
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
		keys.n2 = false;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		keys.n3 = true;
	}
	if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
		keys.n3 = false;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		keys.n4 = true;
	}
	if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
		keys.n4 = false;
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		keys.n5 = true;
	}
	if (key == GLFW_KEY_5 && action == GLFW_RELEASE) {
		keys.n5 = false;
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		keys.n6 = true;
	}
	if (key == GLFW_KEY_6 && action == GLFW_RELEASE) {
		keys.n6 = false;
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		keys.n7 = true;
	}
	if (key == GLFW_KEY_7 && action == GLFW_RELEASE) {
		keys.n7 = false;
	}
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		keys.n8 = true;
	}
	if (key == GLFW_KEY_8 && action == GLFW_RELEASE) {
		keys.n8 = false;
	}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		keys.n9 = true;
	}
	if (key == GLFW_KEY_9 && action == GLFW_RELEASE) {
		keys.n9 = false;
	}
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		keys.n0 = true;
	}
	if (key == GLFW_KEY_0 && action == GLFW_RELEASE) {
		keys.n0 = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		keys.space = true;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		keys.space = false;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		keys.shift = true;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		keys.shift = false;
	}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		keys.ctrl = true;
	}
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
		keys.ctrl = false;
	}

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		keys.tab = true;
	}
	if (key == GLFW_KEY_TAB && action == GLFW_RELEASE) {
		keys.tab = false;
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		keys.w = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		keys.a = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		keys.s = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		keys.d = true;
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		keys.f = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		keys.w = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		keys.a = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		keys.s = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		keys.d = false;
	}
	if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
		keys.f = false;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		keys.mouseLeft = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		keys.mouseLeft = false;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		keys.mouseRight = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		keys.mouseRight = false;
	}
}
	GLFWwindow* window;

	void initWindow() {

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);//may need to remove this

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetWindowFocusCallback(window, window_focus_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeCallback(window, WorkSpace::onWindowResized);
	}

	static void onWindowResized(GLFWwindow* window, int width, int height) {
		if (width == 0 || height == 0) return;

		WorkSpace* app = reinterpret_cast<WorkSpace*>(glfwGetWindowUserPointer(window));
		app->recreateSwapChain();
	}
	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {

		}
	}
	void createSurface() {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface.replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	//returns the required list of extensions based on the validation layers are enabled or not 
	std::vector<const char*> getRequiredExtensions() {
		std::vector<const char*> extensions;

		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (unsigned int i = 0; i < glfwExtensionCount; i++) {
			extensions.push_back(glfwExtensions[i]);
		}

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}


int main() {
	WorkSpace app;
	try {
		app.run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}