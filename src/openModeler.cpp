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
# define INDEXED options.vertexModel == 1
# define IS_PHONG options.phong == 1

    // build and compile our shader program
    // ------------------------------------
    unsigned int shaderProgram;
    // Load phong shader
    if (IS_PHONG)
        shaderProgram = LoadShaders("../shaders/phongShader.vertex", "../shaders/phongShader.frag");
    // Load gouraud shader
    else
        shaderProgram = LoadShaders("../shaders/gouraudShader.vertex", "../shaders/gouraudShader.frag");

    // Create camera from options
    Camera camera = Camera(&options);

    // Create light
    Light dirLight = Light(
        glm::vec3(5.0f, 5.0f, 5.0f),        // Light pos
        glm::vec3(-1.0f, -1.0f, -1.0f),     // Light dir
        glm::vec3(1.0f, 1.0f, 1.0f),        // Light color
        0.1f,                               // Ambient strength
        0.5f);                              // Specular strength

    // Read mesh
    // ---------
    Mesh* displayMesh = new Mesh();
    displayMesh->defaultMat = options.defaultColor;

    // Read mesh from file
    ReadObjFromFile(displayMesh, "../models/", options.objName);
    displayMesh->Scale(glm::vec3(options.objScale, options.objScale, options.objScale));
    displayMesh->SetPos(options.objPos);

    // Load up model into vertice and indice structures
    // Get vertices
    int vertsSize = displayMesh->GetVertCount() * 9;
    float* vertices = new float[vertsSize];
    displayMesh->ConvertToVertData(vertices);

    // Get indices
    int indicesSize = displayMesh->GetIndexCount();
    unsigned int* indices = new unsigned int[indicesSize];
    displayMesh->ConvertToIndexData(indices);

    //unsigned int numVertices = displayMesh->GetVertCount();

    // Print vertices and indices
    if (options.print == 1) {
        PrintArray("Printing vertices:", vertices, vertsSize, 9);
        if (INDEXED)
            PrintArray("Printing indices:", indices, indicesSize, 3);
    }

    // Init VAO, VBO, and EBO
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertsSize * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(indices[0]), indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // Generate light
    //unsigned int lightVAO;
    //glGenVertexArrays(1, &lightVAO);
    //glBindVertexArray(lightVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // Get uniform locations
    unsigned int matrixID = glGetUniformLocation(shaderProgram, "MVP");
    unsigned int modelID = glGetUniformLocation(shaderProgram, "Model");
    unsigned int normalModelID = glGetUniformLocation(shaderProgram, "NormalModel");
    unsigned int lightPosID = glGetUniformLocation(shaderProgram, "LightPos");
    unsigned int lightColorID = glGetUniformLocation(shaderProgram, "LightColor");
    unsigned int viewPosID = glGetUniformLocation(shaderProgram, "ViewPos");
    unsigned int ambientStrengthID = glGetUniformLocation(shaderProgram, "AmbientStrength");
    unsigned int specularStrengthID = glGetUniformLocation(shaderProgram, "SpecularStrength");

    // Get initial mvp
    glm::mat4 mvp = CalcMVP(&camera, displayMesh);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Enable culling
    glEnable(GL_CULL_FACE);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable wireframe if requested in options
    if (options.wireframe == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // Init variables to track user input. Speed constants declared in order:
    // CamMove, CamTurn, ModelMove, ModelTurn, ModelScale, MouseMove, MouseTurn
    SpeedConsts speeds = SpeedConsts(2.0f, 1.0f, 0.3f, 30.0f, 1.0f, 0.1f, 0.1f);
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

        // input
        // -----
        ProcessInput(window, &camera, displayMesh, deltaTime, &speeds, &prevX, &prevY);

        // render
        // ------
        glClearColor(0.90f, 0.90f, 0.90f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the object
        glUseProgram(shaderProgram);

        // Apply MVP
        glm::mat4 model = GetModelMatrix(displayMesh);
        glm::mat4 view = GetViewMatrix(&camera);
        glm::mat4 projection = GetProjectionMatrix(&camera);
        glm::mat3 normalModel = glm::mat3(glm::transpose(glm::inverse(model)));
        mvp = projection * view * model;
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix3fv(normalModelID, 1, GL_FALSE, &normalModel[0][0]);

        // Apply lighting
        glUniform1f(ambientStrengthID, dirLight.ka);
        glUniform1f(specularStrengthID, dirLight.ks);
        glUniform3fv(lightPosID, 1, &dirLight.pos[0]);
        glUniform3fv(lightColorID, 1, &dirLight.color[0]);
        glUniform3fv(viewPosID, 1, &camera.pos[0]);
        glBindVertexArray(VAO);

        // Draw indexed EBO
        glDrawElements(GL_TRIANGLES, indicesSize * sizeof(indices[0]), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Clear up dynamic memory usage
    // -----------------------------
    delete[] vertices;
    delete[] indices;
    delete displayMesh;

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}