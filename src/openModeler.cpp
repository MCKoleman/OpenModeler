#include "openModeler.h"

int main()
{
    // Init window
    GLFWwindow* window = OpenGLInitWindow(SCR_WIDTH, SCR_HEIGHT, "OpenModeler");
    if (window == nullptr)
        return -1;

    // Read Options
    // ------------
    Options options = ReadOptions("../config.txt");

    // Build and compile shader program
    // ------------------------------------
    ProgramIDs* ids = new ProgramIDs();
    ids->shaderProgram = LoadShaderProgram(options.phong == 1);

    // Create scene
    // ------------
    Scene* scene = new Scene();
    scene->SetCameraFromOptions(&options);
    scene->SetLight(new Light(
        glm::vec3(5.0f, 5.0f, 5.0f),        // Light pos
        glm::vec3(-1.0f, -1.0f, -1.0f),     // Light dir
        glm::vec3(1.0f, 1.0f, 1.0f),        // Light color
        0.1f,                               // Ambient strength
        0.5f));                              // Specular strength);
    scene->GetMats()->AddMat("default", options.defaultColor);

    // Read mesh
    // ---------
    Mesh* displayMesh = scene->GetCurMesh();

    // Read mesh from file
    ReadObjFromFile(displayMesh, scene->GetMats(), "../models/", options.objName);
    displayMesh->Scale(glm::vec3(options.objScale, options.objScale, options.objScale));
    displayMesh->SetPos(options.objPos);

    // Load up model into vertice and indice structures
    // Get vertices
    int vertsSize = displayMesh->GetVertCount() * 9;
    float* vertices = new float[vertsSize];
    int indicesSize = displayMesh->GetIndexCount();
    unsigned int* indices = new unsigned int[indicesSize];
    scene->GetVAO(vertices, vertsSize, indices, indicesSize);

    // Print vertices and indices
    if (options.print == 1) {
        PrintArray("Printing vertices:", vertices, vertsSize, 9);
        PrintArray("Printing indices:", indices, indicesSize, 3);
    }

    // Init VAO, VBO, and EBO
    OpenGLInitBuffers(ids, vertsSize, vertices, indicesSize, indices);

    // Enable wireframe if requested in options
    if (options.wireframe == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // Init variables to track user input. Speed constants declared in order:
    // CamMove, CamTurn, ModelMove, ModelTurn, ModelScale, MouseMove, MouseTurn
    SpeedConsts speeds = SpeedConsts(2.0f, 1.0f, 0.3f, 30.0f, 1.0f, 0.1f, 0.1f);
    InputLocks* locks = new InputLocks();
    int prevX = -1;
    int prevY = -1;

    // Track time
    double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = 0.0f;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Get deltaTime
        lastTime = currentTime;
        currentTime = glfwGetTime();
        deltaTime = float(currentTime - lastTime);

        // Process input and render
        ProcessInput(window, scene, locks, deltaTime, &speeds, &prevX, &prevY);
        OpenGLDraw(scene, ids, indicesSize, indices);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear up dynamic memory usage
    // -----------------------------
    OpenGLCleanup(ids);
    delete[] vertices;
    delete[] indices;
    delete locks;
    delete scene;
    delete ids;

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}