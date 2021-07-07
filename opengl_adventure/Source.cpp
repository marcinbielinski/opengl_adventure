#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "Shader.h"

// VERTEX shader source to dynamically compile it at run-time
//const char* vertexShaderSource =    "#version 450 core\n"
//                                    "layout(location = 0) in vec3 aPos; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
//                                    "}\n";

//const char* vertexShaderSource =    "#version 450 core\n"
//                                    "layout(location = 0) in vec3 aPos; \n"
//                                    "out vec4 vertexColor; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    gl_Position = vec4(aPos, 1.0); \n"
//                                    "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); \n"
//                                    "}\n";

// VERTEX SHADER ADJUSTED FOR THREE-WAY - RECEIVE COLOR VALUE AS A VERTEX ATTRIB INPUT
//const char* vertexShaderSource =    "#version 450 core\n"
//                                    "layout(location = 0) in vec3 aPos; \n"
//                                    "layout(location = 1) in vec3 aColor; \n"
//                                    "out vec3 ourColor; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    gl_Position = vec4(aPos, 1.0); \n"
//                                    "    ourColor = aColor; \n"
//                                    "}\n";
// VERTEX SHADER ADJUSTED FOR THREE-WAY OFFSET WITH OUT KEYWORD
const char* vertexShaderSource =    "#version 450 core\n"
                                    "layout(location = 0) in vec3 aPos; \n"
                                    "layout(location = 1) in vec3 aColor; \n"
                                    "out vec3 ourPosition; \n"

                                    "void main()\n"
                                    "{\n"
                                    "    gl_Position = vec4(aPos, 1.0); \n"
                                    "    // ourColor = aColor; \n"
                                    "    ourPosition = aPos; \n"
                                    "}\n";

// FRAGMENT shader source
//const char* fragmentShaderSource =  "#version 450 core\n"
//                                    "out vec4 FragColor; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
//                                    "}\n";

// DARK RED
//const char* fragmentShaderSource =  "#version 450 core\n"
//                                    "out vec4 FragColor; \n"
//                                    "in vec4 vertexColor; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    FragColor = vertexColor; \n"
//                                    "}\n";

// UNIFORM SHADER - global variable
//const char* fragmentShaderSource =  "#version 450 core\n"
//                                    "out vec4 FragColor; \n"
//                                    "uniform vec4 ourColor; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    FragColor = ourColor; \n"
//                                    "}\n";

// THREE-WAY TRIANGLE SHADER
//const char* fragmentShaderSource =  "#version 450 core\n"
//                                    "out vec4 FragColor; \n"
//                                    "in vec3 ourColor; \n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "   FragColor = vec4(ourColor, 1.0); \n"
//                                    "}\n";
 
// UNIFORM SHADER - OFFSET- global variable
const char* fragmentShaderSource =  "#version 450 core\n"
                                    "out vec4 FragColor; \n"
                                    "in vec3 ourPosition; \n"

                                    "void main()\n"
                                    "{\n"
                                    "    FragColor = vec4(ourPosition, 1.0); \n"
                                    "}\n";


// CUSTOM SHADER
//Shader ourShader("path/to/shaders/shader.vs", "path/to/shaders/shader.fs");

//ourShader.use();
//ourShader.setFloat("someUniform", 1.0f);
//DrawStuff();

// ------------------ VERTICES (ENABLE ONE) --------------------
// ONE TRIANGLE
//float vertices[] = {
//    -0.5f, -0.5f, 0.0f, 
//     0.5f, -0.5f, 0.0f, 
//     0.0f,  0.5f, 0.0f   
//};

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

// THREE-WAY COLORED TRIANGLE (GRADIENT)
//float vertices[] = {
//    // positions        //colors
//     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
//    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
//     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
//};

// THREE-WAY COLORED TRIANGLE - UPSIDE DOWN(GRADIENT)
//float vertices[] = {
//    // positions        //colors
//     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // TOP right
//    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // TOP left
//     0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // BOTTOM
//};

// THREE-WAY COLORED TRIANGLE - UPSIDE DOWN - WITH OFFSET (GRADIENT)
float vertices[] = {
    // positions        //colors
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // TOP right
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // TOP left
     0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // BOTTOM
};

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
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // ADJUSTED FOR THREE-WAY TRIANGLE
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

        // Change color over time with global uniform shader
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ RUN OPTIONS ++++++++
        // run program (ONE TRIANGLE (ENABLE ONE))
        //glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // LAST PARAM - AMOUNT OF VERTICES
        
        // run program (TWO TRIANGLES (ENABLE ONE))
        /*glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

        // POLYGON MODE - DRAW PRIMITIVES
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindVertexArray(0);
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwTerminate();
    //int nrAttributes;
    //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    //std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
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