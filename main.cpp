#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

static ShaderProgramSource parse_shader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;

	enum class ShaderType
	{
		none = -1,
		vertex = 0,
		fragment = 1
	};
			
	std::stringstream ss[2];
	ShaderType type = ShaderType::none;
	
	while(getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::vertex;
			}
			else if(line.find("fragment") != std::string::npos)
			{
				type = ShaderType::fragment;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return {ss[0].str(), ss[1].str()};
}

static unsigned int compile_shader(unsigned int type, const std::string& source)
{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);

			std::cout << "[!] Failed To Compile " <<
					(type==GL_VERTEX_SHADER ? "Vertex" : "Fragment") <<
					" Shader" <<
					std::endl;

			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
		return id;
}

static unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader){
		unsigned int program = glCreateProgram();
		unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
}

int main(){
    
    // Creating GLFW Window
    GLFWwindow* window;

    // Initing lib
    if(!glfwInit())
        return -1;
    
    // Creating Window
    window = glfwCreateWindow(640, 480, "Arsenic", NULL, NULL);

    // Checking For Error
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    // Creating OpenGl Context
    glfwMakeContextCurrent(window);

    // Checking For Error
    if(glewInit() != GLEW_OK){
        std::cout << "Error!" << std::endl;
    }

    // Printing Out OpenGl Version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Vertices
    float vertices[6] = {
        -0.5, -0.5,
        0.0f, 0.5f,
        0.5f,-0.5f
    };


    // generating vertex_buffer
    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,6*sizeof(float), vertices, GL_STATIC_DRAW);
    
    // enabling vertex attrib array
    glEnableVertexAttribArray(0);

    // [index of vertex attribute], [No Of Attributes In A Vertex], [Type Of Vertex], [Offset For Accessing Next Vertex], [From the 0 byte how many bytes there is till vertex attribute in this vertex buffer]
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

	//ShaderProgramSource source = 
	ShaderProgramSource source = parse_shader("dist/shaders/shader.shader");
	
	// getting shader id
	unsigned int shader = create_shader(source.vertexSource, source.fragmentSource);

	// using shader
	glUseProgram(shader);

    // Main Game Loop
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

	// glDeleteProgram(shader);
    // Exiting Code
    glfwTerminate();
    return 0;
}
