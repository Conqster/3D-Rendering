#pragma once

class UniformBuffer
{
	unsigned int m_ID = 0;

public:
	UniformBuffer() = default;
	UniformBuffer(signed long long int size);
	~UniformBuffer();

	void Generate(signed long long int size);
	void Bind() const;
	void UnBind() const;
	void SetBufferSubData(const void* data, unsigned long long int size, unsigned int offset) const;
	void BindBufferRndIdx(const unsigned int block_idx, unsigned long long int size, unsigned int offset) const;
	void SetSubDataByID(const void* data, signed long long int size, unsigned int offset) const;

	void Delete();
};