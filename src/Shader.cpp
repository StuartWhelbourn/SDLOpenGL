#include  "Shader.h"
#include <fstream>
#include <iostream>
#include <memory>


Shader::Shader(const std::string &_vert, const std::string &_frag)
{
    std::ifstream shaderSource(_vert.c_str());
    if(!shaderSource.is_open())
    {
      std::cerr<<"File Not Found "<<_vert<<"\n";
      exit(EXIT_FAILURE);
    }
    std::string source = std::string(
                        (std::istreambuf_iterator<char>(shaderSource)),
                         std::istreambuf_iterator<char>()
                        );
    shaderSource.close();
    source+='\0';
    std::cout<<source<<"\n";

    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    const char *csource=source.c_str();
    glShaderSource(vertexID,1,&csource,NULL);
    glCompileShader(vertexID);
    printInfoLog(vertexID,DebugMode::COMPILE);




    shaderSource.open(_frag.c_str());
    if (!shaderSource.is_open())
    {
      std::cerr<<"File Not Found "<<_frag<<"\n";
      exit(EXIT_FAILURE);
    }
    source = std::string(
                        (std::istreambuf_iterator<char>(shaderSource)),
                         std::istreambuf_iterator<char>()
                        );
    shaderSource.close();
    source+='\0';
    std::cout<<source<<"\n";

    GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
    csource=source.c_str();
    glShaderSource(fragID,1,&csource,NULL);
    glCompileShader(fragID);
    printInfoLog(fragID,DebugMode::COMPILE);

    m_id=glCreateProgram();
    glAttachShader(m_id,vertexID);
    glAttachShader(m_id,fragID);
    glLinkProgram(m_id);
    printInfoLog(m_id,DebugMode::LINK);
    glUseProgram(m_id);

}

void Shader::printInfoLog(GLuint _id, DebugMode _mode)
{
  GLint infoLogLength =0;
  GLint charsWritten =0;

  glGetShaderiv(_id,GL_INFO_LOG_LENGTH,&infoLogLength);
  if(infoLogLength >0)
  {
    std::unique_ptr<char []>infoLog(new char [infoLogLength]);
    glGetShaderInfoLog(_id,infoLogLength,&charsWritten,infoLog.get());
    std::cerr<<"Log \n"<<infoLog.get()<<"\n";

    GLenum mode;
    if(_mode == DebugMode::COMPILE)
    {
      mode=GL_COMPILE_STATUS;
    }
    else if(_mode == DebugMode::LINK)
    {
      mode=GL_LINK_STATUS;
    }
    glGetShaderiv(_id,mode,&infoLogLength);
    if(infoLogLength == GL_FALSE)
    {
      std::cerr<<"shader compilatio nor linking error\n";
      exit(EXIT_FAILURE);
    }
  }
}



Shader::~Shader()
{

}


