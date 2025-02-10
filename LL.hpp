class Matrix{
private:
    float **mas;
    int n;
    int m;
public:
    Matrix(int a, int b);
    ~Matrix();
    void def();
    void def_2();
    float det();
    int rank();
    void multiply_by_N(int k);
    void print();
    void transpose();
};