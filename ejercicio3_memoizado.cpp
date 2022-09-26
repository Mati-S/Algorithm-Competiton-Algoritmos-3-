#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <ctime> 
using namespace std;

//unsigned t_inicial, t_final;

#define INFINITO 10000

struct Aspersores {
   double pi;
   double pf; 
   int price;
};

vector<vector <int>> memo;

bool aspersor_sorter(Aspersores const&, Aspersores const&);
int precio_minimo(int, double);
int minimo(int, int);
bool doubleEquals(double, double);

int CANTIDAD_ASPERSORES;
int LONGITUD_MAXIMA;
vector<Aspersores> intervalos;

int main() {
    int n,largo,ancho,posicion_x,radio, precio;
    // cantidad - largo - ancho
    while(scanf("%d %d %d",&n,&largo,&ancho) != EOF) {
        
        CANTIDAD_ASPERSORES = n;
        LONGITUD_MAXIMA = largo;

        int res;
        memo.assign(n,vector<int>(n,INFINITO));

        // si existe campo a cubrir (longitud mayor que cero)
        if (largo > 0) {
            // tomo n veces, los 3 valores para ubicar, conocer el radio del aspersor y precio
            for(int i=0;i<n;i++) {

                scanf("%d %d %d",&posicion_x,&radio,&precio);
                double dx = sqrt((double)radio*radio-(ancho/2.0)*(ancho/2.0));
                // descarto los aspersores de radio < ancho
                // si dx < 0, osea w >= r, comparando los floats da false.  
                if(dx == dx) {
                    //intervalos.push_back({(double)p-dx,(double)p+dx});
                    intervalos.push_back({(double)posicion_x-dx,(double)posicion_x+dx, precio});
                } 
            }
            std::sort(intervalos.begin(),intervalos.end(), &aspersor_sorter);
            //t_inicial=clock();
            res = precio_minimo(0,0);
            //t_final = clock();
        }
        // print resultado
        if(res == INFINITO) res = -1;
        //printf("ΔT:%d\n",t_final-t_inicial);
        printf("RES: %d\n",res);
    }
}

int minimo(int a, int b) {
    //printf("a=%d, b=%d\n", a, b);
    if(a > b) return b;
    return a;
}

int darIndex(double limite) {
    if(!doubleEquals(limite,0L)) {
        int res = -1;
        for (int i = 0; i < CANTIDAD_ASPERSORES; i++) {
            if(doubleEquals(limite, intervalos[i].pf)) res = i;
        }
        //printf("Para el limite %f, el index es: %d\n",limite, res);
        return res;
    } else {
        return 0;
    }
}

int precio_minimo(int index, double limite) {

    // termine de cubrir
    if(limite >= LONGITUD_MAXIMA) {
        //printf("FIN. index=%d, limite=%f\n", index, limite);
        return 0;
    }

    // termine de recorrer y no cubri
    if(index == CANTIDAD_ASPERSORES && limite < LONGITUD_MAXIMA) {
        //printf("PODA: no completo de cubrir. index %d\n", index);
        return INFINITO;
    }

    // falta de superposicion
    if(intervalos[index].pi > limite) {
        //printf("PODA: Espacios sin cubrir");
        return INFINITO;
    }

    // esta contenido, no aporta en la seleccion en curso
    if(intervalos[index].pf <= limite) {
        return precio_minimo(index + 1, limite);
    }

    if(memo[index][darIndex(limite)] != INFINITO) {
        //printf("MEMOIZANDO. m[%d][%d]=%d\n",index,darIndex(limite),memo[index][darIndex(limite)]);
        return memo[index][darIndex(limite)];
    } else {
        memo[index][darIndex(limite)] = minimo(
                // tomo el aspersor actual (precio), avanzo al siguiente y seteo nuevo limite 
                precio_minimo(index + 1, intervalos[index].pf) + intervalos[index].price,
                // no tomo el aspersor actual, entonces no cambia el limite actual y avanzo al siguiente aspersor
                precio_minimo(index + 1, limite)
            );
        return memo[index][darIndex(limite)];
    } 
}

bool aspersor_sorter(Aspersores const& asp1, Aspersores const& asp2) {
    return asp1.pi < asp2.pi;
}

bool doubleEquals(double left, double right) {
  return (fabs(left - right) < .0001);
}