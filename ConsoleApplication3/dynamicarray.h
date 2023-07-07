#include <iomanip>
#include <iostream>

#ifndef dynamicarray_HPP
#define dynamicarray_HPP

namespace dynamicarray {


	template<class T>
	class array
	{
	public:
		array();
		T& operator[](int index);
		array(int size);
		~array();
		void insertind(int index, T value);
		void deleteind(int index);
		void append(T value);
		array(const array& arr);
		 int length;
	private:
		bool resize(int size = 0);
	 int totalsize;
		 T* list;

	};




	
	
	template<class T>
	array<T>::~array() {
		if (list != nullptr) {
			delete[] list;
		}
	}



	template<class T>
	array<T>::array(const array& arr) {
		length = arr.length;
		totalsize = arr.totalsize;
		list = new T[totalsize];
		if (list == nullptr)
		{
			delete[] list;

			return;
		}

		for (int i = 0; i < length; i++) {
			list[i] = arr.list[i];
		}

	}
	template<class T>
	void array<T>::append(T value) {
		if (totalsize <= length)//sees if wee need more memory due to not enogh space
		{
			resize(2 * length + 2);
		}
		list[length++] = value;//postfix just t save one line
		
	}
	template<class T>
	void array<T>::deleteind(int index) {


		if (index < length && index >= 0)//sees if in bounds
		{
			length--;//decrements size
			for (size_t i = index; i < length; i++)
			{
				list[i] = list[i + 1];//this lets index be removed
			}

			list[length] = T();//sets to defailt

		}


	}


	template<class T>
	void array<T>::insertind(int index, T value) {
		if (totalsize <= length)//sees if wee need more memory due to not enogh space
		{
			resize(2 * length + 2);
		}
		if (totalsize <= index + 1)//same thing for index size
		{
			resize(2 * index + 2);
		}
		if (index >= 0)//sees if it over 0
		{

			for (int i = length; i > index; i--)
			{
				list[i] = list[i - 1];
			}

			list[index] = value;
		}

		if (index >= length)//checks if index is higher than the newsize
		{
			length = index;//sets it to index and while this is wrong it is incremented later
		}
		length++;//increment
	}
	template<class T>
	T& array<T>::operator[](int index) {
		if (index < 0)
		{
			return list[0];//to avoid error
		}


		if (index >= totalsize) {
			if (!resize(2 * index + 2))
			{
				return list[0];//again to avoid error in case of memory fail
			}

		}
		if (index >= length) {

			length = index + 1;//used size

		}
		return list[index];


	}


	template<class T>
	bool array<T>::resize(int size) {
		//returns if success
		if (size == 0)
		{
			size = 2 * length + 2;//default case
		}

		if (size > totalsize && size > length)//so it cant be shrunk
		{

			T* newlist = new T[size];


			if (newlist == nullptr)
			{



				return false;
			}

			for (int i = 0; i < length; i++)
			{

				newlist[i] = list[i];
			}
			//also the error here is a bug 


			delete[] list;

			list = newlist;

			totalsize = size;
			return true;
		}
		return false;
	}

	template<class T>
	array<T>::array(int size) {

		length = 0;
		totalsize = size;
		list = new T[size];
		if (list == nullptr)
		{
			delete[] list;

			return;
		}

	}


		template<class T>
		array<T>::array() {
			length = 0;
			totalsize = 1;
			list = new T[1];
			if (list == nullptr)
			{
				delete[] list;

				return;
			}





		}



	

}
#endif