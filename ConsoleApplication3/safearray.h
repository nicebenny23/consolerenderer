#include <iomanip>
#include <iostream>
#include <stdexcept>
#ifndef safearray_HPP
#define safearray_HPP

namespace saferarray {


	template<class T>
	class safearray
	{
	public:
		safearray(int size);
		safearray(const T* arr,int len);
		T& operator[](int index);
		~safearray();
		T* getdata();
		safearray(const safearray& arr);
		int length;
		
	private:

		
		T* list;

	};




	


	template<class T>
	safearray<T>::~safearray() {
		if (list != nullptr) {
			delete[] list;
		}
	}


	template<class T>
	T* safearray<T>::getdata() {
		//unsafe do not use unless needed
		return list;
	}

	template<class T>
	safearray<T>::safearray(const safearray& arr) {
		length = arr.length;
		
		list = new T[length];
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
	safearray<T>::safearray(const T* arr,int len) {
		length = len;
		
		list = new T[length];
		if (list == nullptr)
		{
			delete[] list;

			return;
		}

		for (int i = 0; i < length; i++) {
			list[i] = arr[i];
		}

	}

	template<class T>
	T& safearray<T>::operator[](int index) {


		if (index >= length) {//max index is length

			index = length-1;
			
		}
		if (index < 0)
		{
			index = 0;//to avoid error
		}


		
		return list[index];


	}




	template<class T>
	safearray<T>::safearray(int size) {

		length = size;
		
		list = new T[size];
		if (list == nullptr)
		{
			delete[] list;

			return;
		}

	}



	




}
#endif
