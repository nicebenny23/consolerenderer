namespace stackname {
	template <typename T>
	struct ptrandelemstack
	{

		ptrandelemstack<T>* ptrback;
		T elem;

		ptrandelemstack(T val);
		ptrandelemstack(T val, ptrandelemstack<T>* backpt);
	};


	template<typename T>
	class stack {

		ptrandelemstack<T>* top;
	public:
		bool swaptop(T val);
		T pop();
		T peek();
		bool remove();
		int length;
		void append(T val);
		stack();
		bool empty();



	};


	template<typename T>
	stack<T>::stack() {
		length = 0;
		top = nullptr;



	}

	template<typename T>
	ptrandelemstack<T>::ptrandelemstack(T val)
	{

		elem = T(val);
		ptrback = this;
	}

	template<typename T>
	ptrandelemstack<T>::ptrandelemstack(T val, ptrandelemstack<T>* backpt)
	{

		ptrback = backpt;
		elem = val;
	}

	template<typename T>
	bool stack<T>::swaptop(T val)
	{
		if (!empty())
		{
			top->elem = val;
			return true;
		}
		return false;
	}

	template<typename T>
	T stack<T>::pop()
	{
		if (length == 1)
		{
			ptrandelemstack<T>* cursor = top;
			T val = top->elem;

			top = nullptr;
			delete cursor;
			length--;
			return val;
		}
		if (!empty())
		{
			ptrandelemstack<T>* cursor = top;
			T val = top->elem;

			top = top->ptrback;
			delete cursor;
			length--;
			return val;
		}

		return T();

	}

	template<typename T>
	T stack<T>::peek()
	{
		if (!empty())
		{
			return top->elem;
		}
		return T();
	}

	template<typename T>
	bool stack<T>::remove()
	{
		if (length == 1)
		{
			ptrandelemstack<T>* cursor = top;


			top = nullptr;
			delete cursor;
			length--;
			return true;
		}
		if (!empty())
		{
			ptrandelemstack<T>* cursor = top;


			top = top->ptrback;
			delete cursor;
			length--;
			return true;
		}

		return false;
	}

	template<typename T>
	void stack<T>::append(T val)
	{

		if (empty())
		{

			ptrandelemstack<T>* newelem = new ptrandelemstack<T>(val);
			newelem->ptrback = newelem;
			top = newelem;
			length++;
			return;
		}
		ptrandelemstack<T>* newelem = new ptrandelemstack<T>(val, top);
		top = newelem;
		++length;


	}

	template<typename T>
	bool stack<T>::empty()
	{
		if (length == 0) {

			return true;

		}
		return false;
	}

}