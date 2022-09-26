#include <iostream>
#include <vector>

using namespace std;

int n,m,total,rondas=1;
vector<pair<int,int>> posta_obligada;
vector<int> posta;
vector<vector<bool>> mapa,mapa_aux;
vector<vector<int>> direcciones = {{1,0},{0,1},{-1,0},{0,-1}};

// cuento casillas que me falta recorrer
int recorrido_aux(int x, int y){
    
    // si me paso de margen, podo la recursion
    if(x<0||y<0||x>=n||y>=m) return 0;

    // si me piso, podo la recursion.
    // se contempla lo ya recorrido y ademas lo visitado desde el inicio en la funcion recorrido()
    if(mapa[x][y] || mapa_aux[x][y]) return 0;
    
    // señalo como visitada mi posicion
    mapa_aux[x][y] = true;
    int suma = 1;

    // muevo en cada direccion posible
    for(auto& dir : direcciones){
        int pos_x = dir[0] + x, pos_y = dir[1] + y;
        suma += recorrido_aux(pos_x, pos_y);
    }

    // retorno la cantidad de casillas contadas pendientes por recorrer
    return suma;
}

int recorrido(int x, int y, int pasos) {

    // si me fui de margen, podo la recursion
    if(x<0||y<0||x>=n||y>=m) return 0;
    
    // si ya pasé por esa casilla, podo la recursion
    if(mapa[x][y]) return 0;

    // si termine de recorrer la grilla, tengo una solucion.
    else if(pasos == posta[3]) return 1;
    
    // si llegué al numero de pasos de la tercera posta
    else if(pasos == posta[2]) {
        
        // si no llegue a la tercera, podo la recursion
        if(x!=posta_obligada[2].first || y!=posta_obligada[2].second) return 0;
    
    // si llegué al numero de pasos de la segunda posta
    } else if(pasos == posta[1]) {
    
        // si no llegue a la segunda, podo la recursion
        if(x!=posta_obligada[1].first || y!=posta_obligada[1].second) return 0;
    
    // si llegué al numero de pasos de la primera posta
    } else if(pasos == posta[0]) {
    
        // si no llegue a la primera posta, podo la recursion
        if(x!=posta_obligada[0].first || y!=posta_obligada[0].second) return 0;
    
    // entonces, estoy en un paso mas, y no pode por ninguna de las restricciones
    } else {
    
        for(int i=0;i<4;i++) {
            
            // si estoy en alguna de las postas, podo la recursion
            if(x==posta_obligada[i].first && y==posta_obligada[i].second) {
                return 0;
            }
                
            // calculo los pasos MINIMOS que faltan realizar para la siguiente posta
            int distancia_minima = abs(x-posta_obligada[i].first) + abs(y-posta_obligada[i].second);

            // calculo pos pasos de diferencia que estoy de la siguiente posta
            int diferencia_pasos = posta[i] - pasos;

            // Me quedan pasos por dar a la siguiente posta PERO los pasos minimos que me faltan dar 
            // son mas que la minima distancia ya se que no voy a cumplir lo pedido, entonces podo la recursion.
            if(diferencia_pasos > 0 && diferencia_pasos < distancia_minima) return 0;
        }
    }

    // realizo otro recurrido para contar las casillas que me faltan visitar
    // si las casillas que me faltan visitar no son exactamente los pasos que me falta dar, podo la recursion.
    mapa_aux.assign(n,vector<bool>(m));
    mapa_aux[x][y] = true;
    int pendiente_pasos = recorrido_aux(0,1);
    if(pendiente_pasos != total-pasos) {
        return 0;
    }

    // doy un paso en cada una de las direcciones, y repito todo el proceso.
    mapa[x][y] = true;
    int caminos = 0;
    for(auto& dir : direcciones){
        int pos_x = dir[0] + x, pos_y = dir[1] + y;
        caminos += recorrido(pos_x, pos_y, pasos+1);
    }
    mapa[x][y] = false;

    // retorno cantidad de caminos encontrados
    return caminos;
}

int main() {
    while(scanf("%d %d",&n,&m),(n+m)){
        
        // vector de postas asignadas
        posta_obligada.assign(3, {0,0});  
        
        scanf("%d %d %d %d %d %d", 
                &posta_obligada[0].first, &posta_obligada[0].second,
                &posta_obligada[1].first, &posta_obligada[1].second, 
                &posta_obligada[2].first, &posta_obligada[2].second
        );
        
        // asigno la ultima posta, posicion al lado de la inical
        posta_obligada.push_back(make_pair(0,1));

        // lleno la matriz de ubicaciones con false
        mapa.assign(n,vector<bool>(m,false));
        
        // cantidad total de celdas
        total = n*m;
        
        // postas a controlar
        posta = {total/4,total/2,3*total/4,n*m};
        
        // muestro el resultado de la primera operacion antes de tomar la siguiente
        printf("Case %d: %d\n",rondas++,recorrido(0,0,1));
    }
}
