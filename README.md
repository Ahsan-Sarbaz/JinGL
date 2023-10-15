# JinGL

An Object Oriented Wrapper and Utilities for OpenGL 4.5+

The essentials are available more to come in future (maybe you might help with that)

## Dependencies
- Any OpenGL Loader (e.g GLEW, GLAD, GL3W)
- stb_image.h (and a cpp file with STB_IMAGE_IMPLEMENTATION defined)

## Examples

### Buffers
``` cpp
#include "Buffer.h"
...

Vertex veritices[] = { ... };

Buffer vertexBuffer(sizeof(vertices), vertices, false);

unsigned int indices[] = { ... };

Buffer indexBuffer(sizeof(indices), indices, false);

Buffer combindBuffer(sizeof(vertices) + sizeof(indices), nullptr, true);
combindBuffer.SubData(sizeof(vertices), 0, vertices);
combindBuffer.SubData(sizeof(indices), sizeof(vertices), indices);

Buffer dynamicBuffer(sizeof(Vertex) * max_batch_quad_count, nullptr, true);
combindBuffer.SubData(sizeof(batch_vertices), 0, batch_vertices);
...
```

### Vertex Input (Vertex Array Object)
``` cpp
#include "VertexInput.h"
...

VertexInput vertexInput;
vertexInput.AddVec3();
vertexInput.AddVec4();
vertexInput.AddVec2();

// create one vertex input for each shader attribute combination and 
// just the bind vertex and/or index buffer draw
vertexInput.SetVertexBuffer(vertexBuffer, 0, sizeof(Vertex), 0);
vertexInput.SetIndexBuffer(indexBuffer);

vertexInput.Bind();

glDraw...

// create a vertex input from the attributes of the shader
VertexInput anotherVertexInput(shader_program);

...
```

### Shaders
``` cpp
#include "Shader.h"
...

// creates and compiles the shader from the given source
auto vs = new Shader(ShaderType::Vertex, vertex_source_string);
auto fs = new Shader(ShaderType::Fragment, fragment_source_string);

// create with vertex and fragment shaders
ShaderProgram program(vs, fs);

ShaderProgram another;
// attach shaders one by one
another.AttachShader(vs);
another.AttachShader(fs);
// link all the attached shader into the program
another.Link();

program.bind();


// the uniforms are cached to avoid getting there location every time
float mouse_position[2] = {..};
program.UniformVec2("u_mouse_position", mouse_position);

float projection_matrix[4][4] = {..};
program.UniformMat4("u_projection_matrix", projection_matrix);

...
```

### Textures
``` cpp

#include "TextureLoader.h"
// Texture2D.h is included by TextureLoader
#include "Texture2D.h"
...

// the texture is promised to be loaded not actually loaded
bool flip = false;
Texture2D* texture = TextureLoader::Load("sprite_sheet.png", flip);

// load all promised textures to this point
// uses threads to load many textures data at once
TextureLoader::Get()->LoadPromisedTextures();

// bind at texture unit zero
// bind must be called after the promised texture are loaded
texture->Bind(0);

...
```

### Framebuffers

```cpp
#include "Framebuffer.h"
...

int width = 1920;
int height = 1080;
Framebuffer framebuffer(width, height);
framebuffer.AddAttachment(Format::RGBA8);
framebuffer.AddDepthStencil();
// call once to actually attach the attachments
framebuffer.Resize(width, height);

...

if(window_resized)
{
    // resize all the attachments
    framebuffer.Resize(new_width, new_height);
}

// clear all the attachments with sane values
framebuffer.ClearAttachments();
// bind the frambebuffer and also set the viewport to the size
// of the framebuffer
framebuffer.Bind();

...
```
### Debug Stuff

```cpp
#include "Debug.h"
...

// enables the debug callback and printf's the messages to stdout
// only messages marked as ERROR from SOURCE_API are allowed all
// other messages are ignored by default
EnableDebugMessages();

...
```
