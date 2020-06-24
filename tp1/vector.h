#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

template<typename T>
class vector{

private:

	T * arr;
	int size_;

public:

	//constructores y desctructor
	vector();
	vector(const vector &);
	~vector();

	//metodos

	//metodos size, devuelven la capacidad de almacenamiento actual del vector
	int size();
	int size() const;
	//metodo resize recibe un entero que indica que tamaño debe tomar el vector, en caso de que el nuevo tamaño sea mayor que el actual
	//se puede indicar con que dato de tipo T se quieren llenar los nuevos espacios disponibles, si no se indica se llama al constructor por defecto de T
	void resize(int);
	void resize(int, T&);

	//operadores
	T & operator[](int);
	T const & operator[] (int) const;
	vector& operator= (const vector&);
};

//CONSTRUCTORES Y DESTRUCTOR

template<typename T>
vector<T>::vector(){
	arr = NULL;
	size_ = 0;
}

template <typename T>
vector<T>::vector(const vector & v){

	size_ = v.size_;
	arr = new T[size_];

	for(int i = 0; i<size_; i++)
		arr[i] = v.arr[i];
}

template<typename T>
vector<T>::~vector(){

	if(arr)
		delete[] arr;
}

//METODOS

template<typename T>
int vector<T>::size(){

	return size_;
}

template<typename T>
int vector<T>::size() const{

	return size_;
}



template<typename T>
void vector<T>::resize(int x){
	T a = T();
	this->resize(x, a);
}

template<typename T>
void vector<T>::resize(int x, T & fill_value){

	if(size_ == x)
		return;

	T * aux = new T[x];

	if(size_ < x){
		for(int i = 0; i<size_; i++)
			aux[i] = arr[i];
		for(int i = size_; i<x; i++)
			aux[i] = fill_value;
	}else{
		for(int i = 0; i<x; i++)
			aux[i] = arr[i];
	}
	

	delete[] arr;
	arr = aux;
	size_ = x;
}

//OPERADORES

template<typename T>
T & vector<T>::operator[](int x){

	return arr[x];
}

template<typename T>
T const & vector<T>::operator[](int x) const{

	return arr[x];
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& v){

	size_ = v.size_;
	T * aux = new T[size_];

	for(int i = 0; i<size_; i++)
		aux[i] = v.arr[i];

	delete[] arr;

	arr = aux;

	return *this;
}


#endif
