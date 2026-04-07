#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array {
    private:
        T* arr;
        unsigned int N;
    public:
        Array<T>() {
            arr = new T[0];
            N = 0;            
        };
        ~Array<T>() {
            delete[] arr;
        };
        Array<T>(unsigned int n) {
            arr = new T[n]();
            N = n;
        };
        Array(const Array& other) {
            this->N = other.N;

            this->arr = new T[other.size()]();

            for ( unsigned int i = 0; i < this->size(); i++ )
                this->arr[i] = other.arr[i];
        };
        Array& operator=(const Array& other) {
            if ( this != other )
            {
                this->N = other->N;
                delete[] this->arr;
                this->arr = new T[other.N]();
                for ( unsigned int i = 0; i < this->N; i++ )
                    this->arr[i] = other.arr[i];
            }
        };
        unsigned int size() const {
            return N;
        };
        T& operator[](unsigned int i) {
            if ( i < 0 || i >= this->N )
                throw std::runtime_error("out of  bounds!");
            return this->arr[i];
        };
        const T& operator[](unsigned int i) const{
            try {
                return this->arr[i];
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        };
};

#endif