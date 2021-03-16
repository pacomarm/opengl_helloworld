/*This code is based on The Cherno OpenGL tutorial in https://youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2 
*/
#include <GL/glew.h>    /* tells c++ preprocessor to include contents of glew.h to the file and continue with the rest of this file */
#include <GLFW/glfw3.h> // preprocessor includes glfw3.h to the file and continues

#include <iostream> // preprocessor includes the iostream component to the file
#include <fstream>  // preprocessor includes the fstream component to the file
#include <string>   // preprocessor includes the string header to the file
#include <sstream>  // preprocessor includes the sstream header to the file

#include "Renderer.h" // preprocessor includes the "Renderer" header to the file

#include "VertexBuffer.h"       // preprocessor includes the "Vertex Buffer" header to the file
#include "VertexBufferLayout.h" // preprocessor includes the "Vertex Buffer Layout" header to the file
#include "IndexBuffer.h"        // preprocessor includes the "Index Buffer" header to the file
#include "VertexArray.h"        // preprocessor includes the "Vertex Array" header to the file
#include "Shader.h"             // preprocessor includes the "Shader" header to the file
#include "Texture.h"            // preprocessor includes the "Texture" header to the file

/*New additions*/
#include <glm/glm.hpp>                  // preprocessor includes glm.hpp to the file and continues
#include <glm/gtc/matrix_transform.hpp> // preprocessor includes matrix_transform.hpp to the file and continues
#include <glm/gtc/type_ptr.hpp>         // preprocessor includes type_ptr.hpp to the file and continues

/*-------------*/

int main(void) // main function
{
    GLFWwindow *window; /* creates a pointer that will point to a GLFWwindow*/

    if (!glfwInit()) // Initializes the GLFW library.
        return -1;   // If error occurs exits with -1

    /* these 3 lines set hints for next call of glfwCreateWindow.*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Diamond Ore", NULL, NULL); /* used to create a windowed mode window and its OpenGL context */
    if (!window)                                                    // if error occured creating window
    {
        glfwTerminate(); /*terminate GLFW library*/
        return -1;
    }

    glfwMakeContextCurrent(window); /* makes the window's context current*/
    glfwSwapInterval(1);            // used to set the swap interval for the current context.

    if (glewInit() != GLEW_OK) /* error occured initializing GLEW*/
        std::cout << "Error!" << std::endl;

    /*New additions*/
    glEnable(GL_DEPTH_TEST); // used to enable the server-side GL_DEPTH_TEST capability
    {
        float positions[] = {                                 // new positions array
                             -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // each line is a vertex, 6 vertices are needed to make a face (square)
                             0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // each block of code is a face, as a cube is made with 6 faces, then
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // 6 faces * 6 vertices = 36 vertices
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                             -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                             -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                             -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                             -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                             -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                             0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                             0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                             0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                             -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                             -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                             0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                             -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
        /*-------------*/

        GLCall(glEnable(GL_BLEND));                                // used to enable the blend of the computed fragment color with the values in the color buffers
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); /* used to define the operation of blending, in order to use this glBlend
       must be enabled */

        VertexArray va; // creates a vertex array object
        /*New additions*/
        VertexBuffer vb(positions, sizeof(positions)); // creation of vertex buffer with the bigger positions vector
        /*-------------*/
        VertexBufferLayout layout; // creates the Vertex buffer layout object
        layout.Push<float>(3);     // adds attributes to the Vertex buffer layout object
        layout.Push<float>(2);     // adds more attributes to the Vertex buffer layout object
        va.AddBuffer(vb, layout);  // adds the vertex buffer and layout obj to vertex array

        Shader shader("res/shaders/Basic.shader");              // creates the shader object using the defined Shader in the Basic.shader file
        shader.Bind();                                          //binds the shader
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f); // used to set a 4d vector on the shader
        Texture texture("res/textures/texture.png");            // creates a texture obj and reads the given texture texture.png
        texture.Bind(0);                                        // binds the texture
        shader.SetUniform1i("u_Texture", 0);                    // used to set a scalar program uniform given a string

        va.Unbind();     // used to unbind the vertex array
        vb.Unbind();     // used to unbind the vertex buffer
        shader.UnBind(); // used to unbind the shader

        Renderer renderer; // creates the renderer object

        while (!glfwWindowShouldClose(window)) /* the loop prevails until the user closes the window */
        {
            renderer.Clear(); // clears the renderer

            /*New additions - Transformations - */
            glm::mat4 model = glm::mat4(1.0f);                                                         // creates the model, which is a 4x4 identity matrix
            glm::mat4 view = glm::mat4(1.0f);                                                          // creates the view, which is a 4x4 identity matrix
            glm::mat4 projection = glm::mat4(1.0f);                                                    // creates the projection, which is a 4x4 identity matrix
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));             /*Makes a rotation 4x4 matrix from an axis vector and an angle. Used to create rotation transformation*/
            model = glm::translate(model, glm::vec3(0.8f, -0.3f, 0.1f));                               /*Makes a translation 4x4 matrix from a 3d vector. Used to create translation transformation*/
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));                                 /*Makes a translation 4x4 matrix from a 3d vector. Used to create translation transformation*/
            projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f); /* Creates a matrix for a symetric perspective-view frustum based on the default handedness. Used to create perspective transformation*/
            glm::mat4 mvp = projection * view * model;                                                 // creates model view Projection (MVP) 4x4 matrix
            /*-------------*/

            shader.Bind();                                          // bind the shader
            shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f); // used to set a 4d vector on the shader

            /*New additions*/
            shader.SetMat4("u_MVP", mvp); // sets the 4x4 MVP matrix to the shader object
            renderer.Draw(va, shader);    //draw call by the rendered given the vertex array and shader
            /*-------------*/

            glfwSwapBuffers(window); /* used to swap front and back buffers of the window*/

            glfwPollEvents(); /* call used to process all pending events in queue*/
        }
        //reached when user closes the window
    }
    glfwTerminate(); /* Terminates the GLFW library*/
    return 0;        // normal program termination
}
