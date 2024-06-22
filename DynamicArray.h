#pragma once
#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__


template <class T> class DynamicArray
{
public:
    DynamicArray(const T value = 0);

    DynamicArray(const unsigned lengthValue, const bool ConstructWithLength);

    DynamicArray(const T* values, const unsigned _length = 0);

    DynamicArray(const DynamicArray& other);


    void RemoveAll();

    void RemoveAll(const T& value);

    void RemoveAll(const DynamicArray& other);

    DynamicArray operator+ (const T& value);

    DynamicArray operator+ (const DynamicArray& other);

    void operator+= (const T& value);

    void operator+= (const DynamicArray& other);

    bool operator-= (const T& value);

    void operator-= (const DynamicArray& other);

    DynamicArray& operator= (const DynamicArray& other);

    bool operator== (const T& value);

    bool operator== (const DynamicArray& other);

    bool operator!= (const T& value);

    bool Contains(const T& value);

    bool Contains(const DynamicArray& other);

    T& operator[] (const unsigned number);

    void DisplayInfo_Int();

    void DisplayInfo_Unsigned();

    void DisplayInfo_Float();

    void DisplayInfo_Char();

    void DisplayInfo_String();


    ~DynamicArray();
private:
    T* array = nullptr;
    unsigned length = 0;

    static unsigned genID;
    unsigned ID;

    void ArrayIsNullptr();

	// - - OUTPUT BLOCK - - //
	static const unsigned buf_size = 4096;
	static unsigned write_pos;
	static char write_buf[buf_size];

	inline void writeChar(unsigned x) {
		switch (write_pos)
		{
		case buf_size:
			fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
		}
		write_buf[write_pos] = x;
		++write_pos;
	}

	inline void writeWord(const char* s) {
		while (*s)
		{
			writeChar(*s);
			++s;
		}
	}

	template <class T> inline void writeInt(T x, char end)
	{

		if (x < 0)
		{
			writeChar('-'), x = (signed)-x;
		}

		char s[24];
		unsigned n = 0;
		while (x || !n)
		{
			s[n] = '0' + x % 10, x /= 10;
			++n;
		}
		while (n)
		{
			--n;
			writeChar(s[n]);
		}
		writeChar(end);
	}

	template <class T> inline void writeUnsigned(T x, char end)
	{
		char s[24];
		unsigned n = 0;
		while (x || !n)
		{
			s[n] = '0' + x % 10, x /= 10;
			++n;
		}
		while (n)
		{
			--n;
			writeChar(s[n]);
		}
		writeChar(end);
	}

	template <class T> inline void writeFloat(T x, char end)
	{
		char b[buf_size];
		sprintf_s(b, "%f", x);
		writeWord(b);
		writeChar(end);
	}

	struct Flusher {
		~Flusher() {
			if (write_pos)
				fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
		}
	} flusher;
	// - - OUTPUT BLOCK - - //
};

#endif // !__DYNAMICARRAY_H__