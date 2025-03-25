#include <iostream>

using namespace std;

template<class T>
class Notas {
private:
    string nome;
    T nota;
public:
    Notas(string nome, T nota);
    string getNome(void);
    T getNota(void);
};

template<class T>
Notas<T>::Notas(string nome, T nota) {
    this->nome = nome;
    this->nota = nota;
}

template<class T>
string Notas<T>::getNome(void) {
    return this->nome;
}

template<class T>
T Notas<T>::getNota(void) {
    return this->nota;
}

int main()
{
    Notas<int> alunoA("Klaus", 10);
    Notas<float> alunoB("Laiza", 9.95);

    cout << endl;
    cout << "  NOME │ NOTA" << endl;
    cout << " ──────┼──────" << endl;
    cout << " " << alunoA.getNome() << " │  " << alunoA.getNota() << endl; 
    cout << " " << alunoB.getNome() << " │ " << alunoB.getNota() << endl; 
    cout << endl;
    
    return 0;
}