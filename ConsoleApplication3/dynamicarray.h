#include <iomanip>
#include <iostream>
#include <stdexcept>

#ifndef dynamicarray_HPP
#define dynamicarray_HPP

namespace dynamicarray {


	template<class T>
	class array
	{
	public:

		array();
		array(T* arr,int size);
		T& operator[](int index);
		T getelem(int index);

		array(int size);
		void destroy();
		T& at(int ind);
		void append(array arr);
		bool cutind(int startindex, int endindex);
		void slice(int startindex, int endindex);
		void insertind(int index, T value);
		void merge(int index, const array& arr);
		bool deleteind(int index);
		T& gettop();

		void append(T value);
		T* getdata();
		array(const array& arr);
		int length;
		T* list;
		bool resize(int size = 0);
	
		int capacity;
		

	};





	template<class T>
	T array<T>::getelem(int index) {
		if (index > length) {

			index = length - 1;
		}
		if (index < 0)
		{
			index = 0;
		}
		return list[index];
	}
	template<class T>
	void array<T>::merge(int index, const array& arr) {
		if (index < 0)
		{
			index = 0;
		}
		if (index+arr.length>=length)
		{
			return;
		}
		int otherlength = arr.length;
		if (length + otherlength >= capacity)
		{
			resize(2 * (length + otherlength) + 2);
		}

		for (int i = index; i < length; i++)
		{
			list[i + otherlength] = list[i];
		}
		for (int i = 0; i < otherlength; i++)
		{
			list[i + index] = arr.list[i];
		}
		length += otherlength;
	}
	template<class T>
	T& array<T>::gettop() {
		if (length>0)
		{
			return list[length - 1];

		}

	}
	
	template<class T>
	void array<T>::destroy() {
		if (list != nullptr) {
			delete[] list;
		}
	}


	template<class T>
	T* array<T>::getdata() {
		//unsafe do not use unless needed
		return list;
	}

	template<class T>
	void array<T>::slice(int startindex, int endindex) {


		
		this->cutind(endindex+1, length-1);
		this->cutind(0,startindex-1);

		int v = 1;
		return;
	}

	template<class T>
	array<T>::array(const array& arr) {
		length = arr.length;
		capacity = arr.capacity;
		list = new T[capacity];
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
		if (length>=capacity)//sees if wee need more memory due to not enogh space
		{
			resize(2 * length+2 );
		}
		list[length] = value;
		length++;

	}
	template<class T>
	bool array<T>::deleteind(int index) {


		if (index < length && index >= 0)//sees if in bounds
		{
			
			
			
			length--;//decrements size
			for (int i = index; i < length; i++)
			{
				
				list[i] = list[i + 1];//this lets index be removed
			}

			list[length] = T();//sets to defailt
			return true;
		}
		return false;
		
	}
	template<class T>
	bool array<T>::cutind(int startindex,int endindex) {
		 
		if (endindex < startindex)
		{
			int car = endindex;
			endindex = startindex;
			startindex = car;
		}
		if (startindex<0)
		{
			return false;
		}
		if (endindex>=length)
		{
			return false;
		}//bounds checking
		
			int dif = endindex - startindex;   
			
			
			for (int i =endindex+1; i <length; i++)
			{
				


				list[i- dif-1] = list[i];
				int g = 1;

			}
			
			
			length-=dif+1;
			return true;
	}

		
	

	


	template<class T>
	void array<T>::insertind(int index, T value) {
		if (index < 0)//sees if it over 0
		{
			return;
		}
		if (index > length) {

			index = length;
		}
		if (capacity <= length)//sees if wee need more memory due to not enogh space
		{
			resize(2 * length + 2);
		}
		
		

			for (int i = length; i > index; i--)
			{
				list[i] = list[i - 1];
			}

			list[index] = value;
		

		if (index >= length)//checks if index is higher than the newsize
		{
			length = index;//sets it to index and while this is wrong it is incremented later
		}
		length++;//increment
	}

	template<class T>
	T& array<T>::operator[](int index) {

		if (index>= capacity)
		{
			if (!resize(2 * index + 2))//array resize failed
			{
				return *list;//to avoid error in case of memory fail and derenfrence it because its cool
			}
		}
		if (index >=length) {//max index is length
			
			length =index+1;
		  
		}
		if (index < 0)
		{
			index = 0;//to avoid error
		}


		if (length>capacity) {
			if (!resize(2 * length + 2))//array resize failed
			{
				return *list;//again to avoid error in case of memory fail and derenfrence it because its cool
			}

		}
		
		return list[index];


   	}

	template<class T>
	T& array<T>::at(int index) {
		//same as [] but only in bounds
		if (index >= length) {
			index = length - 1;
		}
		if (index < 0)
		{
			index = 0;
		}


		T val = list[index];
		return list[index];


	}

	template<class T>
	void array<T>::append( array arr) {
	
		
		int otherlength = arr.length;
		if (length + otherlength >= capacity)
		{
			resize(2 * (length + otherlength) + 2);
		}

	
		for (int i = 0; i < otherlength; i++)
		{
			list[i +length] = arr.list[i];
		}
		length += otherlength;
	}
	
	template<class T>
	bool array<T>::resize(int size) {
		//returns if success
	
		if (list == nullptr || length == 0)
		{
			length = 0;
			*this = array<T>(2);
			return true;
		}
		if (size == 0)
		{
			size = 2 * length + 2;//default case
		}
		
		if (size > capacity)//so it cant be shrunk
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

				for (int i = length; i < capacity; i++)
				{

					newlist[i] = T();
				}
				//also the error here is a bug 
				delete[] list;
			
				

		

			list = newlist;

			capacity = size;
			return true;
		}
		return false;
	}

	template<class T>
	array<T>::array(int size) {

		length = 0;
		capacity = size;
		list = new T[size];

		for (int i = 0; i < size; i++)
		{
			list[i] = T();
		}
		if (list == nullptr)
		{
			delete[] list;

			return;
		}

	}


	

	template<class T>
		array<T>::array() {
			length = 0;
			capacity = 0;
			list = nullptr;





		}

		template<class T>
		inline array<T>::array(T* arr,int size)
		{
			length = size;
			capacity = size;
			list = new T[size];

			for (int i = 0; i < size; i++)
			{
				list[i] =arr[i];
			}
			if (list == nullptr)
			{
				delete[] list;

				return;
			}


		}



	

}
#endif