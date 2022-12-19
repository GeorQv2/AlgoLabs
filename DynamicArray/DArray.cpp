#include <iostream>


template<typename T>
class DArray {
public:
	//Constructor by default
	DArray() :
		size_(0),
		capacity_(defaultArraySize_)
	{
		std::cout << "Call Constructor by default" << std::endl;
		pi_ =  (T*) malloc(sizeof(T) * capacity_);
	}

	//Constructor with integer
	DArray(int capacity):
		size_(0),
		capacity_(capacity)
	{
		std::cout << "Call Constructor with integer" << std::endl;
		pi_ = (T*) malloc(sizeof(T) * capacity_);
	}

	//Copy constructor
	DArray(const DArray& other) {
		std::cout << "Call Copy constructor" << std::endl;
		pi_ = (T*) malloc(other.capacity_ * sizeof(T));
		for (size_t i = 0; i < other.size_; i++)
		{
			new(pi_ + i) T(other.pi_[i]);
		}
		size_ = other.size_;
		capacity_ = other.capacity_;
	}

	//Copy assignment operator
	DArray& operator=(DArray& other) {
		std::cout << "Call Copy assignment operator" << std::endl;
		DArray<T> temp = other;
		swap(temp);
		return *this;
	}

	//Destructor
	~DArray() {
		for (size_t i = 0; i < size_; i++)
		{
			pi_[i].~T();
		}
		free(pi_);
		std::cout << "Memory was freed" << std::endl;
	}

	//Move constructor
	DArray(DArray&& other) noexcept{
		std::cout << "Call Move constructor" << std::endl;
		size_ = other.size_;
		capacity_ = other.capacity_;
		pi_ = other.pi_;
		other.size_ = 0;
		other.capacity_ = 0;
		other.pi_ = nullptr;
	}

	//Move Assignment Operator
	DArray& operator=(DArray&& other) noexcept 
	{
		std::cout << "Call Move Assignment Operator" << std::endl;
		if (&other != this)
		{
			for (size_t i = 0; i < size_; i++)
			{
				pi_[i].~T();
			}
			free(pi_);
			pi_ = other.pi_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			other.size_ = 0;
			other.capacity_ = 0;
			other.pi_ = nullptr;
		}
		return *this;
	}

	//append
	int insert(const T& value) {
		if (size_ == capacity_) {
			resize();
		}
		new (pi_ + size_) T(value);
		return size_++;
	}
	
	//insert
	int insert(int index, const T& value) {
		if (index < 0) {
			return -1;
		}
		if (size_ == capacity_)
		{
			resize();
		}
		if (index >= size_)
		{
			new (pi_ + size_) T(value);
		}
		else {
			for (size_t i = size_; i > index; i--)
			{
				new (pi_ + i) T(std::move(pi_[i - 1]));
				pi_[i - 1].~T();
			}
			pi_[index].~T();
			new (pi_ + index) T(value);
		}
		return size_++;
	}

	void remove(int index) {
		if (index < 0 || size_ == 0 || index >= size_) {
			return;
		}
		for (size_t i = index; i < size_ - 1; i++)
		{
			pi_[i].~T();
			new (pi_ + i) T(std::move(pi_[i + 1]));
		}
		pi_[--size_].~T();
	}

	const T& operator[](int index) const {
		return pi_[index];
	}

	T& operator[](int index){
		return pi_[index];
	}

	int size() const {
		return size_;
	}
	
	int capacity() const {
		return capacity_;
	}

	T* getPointer() const {
		return pi_;
	}

	//ConstIterator
	class ConstIterator {
	public:
		ConstIterator(DArray<T>* other, bool isReversed) {
			ptr_ = other;
			isReversed_ = isReversed;
			if (isReversed) {
				curPtr_ = other->pi_ + (other->size_ - 1);
			}
			else {
				curPtr_ = other->pi_;
			}
		}
		const T& get() const {
			return *curPtr_;
		}
		void next() {
			if (isReversed_) {
				curPtr_ += -1;
			}
			else {
				curPtr_ += 1;
			}
		}
		bool hasCurrent() const {
			return ((curPtr_ >= ptr_->pi_) && (curPtr_ <= ptr_->pi_ + (ptr_->size_ - 1)));
		}
	private:
		DArray<T>* ptr_;
		T* curPtr_;
		bool isReversed_;
	};
	//

	//Iterator
	class Iterator {
	public:
		Iterator(DArray<T>* other, bool isReversed) {
			ptr_ = other;
			isReversed_ = isReversed;
			if (isReversed) {
				curPtr_ = other->pi_ + (other->size_ - 1);
			}
			else {
				curPtr_ = other->pi_;
			}
		}
		const T& get() const {
			return *curPtr_;
		}

		void set(T value) {
			curPtr_->~T();
			new (curPtr_) T(value);
		}

		void next() {
			if (isReversed_) {
				curPtr_ += -1;
			}
			else {
				curPtr_ += 1;
			}
		}
		bool hasCurrent() const {
			return ((curPtr_ >= ptr_->pi_) && (curPtr_ <= ptr_->pi_ + (ptr_->size_ - 1)));
		}
	private:
		DArray<T>* ptr_;
		T* curPtr_;
		bool isReversed_;
	};
	//

	Iterator iterator() {
		return Iterator(this, false);
	}
	ConstIterator iterator() const {
		return ConstIterator(this, false);
	}
	Iterator reverseIterator() {
		return Iterator(this, true);
	}
	ConstIterator reverseIterator() const {
		return ConstIterator(this, true);
	}

private:
	int defaultArraySize_ = 10;
	int resizeRate_ = 2;
	int size_;
	int capacity_;
	T* pi_;

	void swap(DArray& other) {
		std::swap(pi_, other.pi_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}

	void resize() {
		capacity_ *= resizeRate_;
		T* temp = (T*)malloc(sizeof(T) * capacity_);
		for (size_t i = 0; i < size_; i++)
		{
			new (temp + i) T(std::move(pi_[i]));
			pi_[i].~T();
		}
		free(pi_);
		pi_ = temp;
	}
};


int main() {
	DArray<int> a;
	a.insert(10);
	a[0] = 20;
}