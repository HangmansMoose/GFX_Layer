#pragma once

#include "Core/Base.h"
#include <string>


class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;
private:
	u32 m_RendererID;
};
