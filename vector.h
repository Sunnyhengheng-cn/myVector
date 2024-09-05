#pragma once
#include<assert.h>

namespace yhr 
{
	/*template<class T>
	class vector {
	public:

	private:
		t* a;
		size_t _size;
		size_t _capacity;
	};*/
	
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		~vector() {
			if (_start) {
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}

		const_iterator begin()const {
			return _start;
		}

		const_iterator end()const {
			return _finish;
		}

		iterator begin() {
			return _start;
		}

		iterator end() {
			return _finish;
		}

		void reserve(size_t n) {

			if (n > capacity()) {
				T* tmp = new T[n];

				size_t oldsize = size();
				if (_start) {
					memcpy(tmp, _start, sizeof(T) * size());
					delete[] _start;
				}

				_finish = tmp + oldsize;
				_start = tmp;
				_end_of_storage = _start + n;
			}
		}

		size_t capacity() {
			return _end_of_storage - _start;
		}
		
		size_t size() {
			return _finish - _start;
		}

		T& operator[](size_t i) {
			assert(i < size());
			return _start[i];
		}


		void push_back(const T& x) {
			if (_finish == _end_of_storage) {
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = x;
			++_finish;
		}

		void pop_back() {
			assert(size() > 0);
			--_finish;
		}

		void insert(iterator pos, const T& x) {
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _end_of_storage) {
				size_t len = pos - _start;
				
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);

				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos){
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
		}

		void erase(iterator pos) {
			assert(pos >= _start);
			assert(pos < _finish);

			iterator it = pos+1;
			while (it<_finish) {
				*(it - 1) = *it;
				++it;
			}
			--_finish;
		}


	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;

	};


}

void test_vector1() {


	//std::vector<int>v1;
	yhr::vector<int>v1;
	//v1.pop_back();

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);


	for (size_t i = 0; i < v1.size(); i++) {
		cout << v1[i] << " ";
	}
	cout << endl;


	v1.pop_back();

	//std::vector<int>::iterator it = v1.begin();
	yhr::vector<int>::iterator it = v1.begin();
	while (it != v1.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << typeid(it).name() << " ";

}

void vector_test02() {
	yhr::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);

	v1.insert(v1.begin() + 3, 999);
	v1.erase(v1.begin());
	for (auto  e : v1) {
		cout << e << " ";
	}
	cout << endl;
}