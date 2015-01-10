#include "hge-serializable.hpp"
void hge::core::Serializable::swapObject(char *const &data, const unsigned int &size)
{
	char tmp;
	for (int j = size / 2, i = j - 1; i >= 0; i--, j++)
	{
		tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
}