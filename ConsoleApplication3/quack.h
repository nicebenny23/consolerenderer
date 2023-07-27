
#include <iostream>
#include <assert.h>

namespace quackd {
	template <typename T>
	struct ptrandelem
	{
		ptrandelem<T>* ptrnext;
		ptrandelem<T>* ptrback;
		T elem;
		ptrandelem();
		ptrandelem(T val, ptrandelem<T>* nextpt, ptrandelem<T>* backpt);
	};
	template<typename T>
	ptrandelem<T>::ptrandelem()
	{

		elem = T();
		ptrback = this;
		ptrnext = this;

	}
	template<typename T>
	ptrandelem<T>::ptrandelem(T val, ptrandelem<T>* nextpt, ptrandelem<T>* backpt)
	{

		elem = val;
		ptrnext = nextpt;
		ptrback = backpt;
	}
	template <typename T>
	class quack {


	public:
		ptrandelem<T>* last;

		ptrandelem<T>* first;
		int length;
		T& operator[](int index);
		void remove(int index);
		void removeptr(ptrandelem<T>* ptr, int index);
		quack();
		~quack();
		void insert(int index, T value);
		void append(T val);
		ptrandelem<T> prepop();
		ptrandelem<T> postpop();
		void prepend(T val);
		void printout();
	};


	template<typename T>
	T& quack<T>:: operator[](int index)
	{
		ptrandelem<T>* cursor;
		cursor = first;
		for (int i = 0; i < index; i++) {

			cursor = cursor->ptrnext;
		}
		return cursor->elem;
	}

	template<typename T>
	void quack<T>::remove(int index)
	{
		if (index % length == length - 1)
		{
			last = last->ptrback;
		}
		ptrandelem<T>* cursor;
		cursor = first;

		if (index % length == 0) {
			first = (first->ptrnext);
		}

		for (int i = 0; i < index; i++) {
			cursor = cursor->ptrnext;
		}

		ptrandelem<T>* prev = cursor->ptrback;
		prev->ptrnext = cursor->ptrnext;
		(cursor->ptrnext)->ptrback = prev;
		delete cursor;


		cursor = first;
		length--;
	}

	template<typename T>
	inline void quack<T>::removeptr(ptrandelem<T>* ptr,int index)
	{
		if (index % length == length - 1)
		{
			last = last->ptrback;
		}
		

		if (index % length == 0) {
			first = (first->ptrnext);
		}

	
		ptrandelem<T>* prev = ptr->ptrback;
		prev->ptrnext = ptr->ptrnext;
		(ptr->ptrnext)->ptrback = prev;
		delete ptr;

		length--;

	}


	template <typename T>
	quack<T>::quack()
	{

		length = 1;
		first = (new ptrandelem<T>());

		(*first).ptrback = first;
		(*first).ptrnext = first;


		last = first;
	}

	template<typename T>
	quack<T>::~quack()
	{
	}
	

	template<typename T>
	void quack<T>::insert(int index, T value)
	{

		ptrandelem<T>* cursor;
		cursor = first;
		for (int i = 0; i < index; i++) {

			cursor = cursor->ptrnext;
		}



		ptrandelem<T>* newelem = (new ptrandelem<T>(value, cursor, cursor->ptrback));
		((*cursor).ptrback)->ptrnext = newelem;
		cursor->ptrback = newelem;

		length++;

		if (index % (length) == length - 1) {

			last = newelem;
		}

		if ((index) % length == 0)
		{
			first = newelem;
		}

	}

	template<typename T>
	void quack<T>::append(T val)
	{
		ptrandelem<T>* cursor = last;
		ptrandelem<T>* newelem = new ptrandelem<T>(val, first, cursor);
		((*cursor).ptrnext) = (newelem);
		first->ptrback = newelem;
		last = newelem;
		++length;

	}

	template<typename T>
	ptrandelem<T> quack<T>::prepop()
	{
		ptrandelem<T>* cursor = first;
		first = (first->ptrnext);
		ptrandelem<T>* prev = cursor->ptrback;
		prev->ptrnext = first;
		(cursor->ptrnext)->ptrback = prev;
		ptrandelem <T> val = *cursor;
		delete cursor;
		return val;
	}

	template<typename T>
	ptrandelem<T> quack<T>::postpop()
	{
		ptrandelem<T>* cursor = last;
		first = (first->ptrnext);
		ptrandelem<T>* prev = cursor->ptrback;
		prev->ptrnext = first;
		(cursor->ptrnext)->ptrback = prev;
		ptrandelem <T> val = *cursor;
		delete cursor;
		return val;
	}

	template<typename T>
	void quack<T>::prepend(T val)
	{
		ptrandelem<T>* cursor;
		cursor = first;
		ptrandelem<T>* newelem = new ptrandelem<T>(val, cursor, last);
		last->ptrnext = newelem;
		first->ptrback = newelem;
		first = newelem;
		++length;

	}

	template<typename T>
	void quack<T>::printout()
	{
		ptrandelem<T>* cursor;
		cursor = first;
		for (int i = 0; i < length; i++)
		{


			std::cout << (*((*cursor).ptrback)).elem << "  ";
			std::cout << (*cursor).elem << "  ";
			std::cout << (*((*cursor).ptrnext)).elem << "\n";
			cursor = (*cursor).ptrnext;
		}

	}



}




