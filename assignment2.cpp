#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
class Node
{
typedef Node* NodePtr;
private:
	int data;
	NodePtr link;
public:
	Node();
	Node(const int &);
	Node(const Node &);
	int getData() const;
	NodePtr getLink() const;
	void setData(const int &);
	void setLink(const NodePtr &);
	friend ostream& operator << (ostream &, const Node &);
};
typedef Node* NodePtr;
Node::Node() : data(0), link(nullptr) {}
Node::Node(const int &d) : data(d), link(nullptr){}
Node::Node(const Node &n) : data(n.data), link(n.link){}
int Node::getData() const { return data; }
NodePtr Node::getLink() const { return link; }
void Node::setData(const int &d) { data = d; }
void Node::setLink(const NodePtr &p) { link = p; }
ostream& operator << (ostream& out, const Node& n)
{
	out << n.data;
	return out;
}
typedef Node* NodePtr;
class LinkedList
{
private:
	NodePtr head;
public:
	LinkedList(); //default constructor: assigns the head pointer member variable a nullptr value
	LinkedList(const LinkedList &); //copy constructor (deep copy)
	~LinkedList(); //destructor (must delete all the nodes from the heap)
	LinkedList& operator= (const LinkedList &); //Assignment operator (deep copy)
	bool isEmpty() const; //return true if the length of the calling object is 0 and false otherwise
	NodePtr getHeadPtr() const; //return the head member variable of the calling object
	int getLength() const; //return the number of nodes in the calling object
	void head_insert(const int &); //as described in the supplementary material
	NodePtr search_node(const int &) const; //as described in the supplementary material
	void insert_after(const NodePtr &, const int &) const; //as described in the supplementary material
	void remove_node(const NodePtr &); //as described in the supplementary material
	void remove_node(const int &); //as described in the supplementary material
	void remove_all(const int &); //as described in the supplementary material
	void tail_insert(const int &); //as described in the supplementary material
	void insert_before(const NodePtr &, const int &); //as described in the supplementary material
	friend ostream& operator << (ostream&, const LinkedList &); //Implemented for you
};
LinkedList::LinkedList()
{
	head = nullptr;
}
LinkedList::LinkedList(const LinkedList &LL)
{
	head = nullptr;
	NodePtr temp;
	temp = LL.head;
	while (temp != NULL)
	{
		this->tail_insert(temp->getData());
		temp = temp->getLink();
	}
}
LinkedList::~LinkedList()
{
	NodePtr temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->getLink();
		delete temp;
	}
}
LinkedList& LinkedList::operator= (const LinkedList &LL)
{
	if (this == &LL)
		return *this;
	else
	{
		this->~LinkedList();
		head = nullptr;
		NodePtr temp;
		temp = LL.head;
		while (temp != NULL)
		{
			this->tail_insert(temp->getData());
			temp = temp->getLink();
		}
		return *this;
	}
}
int LinkedList::getLength() const
{
	int count = 0;
	if (head == nullptr)
		return count;
	else
	{
		NodePtr temp;
		temp = head;
		while (temp != nullptr)
		{
			count++;
			temp = temp->getLink();
		}
	}
	return count;
}
bool LinkedList::isEmpty() const
{
	if (this->getLength() == 0)
		return true;
	return false;
}
NodePtr LinkedList::getHeadPtr() const
{
	return head;
}
void LinkedList::head_insert(const int &value)
{
	NodePtr n = new Node(value);
	n->setLink(head);
	head = n;
}
NodePtr LinkedList::search_node(const int &value) const
{
	NodePtr temp = head;
	while(temp != nullptr)
	{
		if (temp->getData() == value)
			return temp;
		else
			temp = temp->getLink();
	}
	return nullptr;
}
void LinkedList::insert_after(const NodePtr &n, const int &value) const
{
	if (n == nullptr)
		return;
	else
	{
		NodePtr temp = new Node(value);
		temp->setLink(n->getLink());
		n->setLink(temp);
	}
}
void LinkedList::remove_node(const NodePtr &n)
{
	if (head == nullptr || n == nullptr)
		return;
	else if (head == n)
	{
		head = head->getLink();
		delete n;
		return;
	}
	else
	{
		NodePtr b = head;
		while (b != nullptr) 
		{
			if (b->getLink() == n) 
			{
				b->setLink(n->getLink());
				delete n;
				return;
			}
		b = b->getLink();
		}
	}
}
void LinkedList::remove_node(const int &value)
{
	NodePtr n = this->search_node(value);
	this->remove_node(n);
}
void LinkedList::remove_all(const int &value)
{
	NodePtr n;
	do
	{
		n = this->search_node(value);
		this->remove_node(n);
	}while (n != nullptr);
}
void LinkedList::tail_insert(const int &value)
{
	if (head == nullptr)
		this->head_insert(value);
	else
	{
		NodePtr b = head; 
		while(b->getLink() != nullptr)
			b = b->getLink();
		insert_after(b, value);
	}
}
void LinkedList::insert_before(const NodePtr &n, const int &value)
{
	
	if (head == nullptr)
	{
		if (n == nullptr)
			this->head_insert(value);
		else
			cout << "Insertion failed. Bad node argument." << endl;
		return;
	}
	
	if (n == nullptr)
	{
		this->tail_insert(value);
		return;
	}

	if (head == n)
	{
		this->head_insert(value);
		return;
	}

	NodePtr b = head;
	while (b != nullptr)
	{
		if (b->getLink() == n)
		break;
		b = b->getLink();
	}
	if (b == nullptr)
		cout << "Insertion failed. Bad node argument." << endl;
	else
		insert_after(b, value);
}
ostream& operator << (ostream &out, const LinkedList &LL)
{
	if (LL.isEmpty())
		out << "EMPTY LINKED LIST";
	else
	{
		NodePtr temp = LL.head;
		while(temp != nullptr)
		{
			out << *temp << " ";
			temp = temp->getLink();
		}
	}
	return out;
}
LinkedList computeUnsignedBinary(const int &num, const int &bit_pattern_size)
{
	assert(num>=0);
	LinkedList LL;
	int newNum = num;
	
	while (newNum > 0 && LL.getLength() < bit_pattern_size)
	{
		if (newNum % 2 == 0)
			LL.head_insert(0);	
		else
			LL.head_insert(1);
		newNum = newNum/2;
	}
	while (LL.getLength() < bit_pattern_size)
		LL.head_insert(0);
	
	return LL;
}
LinkedList computeSignAndMagnitudeBinary (const int &num, const int &bit_pattern_size)
{
	LinkedList LL;
	int newNum;

	if (num < 0)
		newNum = num*(-1);
	else
		newNum = num;
	
	while (newNum > 0 && LL.getLength() < bit_pattern_size-1)
	{
		if (newNum % 2 == 0)
			LL.head_insert(0);	
		else
			LL.head_insert(1);
		newNum = newNum/2;
	}
	while (LL.getLength() < bit_pattern_size-1)
		LL.head_insert(0);
		
	if (num >= 0)
		LL.head_insert(0);
	else 
		LL.head_insert(1);

	return LL;
}
void flipBits(LinkedList &LL)
{
	NodePtr temp;
	temp = LL.getHeadPtr();
	while (temp != nullptr)
	{
		if (temp->getData() == 0)
			temp->setData(1);
		else if (temp->getData() == 1)
			temp->setData(0);
		temp = temp->getLink();
	}
	delete temp;
}
void reverse (LinkedList &LL)
{
	NodePtr temp;
	temp = LL.getHeadPtr();

	LinkedList LL1;
	while (temp != NULL)
	{
		LL1.head_insert(temp->getData());
		temp = temp->getLink();
	}

	LL.~LinkedList();
	LL = LL1;
}
LinkedList operator+(const LinkedList &LL1, const LinkedList &LL2)
{
	assert(LL1.getLength() == LL2.getLength());
	LinkedList newLL1 = LL1; LinkedList newLL2 = LL2; LinkedList newLL;

	reverse(newLL1); reverse(newLL2);

	NodePtr temp1 = newLL1.getHeadPtr(); NodePtr temp2 = newLL2.getHeadPtr();
	int carry = 0, sum = 0;

	while (temp1 != nullptr || temp2 != nullptr)
	{
		int b1 = temp1->getData(), b2 = temp2->getData();
		sum = carry;
		sum += (b1+b2);
		carry = 0;

		if (sum > 1)
		{
			if (sum % 2 == 0)
				newLL.head_insert(0);
			else
				newLL.head_insert(1);
			carry = 1;
		}
		
		else 
			newLL.head_insert(sum);

		temp1 = temp1->getLink(); temp2 = temp2->getLink();
	}
	return newLL;
}
void addOne (LinkedList &LL)
{
	assert(!LL.isEmpty());
	reverse(LL);
	int carry = 0;
	NodePtr temp;
	temp = LL.getHeadPtr();
	if (LL.getLength() == 1)
	{
		if (temp->getData() == 0)
			temp->setData(1);
		else
			temp->setData(0);
	}
	else
	{
		if (temp->getData() == 0)
			temp->setData(1);
		else
		{
			while (temp->getData() == 1)
			{
				temp->setData(0);
				carry = 1;
				temp = temp->getLink();
			}
			temp->setData(1);	
		}
	}
	reverse(LL);
}
LinkedList computeTwosComplementBinary(const int &num, const int &bit_pattern_size)
{
	LinkedList LL;
	if (num > 0)
		LL = computeUnsignedBinary(num, bit_pattern_size);
	else
	{
		LL = computeUnsignedBinary((num*(-1)), bit_pattern_size);
		flipBits(LL);
		addOne(LL);
	}
	return LL;
}
int twosComplementBinaryToDecimal(const LinkedList &LL)
{
	assert(!LL.isEmpty());
	LinkedList newLL = LL;
	int sum = 0, multiply = 1;
	NodePtr temp = newLL.getHeadPtr();

	if (temp->getData() == 0)
	{
		reverse(newLL);
		temp = newLL.getHeadPtr();
		if (temp->getData() == 1)
			sum += 1;
		temp = temp->getLink();

		for (int i = 1; temp!=NULL; i++, temp = temp->getLink())
		{
			if (temp->getData() == 1)
			{
				for (int j = 0; j < i; j++)
				{
					multiply *= 2;
				}
				sum += multiply;	
				multiply = 1;
			}
		}
	}

	else
	{
		flipBits(newLL);
		addOne(newLL);
		reverse(newLL);
		temp = newLL.getHeadPtr();
		if (temp->getData() == 1)
			sum += 1;
		temp = temp->getLink();
		for (int i = 1; temp!=NULL; i++, temp = temp->getLink())
		{
			if (temp->getData() == 1)
			{
				for (int j = 0; j < i; j++)
				{
					multiply *= 2;
				}
				sum += multiply;	
				multiply = 1;
			}
		}	
		sum *= -1;
	}
	return sum;
}
int selectComputation()
{
	cout << "Select your computation" << endl;
	cout << " 1. Unsigned Binary Representation Computation" << endl;
	cout << " 2. Sign and Magnitude Representation Computation" << endl;
	cout << " 3. Two's Complement Representation Computation" << endl;
	cout << " 4. Exit Program" << endl;
	int selection;
	cout << "Enter your selection (1, 2, 3, or 4): ";
	cin >> selection;
	while (selection != 1 && selection != 2 && selection != 3 && selection != 4)
	{
		cout << "Please enter a correct choice: ";
		cin >> selection;
	}
	return selection;
}
int main()
{
	cout << "This program demonstrates the Linked List Data Structure in C++" << endl;
	cout << "Linked Lists will be used for numeric information representation using" << endl;
	cout << " *** Unsigned Binary Representation" << endl;
	cout << " *** Sign and Magnitude Binary Representation" << endl;
	cout << " *** Two's Complement Binary Representation" << endl << endl;
	cout << "In addition, the program demonstrates" << endl;
	cout << " *** Two's complement binary addition, and" << endl;
	cout << " *** Conversion from two's complement to decimal." << endl << endl;
	do
	{
		int selection = selectComputation();
		if (selection == 1)
		{
			int bit_pattern_size, num;
			cout << endl << "Enter a positive integer for the bit pattern size: ";
			cin >> bit_pattern_size;
			while (bit_pattern_size <= 0)
			{
				cout << "You must enter a positive integer. Enter again please: ";
				cin >> bit_pattern_size;
			}
			cout << "Enter a non-negative integer: ";
			cin >> num;
			while (num < 0)
			{
				cout << "You must enter a non-negative integer. Enter again please: ";
				cin >> num;
			}
			LinkedList LL = computeUnsignedBinary(num, bit_pattern_size);
			cout << "The unsigned binary representation of " << num << " in " << bit_pattern_size << " bit is " << LL << endl;
			cout << endl;
		}
		else if (selection == 2)
		{
			int bit_pattern_size, num;
			cout << endl << "Enter a positive integer for the bit pattern size: ";
			cin >> bit_pattern_size;
			while (bit_pattern_size <= 0)
			{
				cout << "You must enter a positive integer. Enter again please: ";
				cin >> bit_pattern_size;
			}
			cout << "Enter an integer: ";
			cin >> num;
			LinkedList LL = computeSignAndMagnitudeBinary(num, bit_pattern_size);
			cout << "The sign and magnitude binary representation of " << num << " in " << bit_pattern_size << " bit is " << LL << endl;
			cout << endl;
		}
		else if (selection == 3)
		{
			int bit_pattern_size, num1, num2;
			cout << endl << "Enter a positive integer for the bit pattern size: ";
			cin >> bit_pattern_size;
			while (bit_pattern_size <= 0)
			{
				cout << "You must enter a positive integer. Enter again please: ";
				cin >> bit_pattern_size;
			}
			cout << "Enter an integer: ";
			cin >> num1;
			LinkedList LL1 = computeTwosComplementBinary(num1, bit_pattern_size);
			cout << "The two's complement binary representation of " << num1 << " in " << bit_pattern_size << " bit is " << LL1 << endl;
			cout << endl;
			cout << "Enter a second integer: ";
			cin >> num2;
			LinkedList LL2 = computeTwosComplementBinary(num2, bit_pattern_size);
			cout << "The two's complement binary representation of " << num2 << " in " << bit_pattern_size << " bit is " << LL2 << endl;
			cout << endl;
			LinkedList LL3 = LL1 + LL2;
			cout << "The binary sum of " << LL1 << " and " << LL2 << " is " << LL3 << endl;
			int sum = twosComplementBinaryToDecimal(LL3);
			cout << "The integer value of the binary sum is " << sum << endl;
			if (sum == num1 + num2)
				cout << "This is a correct result." << endl;
			else
				cout << "This is not correct result because our bit pattern is too small to store the result." << endl;
		}
		else
			break;
		system("Pause");
		cout << endl << endl;
	}while (true);

	system("Pause");
	return 0;
}