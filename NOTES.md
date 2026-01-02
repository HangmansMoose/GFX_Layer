# Abstracting a Graphics Layer For Runtime Access to Multiple Underlying Graphics APIs

# (At least in the beginning) This project is me learning graphics/rendering abstraction from the YouTube Game Engine Series by TheCherno
The best way to start this is to consider what is required to render a basic shaded triangle in OpenGL.
    1. A Window 
    2. Function pointers to local OpenGL implementation
    3. Vertex Buffer
    4. Element Buffer (Will be referred to as the Index Buffer from here on out)
    5. Vertex & Fragment shaders

Even prior to adding textures into the mix we can see a number of abstractions that would be useful to make here (this is almost certainly not exhaustive).
 - Buffer file to hold the classes for both the Vertex and Index Buffer implementations
 - Shader class
 - VertexArray class
 - Renderer Class
 - RenderCommand class
 - RenderAPI 
 
Each rendering API will then implement these classes, each within the bounds of the specific API
For example:
	- OpenGLBuffer
	- OpenGLContext
	- OpenGLRenderAPI
	- OpenGLVertexArray


### Buffers
Vertex and Index buffer class definitions
```cpp
class VertexBuffer
{
public:
	virtual ~VertexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual const BufferLayout& GetLayout() const = 0;
	virtual void SetLayout(const BufferLayout& layout) = 0;

	static VertexBuffer* Create(f32* vertices, u32 size);
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual u32 GetCount() const = 0;

	static IndexBuffer* Create(u32* indices, u32 size);
};

```

These being abstract we dont want them to have a constructer per se, so instead the `Create` function is
essentially the constructor. It being static, it is shared accross all derived classes. Note that all other
functions along with the destructor are `virtual`

### Vertex Buffer Layouts
Noting that the layout of the vertext buffers are completely up to the developer implementing them, so we need a way
to inform OpenGL, or any other API for that matter, what the layout of these buffers are so it can parse the data correctly.
One way this can be done in OpenGL is by first binding the buffer by its array position using `glEnableVertextAttribArray(0)`
and then defining the layout using `glVertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, pointer to offset)`
Where index is that starting index, size is how many values make up each attribute, type is the data type of the array values, normalized is whether the values
have been normalized or not, stride is the byte length between the beginning of one attribute to the beginning of the next, and offset is offset.


### Vertex Arrays
Vertex arrays are something that is individual to OpenGL, and they dont really contain anything useful in and of itself. The useful
data are in the vertex and index buffers. What the vertex array does is associates a given vertex buffer with its associated index buffer and the layout.


