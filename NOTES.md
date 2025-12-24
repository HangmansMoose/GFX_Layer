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