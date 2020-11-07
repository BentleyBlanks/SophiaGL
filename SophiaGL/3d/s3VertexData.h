#pragma once
#include <core/s3Settings.h>
#include <shader_parser_gl.h>

class s3InputLayout
{
public:
	s3InputLayout()
	{
		//channels.resize(semantic_channel::eC_COUNT);
		//dataTypes.resize(semantic_channel::eC_COUNT);
		//dimensions.resize(semantic_channel::eC_COUNT);

		for (int i = 0; i < semantic_channel::eC_COUNT; i++)
		{
			channels[i]   = false;
			dataTypes[i]  = eDT_INVALID;
			dimensions[i] = 0;
		}
	}
	~s3InputLayout() {}

	bool isEqual(const s3InputLayout& other) const
	{
		for (int i = 0; i < semantic_channel::eC_COUNT; i++)
		{
			if (channels[i]   != other.channels[i] ||
				dataTypes[i]  != other.dataTypes[i] ||
				dimensions[i] != other.dimensions[i])
			{
				return false;
			}
		}
		return true;
	}

	// could be replaced by channelMask
	//std::vector<bool> channels;
	//std::vector<semantic_data_type> dataTypes;
	//std::vector<int> dimensions;

	bool channels[semantic_channel::eC_COUNT];
	semantic_data_type dataTypes[semantic_channel::eC_COUNT];
	int dimensions[semantic_channel::eC_COUNT];

	// default value
	static s3InputLayout invalid;
};

class s3InputLayoutManager
{
public:
    static s3InputLayoutManager& getInstance() { return instance; }

	// return ID for handle
	unsigned int add(const s3InputLayout& newInputLayout);

	bool remove(const s3InputLayout& newInputLayout);
	bool remove(unsigned int handle);

	unsigned int find(const s3InputLayout& inputlayout) const;
	const s3InputLayout& get(unsigned int handle) const;

	bool isValid(unsigned int handle) const;

private:
	// singleton
	s3InputLayoutManager(){}
	~s3InputLayoutManager(){}

	static s3InputLayoutManager instance;

	std::map<unsigned int, s3InputLayout> inputLayoutMap;

	// simple uuid
	unsigned int uuidGenerator = 1;
};

class s3VertexStream
{
public:

};