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
		T& operator[](int index);
		T getelem(int index);
		
		array(int size);
		~array();
		bool cutind(int startindex, int endindex);
		void insertind(int index, T value);
		void merge(int index, const array& arr);
		bool deleteind(int index);
		T& gettop();
	
		void append(T value);
		T* getdata();
		array(const array& arr);
		 int length;
		 bool resize(int size = 0);
	private:
	
	 int capacity;
		 T* list;

	};



	
	template<class T>
	T array<T>::getelem(int index) {
		if (index > length) {

			index = length - 1;
		}
		if (index < 0)
		{
			return list[0];//to avoid error
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
	array<T>::~array() {
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
			
				return false;
			
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
		 
		if (startindex<0)
		{
			startindex = 0;
		}
		if (endindex>=length)
		{
			endindex = length - 1;
		}//bounds checking
		if (endindex>=startindex)//sees if in bounds
		{
			int dif = endindex - startindex;   
			for (int i =endindex; i <=length; i++)
			{
				
				
				list[i-dif] = list[i];//this lets index be removed
				list[i] = T();//sets to defualt
			}
			
			
			length-=dif+1;
		}


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


		if (index >= length) {//max index is length
			
			index = length;
			length++;
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
	bool array<T>::resize(int size) {
		//returns if success
		if (size == 0)
		{
			size = 2 * length + 2;//default case
		}

		if (size > capacity && size > length)//so it cant be shrunk
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
		if (list == nullptr)
		{
			delete[] list;

			return;
		}

	}


	

	template<class T>
		array<T>::array() {
			length = 0;
			capacity = 1;
			list = new T[1];
			if (list == nullptr)
			{
				delete[] list;

				return;
			}





		}



	

}
#endif