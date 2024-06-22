#include "DynamicArray.h"


template <class T> DynamicArray<T>::DynamicArray (const T value) : length(1)
{
	array = new T[length];
	*array = value;
	ID = genID;
	++genID;
}

template<class T> DynamicArray<T>::DynamicArray(const unsigned lengthValue, const bool ConstructWithLength) : length(lengthValue)
{
	switch (length)
	{
	case 0:
		ArrayIsNullptr();
		ID = genID;
		++genID;
		return;
	case 1:
		array = new T[length]{ 0 };
		ID = genID;
		++genID;
		return;
	}
	array = new T[length];
	for (unsigned i = 0; i < length; ++i)
	{
		*(array + i) = 0;
	}
	ID = genID;
	++genID;
}

template<class T> DynamicArray<T>::DynamicArray(const T* values, const unsigned _length) : length(_length)
{
	switch (length)
	{
	case 0:
		while (*(values + length) != '\0')
		{
			++length;
		}
		break;
	case 1:
		array = new T[1];
		*array = *values;
		ID = genID;
		++genID;
		return;
	}
	array = new T[length];
	for (unsigned i = 0; i < length; ++i)
	{
		*(array + i) = *(values + i);
	}
	ID = genID;
	++genID;
}

template <class T> DynamicArray<T>::DynamicArray (const DynamicArray& other)
{
	this->length = other.length;
	this->array = new T[this->length];
	for (unsigned i = 0; i < this->length; ++i)
	{
		*(this->array + i) = *(other.array + i);
	}
	ID = genID;
	++genID;
}

template <class T> unsigned DynamicArray<T>::genID = 0;

template <class T> unsigned DynamicArray<T>::write_pos = 0;


template <class T> void DynamicArray<T>::RemoveAll ()
{
	delete[] array;
	length = 1;
	array = new T[length]{ 0 };
}

template <class T> void DynamicArray<T>::RemoveAll (const T& value)
{
	unsigned foundValuesCounter = 0;
	for (unsigned i = 0; i < length; ++i)
	{
		if (*(array + i) == value) ++foundValuesCounter;
	}
	switch (foundValuesCounter)
	{
	case 0:
		return;
	}
	length -= foundValuesCounter;
	switch (length)
	{
	case 0:
		ArrayIsNullptr();
		break;
	default:
		T* bufferArray = new T[length];
		for (unsigned i = 0, j = 0; j < length + foundValuesCounter; ++i, ++j)
		{
			if (*(array + j) == value) --i;
			else *(bufferArray + i) = *(array + j);
		}
		delete[] array;
		array = bufferArray;
		bufferArray = nullptr;
	}
}

template <class T> void DynamicArray<T>::RemoveAll (const DynamicArray& other)
{
	for (unsigned i = 0; i < other.length; ++i)
	{
		RemoveAll(*(other.array + i));
	}
}

template <class T> DynamicArray<T> DynamicArray<T>::operator+ (const T& value)
{
	DynamicArray<T> newArray = DynamicArray<T>(this->length + 1, true);
	for (unsigned i = 0; i < this->length; ++i)
	{
		*(newArray + i) = *(this->array + i);
	}
	*(newArray + this->length) = value;
	return newArray;
}

template <class T> DynamicArray<T> DynamicArray<T>::operator+ (const DynamicArray& other)
{
	DynamicArray<T> newArray = DynamicArray<T>(this->length + other.length, true);
	unsigned i = 0;
	for (; i < this->length; ++i)
	{
		*(newArray.array + i) = *(this->array + i);
	}
	for (unsigned j = 0; j < other.length; ++i, ++j)
	{
		*(newArray.array + i) = *(other.array + j);
	}
	return newArray;
}

template <class T> void DynamicArray<T>::operator+= (const T& value)
{
	T* bufferArray = new T[++length];
	for (unsigned i = 0; i < length - 1; ++i)
	{
		*(bufferArray + i) = *(array + i);
	}
	*(bufferArray + (length - 1)) = value;
	delete[] array;
	array = bufferArray;
	bufferArray = nullptr;
}

template <class T> void DynamicArray<T>::operator+= (const DynamicArray& other)
{
	T* bufferArray = new T[this->length + other.length];
	for (unsigned i = 0; i < this->length; ++i)
	{
		*(bufferArray + i) = *(this->array + i);
	}
	delete[] this->array;
	this->array = bufferArray;
	bufferArray = nullptr;
	for (unsigned i = this->length, j = 0; j < other.length; ++i, ++j)
	{
		*(this->array + i) = *(other.array + j);
	}
	this->length += other.length;
}

template <class T> bool DynamicArray<T>::operator-= (const T& value)
{
	if (!Contains(value)) return false;
	bool isFound = false;
	T* bufferArray = new T[--length];
	switch (length)
	{
	case 0:
		delete[] array;
		ArrayIsNullptr();
		return true;
	}
	for (int i = length, j = length - 1; i > -1 && j > -1; --i)
	{
		if (*(array + i) == value && !isFound)
		{
			isFound = true;
		}
		else
		{
			*(bufferArray + j) = *(array + i);
			--j;
		}
	}
	delete[] array;
	array = bufferArray;
	bufferArray = nullptr;
	return true;
}
	
template <class T> void DynamicArray<T>::operator-= (const DynamicArray& other)
{
	if (this->array == other.array)
	{
		delete[] array;
		ArrayIsNullptr();
		return;
	}
	for (unsigned i = 0; i < other.length; ++i)
	{
		*this -= *(other.array + i);
	}
		
}

template <class T> DynamicArray<T>& DynamicArray<T>::operator= (const DynamicArray& other)
{
	delete[] this->array;
	this->length = other.length;
	this->array = new T[this->length];
	for (unsigned i = 0; i < this->length; ++i)
	{
		*(this->array + i) = *(other.array + i);
	}
	return *this;
}

template <class T> bool DynamicArray<T>::operator== (const T& value)
{
	switch (length)
	{
	case 1:
		if (*array == value)
		{
			return true;
		}
	}
	return false;
}

template <class T> bool DynamicArray<T>::operator== (const DynamicArray& other)
{
	if (this->length == other.length)
	{
		for (unsigned i = 0; i < length; ++i)
			if (*(this->array + i) != *(other.array + i)) return false;
		return true;
	}
	return false;
}
	
template <class T> bool DynamicArray<T>::operator!= (const T& value)
{
	return !(*this == value);
}

template <class T> bool DynamicArray<T>::Contains(const T& value)
{
	for (unsigned i = 0; i < length; ++i)
	{
		if (*(array + i) == value)
		{
			return true;
		}
	}
	return false;
}

template <class T> bool DynamicArray<T>::Contains(const DynamicArray& other)
{
	for (unsigned i = 0; i < other.length; ++i)
	{
		if (!Contains(*(other + i))) return false;
	}
	return true;
}

template <class T> T& DynamicArray<T>::operator[] (const unsigned number)
{
	return *(array + number);
}

template <class T> void DynamicArray<T>::DisplayInfo_Int ()
{
	writeWord("Array "); writeUnsigned<unsigned>(ID,'\n');
	for (unsigned i = 0; i < length; ++i)
	{
		writeWord("id:\t"); writeUnsigned<unsigned>(i, ' '); writeWord(": "); writeInt<T>(*(array + i), '\n');
	}
}

template <class T> void DynamicArray<T>::DisplayInfo_Unsigned()
{
	writeWord("Array "); writeUnsigned<unsigned>(ID, '\n');
	for (unsigned i = 0; i < length; ++i)
	{
		writeWord("id:\t"); writeUnsigned<unsigned>(i, ' '); writeWord(": "); writeUnsigned<T>(*(array + i), '\n');
	}
}

template <class T> void DynamicArray<T>::DisplayInfo_Float()
{
	writeWord("Array "); writeUnsigned<unsigned>(ID, '\n');
	for (unsigned i = 0; i < length; ++i)
	{
		writeWord("id:\t"); writeUnsigned<unsigned>(i, ' '); writeWord(": "); writeFloat<T>(*(array + i), '\n');
	}
}

template <class T> void DynamicArray<T>::DisplayInfo_Char()
{
	writeWord("Array "); writeUnsigned<unsigned>(ID, '\n');
	for (unsigned i = 0; i < length; ++i)
	{
		writeWord("id:\t"); writeUnsigned<unsigned>(i, ' '); writeWord(": '"); writeChar(*(array + i)); writeWord("'\n");
	}
}

template <class T> void DynamicArray<T>::DisplayInfo_String()
{
	writeWord("Array "); writeUnsigned<unsigned>(ID, ':'); writeWord(" '");
	for (unsigned i = 0; i < length; ++i)
	{
		writeChar(*(array + i));
	}
	writeWord("' = "); writeUnsigned<unsigned>(length, '\n');
}


template <class T> DynamicArray<T>::~DynamicArray ()
{
	if (array != nullptr)
	{
		delete[] array;
		array = nullptr;
	}
}

	
template <class T> void DynamicArray<T>::ArrayIsNullptr ()
{
	length = 1;
	array = new T[length]{ 0 };
	writeWord("\nWarning: nullptr were found! Array initialized with 0.\n");
}