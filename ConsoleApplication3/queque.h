#pragma once
namespace quequename {
	template <typename T>
	struct ptrandelemqueque
	{

		ptrandelemqueque<T>* ptrnext;
		T elem;

		ptrandelemqueque(T val);
		ptrandelemqueque(T val, ptrandelemqueque<T>* nextelem);
	};


	template<typename T>
	class queque {

		ptrandelemqueque<T>* top;
		ptrandelemqueque<T>* bottom;
	public:
		bool swaptop(T val);
		T pop();
		T peek();
		bool remove();
		int length;
		void append(T val);
		queque();
		bool empty();



	};


	template<typename T>
	queque<T>::queque() {
		length = 0;
		top = nullptr;
		bottom = nullptr;


	}

	template<typename T>
	ptrandelemqueque<T>::ptrandelemqueque(T val)
	{

		elem = T(val);
		ptrnext = this;
	}

	template<typename T>
	ptrandelemqueque<T>::ptrandelemqueque(T val, ptrandelemqueque<T>* nextelem)
	{

		ptrnext = nextelem;
		elem = val;
	}

	template<typename T>
	bool queque<T>::swaptop(T val)
	{
		if (!empty())
		{
			top->elem = val;
			return true;
		}
		return false;
	}

	template<typename T>
	T queque<T>::pop()
	{
		if (length == 1)
		{
			ptrandelemqueque<T>* cursor = bottom;
			T val = bottom->elem;

			top = nullptr;
			bottom = nullptr;
			delete cursor;
			length--;
			return val;
		}
		if (!empty())
		{
			ptrandelemqueque<T>* cursor = top;
			T val = bottom->elem;

			bottom = bottom->ptrnext;
			delete cursor;
			length--;
			return val;
		}

		return T();

	}

	template<typename T>
	T queque<T>::peek()
	{
		if (!empty())
		{
			return bottom->elem;
		}
		return T();
	}

	template<typename T>
	bool queque<T>::remove()
	{
		if (length == 1)
		{
			ptrandelemqueque<T>* cursor = bottom;



			top = nullptr;
			bottom = nullptr;
			delete cursor;
			length--;
			return true;
		}
		if (!empty())
		{
			ptrandelemqueque<T>* cursor = bottom;


			bottom = bottom->ptrnext;



			delete cursor;
			length--;
			return true;
		}

		return false;
	}

	template<typename T>
	void queque<T>::append(T val)
	{

		if (!empty())
		{

			ptrandelemqueque<T>* newelem = new ptrandelemqueque<T>(val);
			top->ptrnext = newelem;
			top = newelem;

			length++;
			return;
		}
		ptrandelemqueque<T>* newelem = new ptrandelemqueque<T>(val);
		top = newelem;
		bottom = newelem;
		++length;


	}

	template<typename T>
	bool queque<T>::empty()
	{
		if (length == 0) {

			return true;

		}
		return false;
	}



}