	#pragma once
using namespace std;
#include <cassert>

const int NUM_ELEMENTS_PER_NODE = 6;
//----------------------------------------------------------------------------------------------------------
// NODE CLASS
template <class T>
class Node 
{
public:
	//CONSTRUCTORS
	Node()
	{
		next_ = NULL;
		prev_ = NULL;
		values_ = new T[NUM_ELEMENTS_PER_NODE];
		num_elements = 0;
	}
	Node(const T& v)
	{
		next_ = NULL;
		prev_ = NULL;
		values_ = new T[NUM_ELEMENTS_PER_NODE];
		values_[0] = v;
		num_elements = 1;
	}
	Node(T* const v, unsigned int size)
	{
		next_ = NULL;
		prev_ = NULL;
		values_ = v;
		num_elements = size;
	}
	// REPRESENTATION
	T *values_;
	Node<T>* next_;
	Node<T>* prev_;
	unsigned int num_elements;
};

template <class T> class dslist;

// -----------------------------------------------------------------
// LIST ITERATOR 
template <class T>
class list_iterator {
public:
	// default constructor, copy constructor, assignment operator, & destructor
	list_iterator(Node<T>* p = NULL, int index = 0) : ptr_(p),offset(index) {} 

	// dereferencing operator gives access to the value at the pointer
	T operator*() 
	{ 
		return ptr_->values_[offset];
	}

	// increment & decrement operators
	list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
		//Move on to next node if no more elements in current node
		if (offset == (ptr_->num_elements)-1)
		{
			ptr_ = ptr_->next_;
			offset = 0;
		}
		else
		{
			offset++;
		}
		
		
		return *this;
	}
	list_iterator<T> operator++(int) { // post-increment, e.g., iter++
		list_iterator<T> temp(*this);
		//Move on to next node if no more elements in current node
		if (offset == (ptr_->num_elements) - 1)
		{
			ptr_ = ptr_->next_;
			offset = 0;
		}
		else
		{
			offset++;
		}
		return temp;
	}
	list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
		//Move on to next node if no more elements in current node
		if (offset == 0)
		{
			ptr_ = ptr_->prev_;
			offset = (ptr_->num_elements) - 1;
		}
		else
		{
			offset--;
		}
		
		return *this;
	}
	list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
		list_iterator<T> temp(*this);
		//Move on to next node if no more elements in current node
		if (offset == 0)
		{
			ptr_ = ptr_->prev_;
			offset = (ptr_->num_elements) - 1;
		}
		else
		{
			offset--;
		}
		return temp;
	}
	// the dslist class needs access to the private ptr_ member variable
	friend class dslist<T>;

	// Comparions operators are straightforward
	bool operator==(const list_iterator<T>& r) const 
	{
		return (ptr_ == r.ptr_ && offset == r.offset);
	}
	bool operator!=(const list_iterator<T>& r) const 
	{
		return (ptr_ != r.ptr_  || offset != r.offset);
	}

	//Helper method that returns a copy of an iterator of the next adjacent element to the current iterators value
	list_iterator<T> next() 
	{
		list_iterator<T> temp(*this);
		if (ptr_->next_ == NULL && ptr_->prev_ == NULL && ptr_->num_elements == 1)
		{
			return temp;
		}
		temp++;
		return temp;
	}
	//Helper method that returns a copy of an iterator of the previous adjacent element to the current iterators value
	list_iterator<T> prev()
	{
		list_iterator<T> temp(*this);
		temp--;
		return temp;
	}
	// REPRESENTATION
	Node<T>* ptr_; //pointer to node
	unsigned int offset; //offset value (index of node)

};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
template <class T>
class UnrolledLL {
public:
	// default constructor, copy constructor, assignment operator, & destructor
	UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
	UnrolledLL(const UnrolledLL<T>& old) 
	{ 
		copy_list(old); 
	}
	UnrolledLL& operator= (const UnrolledLL<T>& old); 
	//DESTRUCTOR
	~UnrolledLL() 
	{ 
		destroy_list();
	}

	typedef list_iterator<T> iterator;

	// simple accessors & modifiers
	unsigned int size() const 
	{ 
		return size_; 
	}
	bool empty() const 
	{ 
		return head_ == NULL; 
	}
	void clear() 
	{ 
		destroy_list(); 
	}

	// read/write access to contents
	const T& front() const 
	{ 
		return head_->values_[0];
	}
	T& front() 
	{ 
		return head_->values_[0];
	}
	const T& back() const 
	{ 
		return tail_->values_[tail_->num_elements - 1];
	}
	T& back() 
	{ 
		return tail_->values_[tail_->num_elements - 1];
	}

	// modify the linked list structure
	void push_front(const T& v);
	void pop_front();
	void push_back(const T& v);
	void pop_back();
	void print(ostream& COUT);
	iterator erase(iterator itr);
	iterator insert(iterator itr, const T& v);

	iterator begin() 
	{ 
		return iterator(head_,0); 
	}
	iterator end() 
	{ 
		return iterator(NULL,0);
	}

private:
	// private helper functions
	void copy_list(const UnrolledLL<T>& old);
	void destroy_list();

	//REPRESENTATION
	Node<T>* head_; //pointer to head of list
	Node<T>* tail_; //pointer to tail of list
	unsigned int size_; //overall size of list
};

template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) 
{
	// check for self-assignment
	if (&old != this) {
		destroy_list();
		copy_list(old);
	}
	return *this;
}

//Insert element at very front of list
template <class T>
void UnrolledLL<T>::push_front(const T& v) 
{
	if (size_ == 0)
	{
		push_back(v);
	}
	else
	{
		insert(iterator(head_, 0), v);
	}
}

//Erase element at very front of list
template <class T>
void UnrolledLL<T>::pop_front() 
{
	if (size_ != 0)
	{
		erase(iterator(head_,0));
	}

}

//Insert element at very back of list
template <class T>
void UnrolledLL<T>::push_back(const T& v) { 
	Node<T>* newp = new Node<T>(v);
	// special case: initially empty list
	if (!tail_) {
		head_ = tail_ = newp;
	}
	else {
		// normal case: elements in last node are not filled up
		if (tail_->num_elements != NUM_ELEMENTS_PER_NODE)
		{
			tail_->values_[tail_->num_elements] = v;
			tail_->num_elements++;

			//Delete allocation
			delete[] newp->values_;
			delete newp;
		}
		else
		{
			//Insert node with element at end
			newp->prev_ = tail_;
			tail_->next_ = newp;
			tail_ = newp;
		}
	}
	++size_;
}

//Erase last element
template <class T>
void UnrolledLL<T>::pop_back()
{
	erase(iterator(tail_, tail_->num_elements - 1));
}

//Helper method to print out Unrolled List
template <class T>
void UnrolledLL<T>::print(ostream& COUT)
{
	iterator itr(head_, 0);
	COUT << "UnrolledLL, size: " << size_ << endl;
	bool lastNode = false;
	if (size_ != 0)
	{
		while (!lastNode)
		{
			if (itr.ptr_->next_ == NULL)
			{
				lastNode = true;
			}
			COUT << " node:[" << itr.ptr_->num_elements << "]";
			int nodNumElements = (int)itr.ptr_->num_elements;
			for (int i = 0; i < nodNumElements; i++)
			{
				COUT << " " << itr.ptr_->values_[i];
				if (!lastNode)
				{
					itr++;
				}
			}

			COUT << endl;

		}
	}
	
}
//Comparison
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
	if (left.size() != right.size()) return false;
	typename UnrolledLL<T>::iterator left_itr = left.begin();
	typename UnrolledLL<T>::iterator right_itr = right.begin();
	// walk over both lists, looking for a mismatched value
	while (left_itr != left.end()) {
		if (*left_itr != *right_itr) return false;
		left_itr++; right_itr++;
	}
	return true;
}

//Comparison
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right) { return !(left == right); }

//Method to erase element that the iterator is currently pointing to and return an iterator pointing to the next available element
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
	assert(size_ > 0);
	--size_;
	//Iterator of next available element
	iterator result(itr.next());
	// One node left in the list.
	if (itr.ptr_ == head_ && head_ == tail_) 
	{
		//Only one element remaining in node
		if (itr.ptr_->num_elements == 1)
		{
			delete[] itr.ptr_->values_;
			
			delete itr.ptr_;
			head_ = tail_ = 0;
			
			return result;
		}
		else
		{
			//Loop the elements that need to shift over after deletion of element in node
			for (int i = 0; i < (int)(itr.ptr_->num_elements - (itr.offset + 1)); i++)
			{
				itr.ptr_->values_[itr.offset + i] = itr.ptr_->values_[itr.offset + i + 1];
			}
			itr.ptr_->num_elements--;
			//Deleting last elemeent in node (don't need to shift anything)
			if (itr.offset == itr.ptr_->num_elements)
			{
				return iterator(head_, itr.offset-1);
			}
			else
			{
				return itr;
			}
		}
		
	}
	// Removing the head in a list with at least two nodes
	else if (itr.ptr_ == head_)
	{
		//Only one element remaining in node
		if (itr.ptr_->num_elements == 1)
		{
			delete[] itr.ptr_->values_;
			head_ = head_->next_;
			head_->prev_ = 0;
			delete itr.ptr_;
		}
		else
		{
			//Loop the elements that need to shift over after deletion of element in node
			for (int i = 0; i < (int)(itr.ptr_->num_elements - (itr.offset + 1)); i++)
			{
				itr.ptr_->values_[itr.offset + i] = itr.ptr_->values_[itr.offset + i + 1];
			}
			itr.ptr_->num_elements--;
			//Deleting last elemeent in node (don't need to shift anything)
			if (itr.offset == itr.ptr_->num_elements)
			{
				return result;
			}
			else
			{
				return itr;
			}
		}
	}
	// Removing the tail in a list with at least two nodes
	else if (itr.ptr_ == tail_)
	{
		//Only one element remaining in node
		if (itr.ptr_->num_elements == 1)
		{
			delete[] itr.ptr_->values_;
			tail_ = tail_ ->prev_;
			tail_->next_ = 0;
			delete itr.ptr_;
			return iterator(tail_, tail_->num_elements-1);
		}
		else
		{
			//Loop the elements that need to shift over after deletion of element in node
			for (int i = 0; i < (int)(itr.ptr_->num_elements - (itr.offset + 1));i++)
			{
				itr.ptr_->values_[itr.offset + i] = itr.ptr_->values_[itr.offset + i + 1];
			}
			itr.ptr_->num_elements--;

			//Deleting last elemeent in node (don't need to shift anything)
			if (itr.offset == itr.ptr_->num_elements)
			{
				return iterator(tail_, tail_->num_elements - 1);;
			}
			else
			{
				return itr;
			}
		}
	}
	// Need to remove entire Node
	else if (itr.ptr_->num_elements == 1)
	{
		delete[] itr.ptr_->values_;
		itr.ptr_->prev_->next_ = itr.ptr_->next_;
		itr.ptr_->next_->prev_ = itr.ptr_->prev_;
		delete itr.ptr_;
		return result;
	}
	//More than two nodes and node has more than 1 element
	else
	{
	//Loop the elements that need to shift over after deletion of element in node
		for (int i = 0; i < (int)(itr.ptr_->num_elements - (itr.offset + 1));i++)
		{
			itr.ptr_->values_[itr.offset + i] = itr.ptr_->values_[itr.offset + i + 1];
		}
		itr.ptr_->num_elements--;
		//Deleting last elemeent in node (don't need to shift anything)
		if (itr.offset == itr.ptr_->num_elements)
		{
			return result;
		}
		else
		{
			return itr;
		}
	}
	
	return result;
}


//Method to insert given value right before what the given iterator is pointing to. Returns iterator pointing at new element
//Insert value at current spot and keep shifting values to the right until an open spot or reached the end of list
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) 
{
	//Special case if list is empty
	if (size_ == 0)
	{
		push_back(v);
		return itr;
	}
	++size_;
	T curr;
	T tmp = v;
	bool thru = false;
	iterator inIndex(itr.ptr_,itr.offset);

	//Check if need to insert before very first element and that node is full
	if (itr.ptr_->num_elements == NUM_ELEMENTS_PER_NODE && itr.ptr_ == head_ && itr.offset == 0)
	{
		Node<T>* newNode = new Node<T>(v);
		head_->prev_ = newNode;
		newNode->next_ = head_;
		head_ = newNode;
		inIndex.ptr_ = head_;
		inIndex.offset = 0;
	}
	else
	{
		//Loop until there is an open spot in the element allocation
		while (!(itr.offset == (itr.ptr_->num_elements) - 1 && itr.offset != NUM_ELEMENTS_PER_NODE-1))
		{
			thru = true;
			//Continuously shift elements to the right
			curr = itr.ptr_->values_[itr.offset];
			itr.ptr_->values_[itr.offset] = tmp;
			tmp = curr;
			//Reached the end of the list without finiding an opening
			if (itr.ptr_->next_ == NULL && itr.offset == NUM_ELEMENTS_PER_NODE - 1)
			{
				break;
			}
			itr++;

			
		}
		//If list didn't go through the loop (insert at end of node)
		if (!thru)
		{
			//Need to insert at very end
			if (itr.ptr_->next_ == NULL && itr.offset == NUM_ELEMENTS_PER_NODE - 1)
			{
				size_--;
				push_back(tmp);
			}
			else
			{
				curr = itr.ptr_->values_[itr.offset];
				itr.ptr_->values_[itr.offset] = tmp;
				itr.ptr_->values_[itr.ptr_->num_elements] = curr;
				itr.ptr_->num_elements++;
			}
		}
		else
		{
			//If no more space left pushback the last remaining term
			if (itr.ptr_->next_ == NULL && itr.offset == NUM_ELEMENTS_PER_NODE - 1)
			{
				size_--;
				push_back(tmp);
			}
			else
			{
				//Shift last two elements over
				curr = itr.ptr_->values_[itr.offset];
				itr.ptr_->values_[itr.offset] = tmp;
				tmp = curr;

				itr.ptr_->values_[itr.ptr_->num_elements] = tmp;
				itr.ptr_->num_elements++;
			}
		}
		
	}
	return inIndex;
}

//Helper method to used by copy constructor to copy one list to another
template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>&old)  
{
	size_ = old.size_;
	// Handle the special case of an empty list.
	if (size_ == 0)
	{
		head_ = tail_ = 0;
		return;
	}
	head_ = new Node<T>(old.head_->values_,old.head_->num_elements);
	tail_ = head_;
    
	Node<T>* old_p = old.head_->next_;
	while (old_p)
	{
		tail_->next_ = new Node<T>(old_p->values_,old_p->num_elements);
		tail_->next_->prev_ = tail_;
		tail_ = tail_->next_;
		old_p = old_p->next_;
	}
}

//Destroy list
template <class T>
void UnrolledLL<T>::destroy_list() 
{
	Node<T>* temp;
	if (size_ != 0)
	{
		//Loop until empty list
		while (head_ != NULL)
		{
			temp = head_;
			head_ = head_->next_;
			delete[] temp->values_;
			delete temp;
		}
	}
	
	head_ = tail_ = 0;
	size_ = 0;
}
