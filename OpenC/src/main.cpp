// -- header files --
#include <GL/glew.h>    /* tells the cpp preprocessor to include the contents of 
                           glew.h to this file and continue with the rest of the file */
#include <GLFW/glfw3.h> // preprocessor includes glfw3.h to the file and continues
#include <iostream>     // preprocessor includes the iostream component to the file and continues
// -- header files --

/* -- shaders creation--*/
/* Function that is used to create each individual shader
 parameters: unsigned integer and a reference to a string object
 return type: unsigned integer*/
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); /* creates empty shader object & 
                                returns an int by which it can be referenced*/
    const char* src = source.c_str(); /* stores in src a pointer that points
                                         to source*/
    glShaderSource(id, 1, &src, nullptr); /*sets the source code of the shader 
                                            object to the source code in the string*/
    glCompileShader(id); /* Compiles the source code stored in the shader object
                            specified by the integer identifier*/
    // --Error handling --
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); /* Returns the value of 
                    GL_COMPILE_STATUS for the shader object specified by id
                    and stores it in result*/
    if (result == GL_FALSE) // error ocurred
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); /* Returns the value of 
                    GL_INFO_LOG_LENGTH for the shader object specified by id
                    and stores it in length*/
        char* message = (char*)alloca(length * sizeof(char)); /*basic string ptr*/
        glGetShaderInfoLog(id, length, &length, message); /* Returns the info log
                    of the compiled shader, stores it in message*/
        /* printing error message, uses ternary operator :)*/
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : 
        "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        /* printing error message*/

        glDeleteShader(id); /* Frees allocated memory and deletes the id name associated
                            to the created shader*/
        return 0;
    }
    return id; /*returns the id reference of the created shader if no errors ocurred*/
}

/* Function that is used to create the vertex and fragment shader
 parameters: two string object references: for the vertexShader and for fragmentShader 
 return type: integer*/
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram(); /* Creates an empty program object and it
                                                 returns a value from which it can be 
                                                 referenced*/
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); /* calls the
    CompileShader method to create the vertexShader, saves id of the created shader in vs*/
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); /* calls the
    CompileShader method to create the fragmentShader, saves id of the created shader in fs*/

    glAttachShader(program, vs); /* Attaches the vertex shader to the progam object*/
    glAttachShader(program, fs); /* Attaches the fragment shader to the progam object*/
    glLinkProgram(program); /* Used to link the program object*/
    glValidateProgram(program); /* Makes sure that the components in the program object
                            can be executed in the current OpenGL state*/
    glDeleteShader(vs); /* Frees allocated memory and deletes the id vs associated
                            to the vertex shader*/
    glDeleteShader(fs); /* Frees allocated memory and deletes the id fs associated
                            to the fragment shader*/
    return program; /* returns the integer id that references the program object*/
}
/* -- shaders creation--*/

int main(void)
{
    GLFWwindow* window; /*pointer to a GLFWwindow*/

    if (!glfwInit()) // Initializes the GLFW library. 
        return -1;   // If successful returns true 
        
    glewInit(); /* Initializes the GLEW entrypoints*/

    /* Creates a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL); /
    if (!window) /* error creating window*/
    {
        glfwTerminate(); /*terminates the GLFW library*/
        return -1;
    }

    glfwMakeContextCurrent(window); /* Used to make the window's 
                                    context current*/

    if (glewInit() != GLEW_OK) {  /* error initializing GLEW*/
        std:: cout << "Error in glew" << std:: endl;
        return -1;
    }

    std:: cout << glGetString(GL_VERSION)<<std:: endl;/* prints
                                                OpenGL version*/

    /* -- vertex buffer-- */
    float positions[6] = { // array definition of the x and y
       -0.5f, -0.5f,       // coordinates of the vertices of 
        0.5f, -0.5f,       // the triangle 
        0.0f, 0.5f         // (-.5, -.5),(0.5,-.5),(0,.5)
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer); /* returns 1 buffer obj name in buffer*/
    glBindBuffer(GL_ARRAY_BUFFER, buffer); /* binds the buffer to
                                            the GL_ARRAY_BUFFER*/
    
    /*creates a data store for the buffer object*/                                       
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    /* specifies the data format and location of the array of generic vertex 
       attributes at index 0 that will be used when doing the rendering*/
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0); /* enables the generic vertex attribute 
                                     array specified by index 0*/
    /* -- VS and FS program creation --*/
    /*Creates a string variable containing the vertex shader program*/
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    /*Creates a string variable containing the fragment shader program*/
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 1.0, 0.0);\n"
        "}\n";
    /* -- VS and FS program creation --*/
    /*calls CreateShader function to create vertex and fragment shader
      stores in shader the int id of the created program obj*/
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader); /* used to install the program obj specified
                    by shader as part of the current rendering state*/

    /* Loop prevails until the user closes the window */
    while (!glfwWindowShouldClose(window)) /* returns the value of the
                                            close flag of the window*/
    {
        glClear(GL_COLOR_BUFFER_BIT); /* used to set the bitplane area
             of the window to the values on the  GL_COLOR_BUFFER_BIT*/

        glDrawArrays(GL_TRIANGLES, 0, 3); /*draws triangle to screen*/
        
        /* Swap front and back buffers of the window*/
        glfwSwapBuffers(window);

        glfwPollEvents(); /* Processes all pending events in queue*/
    }

    glfwTerminate(); /* Terminates the GLFW library*/
    return 0;
}