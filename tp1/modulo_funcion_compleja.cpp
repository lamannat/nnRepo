#include "modulo_funcion_compleja.h"

string shutting_yard(string const & str){

	Stack<string> ops;
	string output = "";
	string onlyops = "+-/*^";
	string aux;

    for(size_t i = 0; i < str.size(); i++){

    	if(str[i] == ' ')
    		continue;

    	//numeros
    	if(isdigit(str[i]) || str[i] == 'j' || str[i] == 'z'){
    		while(isdigit(str[i]) || str[i] == 'j' || str[i] == 'z' || str[i] == '.'){
    			output += str[i];
    			i++;
    		}
    		output += ' ';
    		i--;
    		continue;
    	}

    	//funciones
    	switch(str[i]){
			case 'e':
				ops.push("exp");
				i += 3;
				break;
			case 'l':
				ops.push("ln");
				i += 2;
				break;
			case 'r':
				ops.push("re");
				i += 2;
				break;
			case 'i':
				ops.push("im");
				i += 2;
				break;
			case 'a':
				ops.push("abs");
				i += 3;
				break;
			case 'p':
				ops.push("phase");
				i += 5;
				break;
		}
    	

		//operadores
    	if(onlyops.find(str[i])!=string::npos){

    		while( !ops.empty() && (ops.top() != "(") && (precedencia(ops.top()) >= precedencia(str[i])) ){
    			output += ops.pop();
    			output += ' ';
    		}

    		ops.push(aux = str[i]);
    		continue;
    	}

    	//parentesis
    	if(str[i] == '('){
    		ops.push(aux = str[i]);
    		continue;
    	}

    	if(str[i] == ')'){
    		while(ops.top() != "("){
    			output += ops.pop();
    			output += ' ';
    		}

    		ops.pop();
    		continue;
    	}
    }

    while(!ops.empty()){
    	output += ops.pop();
    	output += ' ';
    }

    return output;
}

bool esta_balanceada(string const & cadena){

	Stack<char> Stack;
	bool balanced = true;

	for(size_t i = 0; i < cadena.size() && balanced; i++){
		switch(cadena[i]){
			case '{': //fall through
			case '[':
			case '(':
				Stack.push(cadena[i]);
				break;
			case '}':
				if(!Stack.empty() && Stack.top() == '{')
					Stack.pop();
				else
					balanced = false;
				break;
			case ']':
				if(!Stack.empty() && Stack.top() == '[')
					Stack.pop();
				else
					balanced = false;
				break;
			case ')':
				if(!Stack.empty() && Stack.top() == '(')
					Stack.pop();
				else
					balanced = false;
				break;
		}
	}
	if(!Stack.empty())
		balanced = false;

	return balanced;
}
int precedencia(string const & op){

	return precedencia(op[0]);
}
int precedencia(char const & op){

	if(op == '+' || op == '-')
		return 2;
	if(op == '*' || op == '/')
		return 3;
	if(op == '^')
		return 4;
	if(op == 'e' || op == 'r' || op == 'i' || op == 'l' || op == 'a' || op == 'p')
		return 5;

	return -1;
}

complejo evaluar_expresion_rpn(string & rpn, complejo &var){

	complejo out;
	complejo cx_aux, cx_aux2;
	Stack<complejo> pila;
	string s_aux;
	double d_aux;
	string onlyops = "+-/*^";

	for(size_t i = 0; i < rpn.size(); i++){

		if(rpn[i] == ' ')
			continue;

		//numeros, variable z y valores imaginarios
    	if(isdigit(rpn[i]) || rpn[i] == 'j' || rpn[i] == 'z'){

    		stringstream ss_aux;
    		
    		if(isdigit(rpn[i])){
    			while(rpn[i] != ' '){
    				s_aux += rpn[i];
    				i++;
    			}
    			ss_aux<<s_aux; //pasaje string a stream
    			ss_aux>>d_aux; //pasaje stram a double
    			pila.push(complejo(d_aux,0));
    			s_aux.clear();
    		}
    		else if(rpn[i] == 'j'){
    			pila.push(complejo(0,1));
    		}
    		else if(rpn[i] == 'z')
    			pila.push(var);
    		continue;
    	}

    	//operadores
    	if(onlyops.find(rpn[i])!=string::npos){
    		cx_aux = pila.pop();
    		cx_aux2 = pila.pop();
    		pila.push(calc(rpn[i], cx_aux, cx_aux2));
    		continue;
    	}

    	//funciones
    	switch(rpn[i]){
    		case 'a':
			case 'e':
				cx_aux = pila.pop();
				pila.push(calc(rpn[i],cx_aux));
				i += 3;
				break;
			case 'l':
			case 'r':
			case 'i':
				cx_aux = pila.pop();
				pila.push(calc(rpn[i],cx_aux));
				i += 2;
				break;
			case 'p':
				cx_aux = pila.pop();
				pila.push(calc(rpn[i],cx_aux));
				i += 5;
				break;
		}
	}

	out = pila.pop();
	return out;
}


complejo calc(char & op, complejo &right, complejo &left){

	complejo aux;

	switch(op){
		case '+':
			aux = left + right;
			break;
		case '-':
			aux = left - right;
			break;
		case '*':
			aux = left * right;
			break;
		case '/':
			aux = left / right;
			break;
		case '^':
			aux = pow(left, right);
	}
	return aux;
}

complejo calc(char & func, complejo &z){

	complejo aux;

	switch(func){
		case 'e':
			aux = exp(z);
			break;
		case 'i':
			aux = complejo(z.imag(),0);
			break;
		case 'l':
			aux = log(z);
			break;
		case 'r':
			aux = complejo(z.real(),0);
			break;
		case 'a':
			aux = complejo(abs(z),0);
			break;
		case 'p':
			aux = complejo(arg(z),0);
	}

	return aux;
}

bool funcion_valida(string const &func){

	int count_num = 0;
	string onlyops = "+-/*^";
	bool valida = true;

	for(size_t i = 0; i < func.size() && valida; i++){

		if(func[i] == ' ' || func[i] == '(' || func[i] == ')')
			continue;

		//conteo de numeros y variable z
    	else if(isdigit(func[i]) || func[i] == 'j' || func[i] == 'z'){

	  		if(isdigit(func[i])){
    			while(isdigit(func[i]) || func[i] == '.'){   //numeros de multiples digitos				
    				i++;
    			}
    			i--;
    			count_num++;
    		}
    		else if(func[i] == 'j' || func[i] == 'z'){
    			
    			count_num++;
    		}
    		continue;
    	}

    	//operadores
    	else if(onlyops.find(func[i])!=string::npos){
    		count_num--;
    		continue;
    	}

    	else if(func[i] == 'a' || func[i] == 'e' || func[i] == 'l' 
    		 || func[i] == 'r' || func[i] == 'i' || func[i] == 'p'){

    		switch(func[i]){
    			case 'a':
    				if(func[++i] == 'b' && func[++i] == 's' && func[++i] == '(')
    					break;
    				else
    					valida = false;
    				break;
				case 'e':
					if(func[++i] == 'x' && func[++i] == 'p' && func[++i] == '(')
    					break;
    				else
    					valida = false;
    				break;
				case 'l':
					if(func[++i] == 'n' && func[++i] == '(')
    					break;
    				else
    					valida = false;
    				break;
				case 'r':
					if(func[++i] == 'e' && func[++i] == '(')
    					break;
    				else
    					valida = false;
    				break;
				case 'i':
					if(func[++i] == 'm' && func[++i] == '(')
    					break;
    				else
    					valida = false;
    				break;
				case 'p':
					if(func[++i] == 'h' && func[++i] == 'a' && func[++i] == 's' && func[++i] == 'e' && func[++i] == '(')
    					break;
    				else
    					valida = false;
    				break;
			}
		}
		else{
			valida = false;
			break;
		}
	}
	if(count_num != 1)
		valida = false;
	return valida;
}
