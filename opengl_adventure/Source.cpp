#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// VERTEX shader source to dynamically compile it at run-time
const char* vertexShaderSource = "#version 450 core\n"
"layout(location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
"}\n";

// FRAGMENT shader source
const char* fragmentShaderSource = "#version 450 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"}\n";

// ------------------ VERTICES (ENABLE ONE) --------------------
// ONE TRIANGLE
float vertices[] = {
    -0.5f, -0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f, 
     0.0f,  0.5f, 0.0f   
};

// RECTANGLE
//float vertices[] = {
//      0.5f,  0.5f, 0.0f,   // top right
//      0.5f, -0.5f, 0.0f,   // bottom right
//     -0.5f, -0.5f, 0.0f,   // bottom left
//     -0.5f,  0.5f, 0.0f    // top left
//
//};

 //TWO TRIANGLES
//float vertices[] = {
//    -0.5f, -0.5f, 0.0f, // left
//    -0.0f, -0.5f, 0.0f, // right
//    -0.5f,  0.5f, 0.0f, // top
//
//     0.0f, -0.5f, 0.0f, // left
//     0.5f, -0.5f, 0.0f, // right
//     0.5f,  0.5f, 0.0f  // top
//};

// ------------------------------------------------------------

// ------------------ INDICES (ENABLE ONE) --------------------

unsigned int indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

// ------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);


int main() {
    // initialize GLFW
    glfwInit();
    // GLFW config
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // creating window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Adventure", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD - manage function pointers (before any OpenGL function)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // tell OpenGL how to display the data and coordinates with respect to the window
    glViewport(0, 0, 800, 600);


    // // call this function on every window resize by registering it
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ----- INITIALIZATION CODE (DONE ONCE (UNLESS OBJECT FREQUENTLY CHANGES)) -----
    // ------------- VAO vertex array object --------------------------------
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // SECOND VAO ?
    /*unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);*/
    
    // ------------- VBO vertex buffer object --------------------------------
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // SECOND VBO ?
    /*unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/

    // ------------- EBO element buffer object --------------------------------
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // tell OpenGL how to interpret vertex data (per vertex attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ----------COMPILE VERTEX SHADER------------------------------------------
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // takes the shader object to compile te as its first argument
    // second one specifies how many strings we're passing as source code
    // third param is the actual source code of vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check if compilation was successful after the call to glCompileShader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // possible errors
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    // ----------COMPILE FRAGMENT SHADER---------------------------------------
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check if compilation was successful after the call to glCompileShader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // pissbile errors
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    // --------PROGRAM OBJECT--------------------------------------------------

    // creates program and returns the ID ref to the newly created program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // attach previously copiled shaders to the program object
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // program LINKING POSSIBLE ERRORS
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    // delete previously linked shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // render loop (check if GLFW has been instructed to close; if true stop running)
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ RUN OPTIONS ++++++++
        // run program (ONE TRIANGLE (ENABLE ONE))
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); // LAST PARAM - AMOUNT OF VERTICES

        // run program (TWO TRIANGLES (ENABLE ONE))
        /*glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

        // POLYGON MODE - DRAW PRIMITIVES
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindVertexArray(0);
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}

// resize callback function (when user interferes with the window size)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}