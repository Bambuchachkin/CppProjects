Matrix::Matrix(int a, int b){
    n = a;
    m = b;
    mas = new float*[n];
    for (int i=0; i<n; i++){
        mas[i] = new float[m];
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            mas[i][j] = 0;
        }
    }
}

Matrix::~Matrix(){
    for (int i=0; i<n; i++){
        delete[] mas[i];
    }
    delete[] mas;
}

void Matrix::def(){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin>>mas[i][j];
        }
    }
}

void Matrix::def_2(){
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            mas[i][j] = 2;
        }
    }
}

void Matrix::print(){
    cout<<"Результат:"<<endl;
    for (int i =0; i<n; i++){
        for( int j=0; j<m; j++){
            cout<<mas[i][j]<<" ";
        }
        cout<<endl;
    }
}

float Matrix::det(){
    if(n!=m){
        cout<<"ERROR: "<<"11010000 10110100 11010001 10000011 11010001 10000000 11010000 10110000 11010000 10111010"<<endl;
        return(-1);
    }
    if (n==1){
        return(mas[0][0]);
    }
    Matrix Minor(n-1, n-1);
    float D = 0;
    for (int i=0; i<m; i++){ //разложение по 1ой строке
        for (int i1=0; i1<n-1; i1++){
            for (int j1=0; j1<n; j1++){
                if (j1>i){
                    Minor.mas[i1][j1-1] = mas[i1+1][j1];
                }
                if (j1<i){
                    Minor.mas[i1][j1] = mas[i1+1][j1];
                }
            }
        }
        if (i%2==0){
            D += mas[0][i] * Minor.det();
        } else{
            D -= mas[0][i] * Minor.det();
        }
    }
    return(D);
}

void Matrix::multiply_by_N(int k){
    for (int i =0; i<n; i++){
        for( int j=0; j<m; j++){
            mas[i][j]*=k;
        }
    }
}

int Matrix::rank(){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (mas[i][j]!=0){ //нашли опорный элемент
                float del = mas[i][j];
                for (int il=0; il<n; il++){
                    if (il!=i){
                        for(int jl=0; jl<m; jl++){
                            if ((jl!=j) and (mas[il][j]!=0)){
                                mas[il][jl]-=mas[i][jl]*(mas[il][j]/mas[i][j]); //превращаем все элементы в столбце опорного элемента в нули а и меняем остальные элементы в строке
                            }
                        }
                        mas[il][j] = 0;
                    }
                }
                break;
            }
        }
    }
    int Rank = 0;
    int flag=0;
    for (int i=0; i<n; i++){
        flag = 0;
        for (int j=0; j<m; j++){
            if(mas[i][j]!=0){
                flag = 1; //Если строка не нулевая, увеличить ранг на единицу
                break;
            }
        }
        if (flag == 1){
            Rank++;
        }
    }
    return(Rank);
}

void Matrix::transpose(){
    float **N_data = new float*[m];
    for (int i=0; i<m; i++){
        N_data[i] = new float[n];
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            N_data[j][i] = mas[i][j];
        }
    }
    this->~Matrix();
    int const_1 =n;
    this->n=m;
    this->m=const_1;
    mas = N_data;
}