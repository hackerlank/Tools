#include "DynBufResizePolicy.h"
#include "BufferDefaultValue.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

// 获取一个最近的大小
uint32 DynBufResizePolicy::getCloseSize(size_t needSize, size_t capacity)
{
	uint32 ret = 0;

	if (needSize <= MAX_CAPACITY)
	{
		if (capacity >= needSize)
		{
			ret = capacity;
		}
		else
		{
			ret = 2 * capacity;
			while (ret < needSize && ret < MAX_CAPACITY)
			{
				ret *= 2;
			}

			if (ret > MAX_CAPACITY)
			{
				ret = MAX_CAPACITY;
			}
		}
	}
	else	// 需要的数据比允许最大允许分配的大小还大
	{
		// 日志，需要的存储空间太大
	}

	return ret;
}

END_NAMESPACE_FILEARCHIVETOOL