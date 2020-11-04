#include <3d/s3VertexData.h>

s3InputLayout s3InputLayout::invalid;
s3InputLayoutManager s3InputLayoutManager::instance;

unsigned int s3InputLayoutManager::add(const s3InputLayout& newInputLayout)
{
    auto handle = find(newInputLayout);

    // newInputLayout already exsited
    if (handle != 0) return handle;

    inputLayoutMap[uuidGenerator] = newInputLayout;

    // simple uuid generation
    auto old = uuidGenerator++;
    return old;
}

bool s3InputLayoutManager::remove(const s3InputLayout& newInputLayout)
{
    auto handle = find(newInputLayout);
    if (handle == 0) return false;

    auto iter = inputLayoutMap.begin();
    for (iter; iter != inputLayoutMap.end();)
    {
        if (iter->second.isEqual(newInputLayout))
        {
            inputLayoutMap.erase(iter++);
            return true;
        }
        else
        {
            iter++;
        }
    }
    // can't be here
    return true;
}

bool s3InputLayoutManager::remove(unsigned int handle)
{
    auto input = get(handle);
    return remove(input);
}

unsigned int s3InputLayoutManager::find(const s3InputLayout& inputlayout) const
{
    for (auto iter = inputLayoutMap.begin(); iter != inputLayoutMap.end(); iter++)
    {
        if (iter->second.isEqual(inputlayout))
            return iter->first;
    }
    return 0;
}

const s3InputLayout& s3InputLayoutManager::get(unsigned int handle) const
{
    auto iter = inputLayoutMap.find(handle);
    if (iter != inputLayoutMap.end())
    {
        return iter->second;
    }
    else
    {
        // return default value's reference
        return s3InputLayout::invalid;
    }
}

bool s3InputLayoutManager::exsited(unsigned int handle) const
{
    auto iter = inputLayoutMap.find(handle);
    if (iter != inputLayoutMap.end())
        return true;
    else
        return false;
}
