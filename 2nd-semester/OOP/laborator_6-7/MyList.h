#pragma once

template <typename TElem>
class Iterator;

template <typename TElem>
class MyVector
{
public:
	/*Constructor implicit
	*/
	MyVector();

	/*Constructor prin copiere
	*/
	MyVector(const MyVector& ot);

	/*Destructor
	*/
	~MyVector();

	/*Operatorul de asignare
	* Inlocuieste continutul instantei de obiect cu continutul obiectului ot
	* ot = obiect de tip MyVector
	*/
	MyVector& operator=(const MyVector& ot);


	/*
	Move constructor - constructor explicit prin mutarea continutului din ot in instanta curenta de MyVector
	* ot - referinta la un obiect MyVector de tip R-value
	* aftermath: instanta curenta de MyVector are continutul obiectului ot, obiectul ot se elibereaza
	*/
	MyVector(MyVector&& ot);

	/*
	Move assignment
	*aftermath: instanta curenta de MyVector are continutul obiectului ot, obiectul ot se elibereaza
	*/
	MyVector& operator=(MyVector&& ot);

	/*Functia de adaugare la sfarsitul vectorului
	*/
	void push_back(const TElem& el);

	/*Functia de stergere obiect de pe pozitia poz
	*/
	void erase(const int poz);

	/*returns: obiectul de pe pozitia poz din instanta curenta de MyVector
	*/
	TElem& at(int poz) const;

	/*Functia care modifica obiectul de pe pozitia poz
	* poz - int, pozitia din vector a obiectului pe care doresti sa-l modifici
	* el - obiectul modificat pe care il doresti pe pozitia poz
	*/
	void set(int poz, const TElem& el);

	/*returns: dimensiunea instantei de MyVector
	*/
	int size() const noexcept;

	friend class Iterator<TElem>;
	//functii care creaza iteratori
	Iterator<TElem> begin() noexcept;
	Iterator<TElem> end();


private:
	int lg;
	int cap;
	TElem* elems;

	void ensureCapacity();
};


template<typename TElem>
MyVector<TElem>::MyVector() :elems{ new TElem[5] }, cap{ 5 }, lg{ 0 } {}

template<typename TElem>
MyVector<TElem>::MyVector(const MyVector<TElem>& ot) {
	elems = new TElem[ot.cap];
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
}

template<typename TElem>
MyVector<TElem>& MyVector<TElem>::operator=(const MyVector<TElem>& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	elems = new TElem[ot.cap];
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}


template<typename TElem>
MyVector<TElem>::~MyVector() {
	delete[] elems;
}

template<typename TElem>
MyVector<TElem>::MyVector(MyVector&& ot) {
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

template<typename TElem>
MyVector<TElem>& MyVector<TElem>::operator=(MyVector<TElem>&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

template<typename TElem>
void MyVector<TElem>::push_back(const TElem& el) {
	ensureCapacity();
	elems[lg++] = el;
}

template<typename TElem>
void MyVector<TElem>::erase(const int poz)
{
	for (int i = poz; i < lg - 1; i++)
		this->elems[i] = elems[i + 1];
	this->lg--;
}

template<typename TElem>
TElem& MyVector<TElem>::at(int poz) const {
	return elems[poz];
}

template<typename TElem>
void MyVector<TElem>::set(int poz, const TElem& el) {
	elems[poz] = el;
}

template<typename TElem>
int MyVector<TElem>::size() const noexcept {
	return lg;
}

template<typename TElem>
void MyVector<TElem>::ensureCapacity() {
	if (lg < cap) {
		return;
	}
	cap *= 2;
	TElem* aux = new TElem[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}

template<typename TElem>
Iterator<TElem> MyVector<TElem>::begin() noexcept
{
	return Iterator<TElem>(*this);
}


template<typename TElem>
class Iterator {
private:
	const MyVector<TElem>& v;
	int poz = 0;
public:
	Iterator(const MyVector<TElem>& v) noexcept;
	Iterator(const MyVector<TElem>& v, int poz)noexcept;
	bool valid()const noexcept;
	TElem& element() const noexcept;
	void next();
	TElem& operator*();
	Iterator& operator++();
	bool operator==(const Iterator& ot)noexcept;
	bool operator!=(const Iterator& ot)noexcept;
};

template<typename TElem>
Iterator<TElem>::Iterator(const MyVector<TElem>& v) noexcept :v{ v } {}

template<typename TElem>
Iterator<TElem>::Iterator(const MyVector<TElem>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename TElem>
bool Iterator<TElem>::valid()const noexcept {
	return poz < v.lg;
}

template<typename TElem>
TElem& Iterator<TElem>::element() const noexcept {
	return v.elems[poz];
}

template<typename TElem>
void Iterator<TElem>::next() {
	poz++;
}

template<typename TElem>
TElem& Iterator<TElem>::operator*() {
	return element();
}

template<typename TElem>
Iterator<TElem>& Iterator<TElem>::operator++() {
	next();
	return *this;
}

template<typename TElem>
bool Iterator<TElem>::operator==(const Iterator<TElem>& ot) noexcept {
	return poz == ot.poz;
}

template<typename TElem>
bool Iterator<TElem>::operator!=(const Iterator<TElem>& ot)noexcept {
	return !(*this == ot);
}
template<typename TElem>
Iterator<TElem> MyVector<TElem>::end() {
	return Iterator<TElem>(*this, lg);
}