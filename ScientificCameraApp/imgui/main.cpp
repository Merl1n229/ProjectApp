#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// Dummy Camera class
class Camera {
public:
    std::vector<float> getData() {
        // Dummy data generation
        std::vector<float> data(100); // Assuming data size is 100
        for (int i = 0; i < 100; ++i) {
            data[i] = static_cast<float>(rand()) / RAND_MAX; // Dummy data generation
        }
        return data;
    }
};

// Function to generate dummy data
std::vector<float> generateDummyData() {
    std::vector<float> data(100); // Assuming data size is 100
    for (int i = 0; i < 100; ++i) {
        data[i] = static_cast<float>(rand()) / RAND_MAX; // Dummy data generation
    }
    return data;
}

// Initialize Dear ImGui
void initImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
}

// Render ImGui GUI
void renderGUI() {
    static std::vector<float> data; // Data vector

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Main menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open")) {
                // Handle open action
                // For simplicity, let's print a message
                std::cout << "Open action triggered" << std::endl;
            }
            if (ImGui::MenuItem("Save")) {
                // Handle save action
                // For simplicity, let's print a message
                std::cout << "Save action triggered" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Main window
    ImGui::Begin("Data Viewer");

    static bool recording = false;

    // Buttons
    if (!recording && ImGui::Button("Start Recording")) {
        // Handle start recording action
        recording = true;
        std::cout << "Recording started" << std::endl;
    }
    ImGui::SameLine();
    if (recording && ImGui::Button("Stop Recording")) {
        // Handle stop recording action
        recording = false;
        std::cout << "Recording stopped" << std::endl;
    }

    ImGui::Separator();

    // Button to load data
    if (ImGui::Button("Load Data")) {
        // Load data from camera
        Camera camera;
        data = camera.getData(); // Get data from camera
    }

    // Real-time plot
    if (!data.empty()) {
        ImGui::PlotLines("Data Plot", data.data(), data.size());
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    if (gl3wInit() != GL3W_OK) {
        std::cerr << "Failed to initialize OpenGL loader" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    initImGui(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start the ImGui frame
        renderGUI();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
