#pragma once
#include "Rendering\IndexBuffer.h"

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	~OpenGLIndexBuffer();
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Returns OpenGL ID
	inline uint32_t getCount() const { return m_count; } //!< Returns count
	void bind();
	void unbind();
private:
	uint32_t m_OpenGL_ID; //!< Render ID
	uint32_t m_count; //!< Effective draw count
};