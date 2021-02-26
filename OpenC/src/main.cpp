/*This code uses Modern OpenGL to render geometry, 
    and uses an abstraction of the VertexBuffer, VertexArray, and Shader.
  The code is based on The Cherno OpenGL tutorial in https://youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
*/
#include <GL/glew.h>       
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>  
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // to create the vertex array
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE
    );


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Rendering a lebron james", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);  //to synchronize the animation

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        // include the texture positions to be mapped
        float positions[] = {
            -0.5f, -0.5f, 0.f, 0.f,      // 0 the bottom left
             0.5f, -0.5f, 1.f, 0.f,      // 1 the bottom right side
             0.5f,  0.5f, 1.f, 1.f,      // 1 the top right
            -0.5f,  0.5f, 0.f, 1.f,      // 2 the top left
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        //defining how openGL is going to blend alpha
        GLCall(glEnable(GL_BLEND));                                 
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  //src alpha = 0; dest = 1 - 0 = 0
       


        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float)); // expand the buffer to 4 elements per vertex
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);  // adding to more attributes
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/texture0.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);  //the slot is 0


        va.Unbind();
        vb.Unbind();    //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        ib.Unbind();    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        shader.UnBind();  //GLCall(glUseProgram(0));
               
        Renderer renderer;

        // to create the animation that change the color 
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();  //GLCall(glClear(GL_COLOR_BUFFER_BIT));

            // use the shader and bind the buffer and ibo each time in case that the buffer change
            shader.Bind();   //GLCall(glUseProgram(shader));
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);   //GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

            renderer.Draw(va, ib, shader);

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            //part of the animation
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}



