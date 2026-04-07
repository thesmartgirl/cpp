#ifndef ARRAY_HPP
#define ARRAY_HPP

template <class T>
class Array {
    private:
        T* arr;
    public:
        Array<T>() {
            this.arr = new T[0];
        };
        ~Array<T>() {
            delete[] arr;
        };
        Array<T>(unsigned int n) {
            T* arr = new T[n];
        };
        Array(const Array& other) {

            this->arr = new T[this->size()];

            for ( int i = 0; i < this.size(); i++ )
                this->arr[i] = other.arr[i];
        };
        Array& opertaor=(const Array& other) {
            if ( this != other )
            {
                delete[] this.arr;
                this.arr = new T[this->size()];
                for ( int i = 0; i < this.size(); i++ )
                    this->arr[i] = other.arr[i];
            }
        };
        unsigned int size() const {
            return sizeof(this->arr) / sizeof(this->arr[0]);
        };
        T& operator[](unsigned int i) {
            return this->arr[i];
        };

};

#endif