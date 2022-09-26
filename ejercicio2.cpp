#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    int n,largo,ancho,posicion_x,radio;
    // tomo los primeros 3 valores: cantidad de aspersores - largo - ancho
    while(scanf("%d %d %d",&n,&largo,&ancho) != EOF){

        int res = 0;
        
        // si existe campo a cubrir (longitud mayor que cero)
        if (largo > 0) {

            // ya veremos que es esto
            vector<pair<double,double>> intervalos;
            
            // tomo n veces, los dos valores para ubicar y conocer el radio del aspersor
            for(int i=0;i<n;i++){

                scanf("%d %d",&posicion_x,&radio);
                double dx = sqrt((double)radio*radio-(ancho/2.0)*(ancho/2.0));

                // descarto los aspersores de radio < ancho
                // si dx < 0, osea w >= r, comparando los double da false.
                if(dx == dx){
                    intervalos.push_back({(double)posicion_x-dx,(double)posicion_x+dx});
                }
            }

            // ordeno de menor a mayor segundo la primera componente
            // es decir, donde comienza el intervalo en el eje x
            sort(intervalos.begin(),intervalos.end());
          
            double largo_Actual = 0;

            for(int i=0; i < intervalos.size() && largo_Actual < largo; i++){
                
                // valido que no existan intervalos vacios entre los circulos
                // es decir que todos se superponen
                if(intervalos[i].first > largo_Actual) {
                    break;
                }
                
                // sumo
                res++;
                
                // el extremo mas lejano actual como el segundo elemento del aspersor actual
                double mas_lejano = intervalos[i].second;

                // valido entre todos los aspersores que tienen inicio superpuesto
                // con el final del aspersor recien colocado
                    while(i+1<intervalos.size() && intervalos[i+1].first <= largo_Actual){
                        // Tomo el siguiente aspersor que llegue mas lejos, con inicio ya validado.
                        mas_lejano = max(intervalos[++i].second,mas_lejano);
                    }
                        // seteo el actual punto mas lejano cubierto (mayor valor de x cubierto)
                        largo_Actual = mas_lejano;
                    }
            
            // si detecto que interrumpí la colocacion de aspersores, retorno -1
            if(largo_Actual < largo) res = -1;
        }
        // print resultado
        printf("%d\n",res);
    }
}