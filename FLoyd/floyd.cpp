#include <iostream>
#include <vector>
#include <limits>
const int MAX = 4;
void floyd(int D[MAX][MAX], int n){
    for (int k=0; k<n; k++){
        for (int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][k] + D[k][j] <D[i][j])
                {D[i][j] = D[i][k] + D[k][j];}
            }
        }
    }
}
int main(){
    int inf = std::numeric_limits<int>::max();
    int matrix_example[4][4] = {{0,2, inf ,2}, {8,0,2,inf}, {5,inf,0,1},
    {7,inf,inf,0}};
    floyd(matrix_example, 4);
    for (int i =0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            std::cout <<matrix_example[i][j] << std::endl;
        }
    }
}