#include "imagen.h"

using namespace std;

imagen::imagen(){
    ancho = 1;
    alto = 1;
    intensidad = 255;
    pixel.resize(alto);
    pixel[0].resize(ancho);
    pixel[0][0]=0;
}

imagen::imagen(const int intensidad, const vector<vector<int>> &matriz){
    ancho = matriz[0].size();
    alto = matriz.size();
    this->intensidad = intensidad;
    pixel.resize(alto);

    for(int i = 0; i < alto; i++){
        pixel[i].resize(ancho);

        for(int j = 0; j < ancho; j++){
            pixel[i][j] = matriz[i][j];
        }
    }
}

imagen::imagen(const imagen &img){
    ancho = img.ancho;
    alto = img.alto;
    intensidad = img.intensidad;
    pixel.resize(alto);

    for(int i = 0; i < alto; i++){
        pixel[i].resize(ancho);

        for(int j = 0; j < ancho; j++){
            pixel[i][j] = img.pixel[i][j];
        }
    }
}

imagen::~imagen(){}

imagen & imagen::operator =(const imagen & img){
	ancho = img.ancho;
	alto = img.alto;
	intensidad = img.intensidad;
	pixel = img.pixel;

	return *this;	
}

vector<vector<int>> & imagen::getMatrizPixel(){
	return pixel;
}

imagen imagen::transformar(void(*pfuncion)(vector<vector<int>>&, int, int)){

	imagen img_out(*this);
    imagen img_backup(*this);

    vector<vector<int>> matriz_aux;

	pfuncion(img_out.getMatrizPixel(), img_out.ancho, img_out.alto);

    matriz_aux = img_out.getMatrizPixel();    

    for(int i = 0; i < img_out.alto; i++){
        for(int j = 0; j < img_out.ancho; j++){
            if(matriz_aux[i][j] <= intensidad){}
            else{
                cerr<<"transformacion no valida"<<endl;
                return img_backup;
            }
        }
    }
    return img_out;
}

int imagen::getAlto(){
    return alto;
}

int imagen::getAncho(){
    return ancho;
}

int imagen::getIntensidad(){
    return intensidad;
}



ostream & operator<<(ostream &os, const	imagen &img){

    os<<"P2\n"<<img.ancho<<" "<<img.alto<<"\n"
    <<img.intensidad<<"\n";

    for(int i = 0; i < img.alto; i++){
                
        for(int j = 0; j < img.ancho; j++){
            os<<img.pixel[i][j]<<" ";
        }
        os<<"\n";
    }
    os<<"\n";
    return os;
}

std::istream & operator>>(std::istream &is, imagen &img){

    std::string linea;
    bool good = false;
    bool bad = false;
    bool comentarios = true;
    int ancho;
    int alto;
    int intensidad;
    vector<vector<int>> matrizpixel;



    if(is>>linea && linea=="P2"){

        while(comentarios){
            if(is>>linea && linea[0]!='#'){
                if(istringstream(linea)>>ancho && is>>alto && is>>intensidad 
                    && ancho > 0 && alto > 0 && intensidad >= 0)
                    good = true;
                else
                    bad = true;
                comentarios = false;
            }
            else{

                if(is.good()){
                    getline(is, linea);
                }else{
                    bad = true;
                    comentarios = false;
                }
            }
        }
    }else{

        cerr<<"Entrada no valida, se espera imagen en formato pgm\n";
        bad = true;
    }

    if(good){

    	matrizpixel.resize(alto);

    	for(int i = 0; i < alto && bad == false; i++){

            matrizpixel[i].resize(ancho);

            for(int j = 0; j < ancho; j++){

                if(is>>matrizpixel[i][j] && matrizpixel[i][j] <= intensidad){}
                else{
                	bad = true;
                	good = false;
                	break;
	           	}
    		}
    	}
    }

    if(good){
    	img.ancho = ancho;
    	img.alto = alto;
    	img.intensidad = intensidad;
    	img.pixel = matrizpixel;
    }

    if(bad){
    	cerr<<"imagen invalida\n";
    	is.clear(ios::badbit);
    }

    return is;
}
