#ifndef _PILA_H_
#define _PILA_H_

#define SIZE 100

template<typename T>
class Stack
{
	private:

	T * data;
	int size;
	int sup;

	//metodo privado que aumenta la capacidad de la pila en funcion de SIZE
	void resize();

	public:
		
	// Constructores y destructor.
	Stack();
	Stack(const Stack &);
	~Stack();

	// Funciones generales

	//Metodo pop como precondicion la pila no debe estar vacia y como postcondicion retira y devuelve el elemento en la posicion superior de la pila
	T pop();
	//metodo push recibe un dato de tipo T y lo coloca en la posicion superior de la pila
	void push(const T &);
	//metodo empty devuelve true si la pila se encuentra vacia, false en caso contrario
	bool empty();
	//metodo top devuelve una referencia constante al valor superior de la pila, como precondicion la pila no debe estar vacia
	T const & top();
	
};

//****************************
// Constructores y destructor.
//****************************

//Constructor por defecto de la clase Stack.
template<typename T>
Stack<T>::Stack(){

	size=0;
	sup=-1;
	data=NULL;
}

//Constructor copia de la clase de la clase Stack.
template<typename T>
Stack<T>::Stack(const Stack &orig){

	size=orig.size;
	sup=orig.sup;

	data = new T[size];

	for(int i = 0; i<=sup; i++)
		data[i] = orig.data[i];
 
}

//Destructor de la clase Stack. 
template<typename T>
Stack<T>::~Stack(){

	if(data)
		delete[] data;
}


//****************************
// Funciones en general.
//****************************
//Método para apilar en el Stack.
template<typename T>
void Stack<T>::push(const T &t){

	if(sup == size-1)
		this->resize();

	sup++;

	data[sup] = t;
}

//Método para desapilar en el Stack.
template<typename T>
T Stack<T>::pop(){

	if(this->empty()){
		std::cerr<<"Stack underflow"<<std::endl;
		exit(1);
	}

	T aux = data[sup];
	sup--;
	return aux;
}

//Método para verificar si el Stack se encuentra vacio.
template<typename T>
bool Stack<T>::empty(){	

	return (sup == -1);
}

//Método para obtención del elemento sup de la clase.
template<typename T>
T const & Stack<T>::top(){

	if(this->empty()){
		std::cerr<<"Stack underflow"<<std::endl;
		exit(1);
	}
	return data[sup];
}

template<typename T>
void Stack<T>::resize(){

	size = size + SIZE;
	T * aux = new T[size];

	for(int i = 0; i<=sup; i++)
		aux[i] = data[i];
	
	delete[] data;

	data = aux;	
}

#endif
