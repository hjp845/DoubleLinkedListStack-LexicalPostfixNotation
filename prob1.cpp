#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

template<class E>
class Node {	// stack ���� �ȿ� ���� Ŭ����
public:
	E data;		// �� Node�� data ���� ������.
	Node* next;		// ���� Node�� ����Ű��  ������
	Node* prev;		// ���� Node�� ����Ű�� ������
	Node() {	// �⺻ ������
		next = NULL;	// �⺻ �������� next ������ ���� NULL
		prev = NULL;	// �⺻ �������� prev ������ ���� NULL
		data = '0';		// �⺻ �������� data ���� '0'
	}
	Node(E e, Node* ptr) { // ������ptr�� ����Ű�� Node �ڿ� ���ο� Node�� �߰�
		data = e;	// ���� data ���� ������
		prev = ptr;		// ���ο� Node�� �� Node�� �ּҴ� ptr �̸�
		next = ptr->next;	// ���ο� Node�� �� Node�� �ּҴ�, ���� ���ּҰ� ����Ű�� ���� �ּ��̴�. 
		prev->next = this;	// �� Node�� next �ּҸ� ���ο� Node�� �ּҷ� ����
		next->prev = this;	// �� Node�� prev �ּҸ� ���ο� Node�� �ּҷ� ����
	}
	void selvDelete() {		// Node ������ ������� �ϴ� ��� �Լ�
		prev->next = next;	// �� Node�� next �ּҸ� ���� Node ���� �ּҷ� ����
		next->prev = prev;	// �� Node�� prev �ּҸ� ���� Node ���� �ּҷ� ����
		delete this;	// �����θ� �����Ѵ�.
	}
};

class StackEmpty : public std::runtime_error {
public:
	explicit StackEmpty(const std::string& msg) : runtime_error(msg) {
		string what = msg;
	}
	explicit StackEmpty(const char* msg) : runtime_error(msg) {
		
	}
};

template<class E>
class Stack {	// ���� ���� Ŭ����
public:
	Node<E>* head;	
	Node<E>* tail;	// �⺻������ head�� tail ��带 �������ش�.
	Stack() {	// �⺻ ������
		head = new Node<E>();
		tail = new Node<E>();	// head�� tail ���� �󲮵���� ����ϴ�. ���� ���� ������ ���ϰ� �ϱ� �����̴�.
		head->next = tail;
		tail->prev = head;	// head�� tail�� ���� �������ش�.
	}
	~Stack() {	// �Ҹ���
		while (head->next != tail) {	// head �� tail�� ���� ������ ��� Node�� �����Ѵ�.
			head->next->selvDelete();
		}
		delete tail;	
		delete head;	// �� �� ��� Node�� �����Ѵ�.
	}
	size_t size() const {	// ���ÿ� ����ִ� Node���� return �Ѵ�.
		size_t count = 0; 
		Node<E>* temp = tail;
		while (temp->prev != head) {	// head ���� ����Ͽ� head�� tail ��带 ������ ����� ���� ����.
			count++;
			temp = temp->prev;
		}
		return count;
	}
	bool empty() const {	// ������ ��� ������ true, ������ ��� ���������� false ���� ��ȯ�Ѵ�.
		if (tail->prev == head) {
			return true;
		}
		else {
			return false;
		}
	}
	const E& top() const throw(StackEmpty) {	// ������ �� ������ ��� ���� ���� return �Ѵ�.
		try {
			if (head->next == tail) {
				throw StackEmpty("ERROR");
			}
			return tail->prev->data;
		}
		catch (StackEmpty& h) {
			cout << h.what() << endl;	// ���� ������ ��� �ִٸ� ERROR�� ����Ѵ�.
		}
	}
	void push(const E& e) {		// �Ķ���� ���� data�� ���� Node�� ���� �ǵڿ� �����Ѵ�.
		new Node<E>(e, tail->prev);		// tail �� ����� �ڿ� ���ο� Node ����
	}
	void pop() throw(StackEmpty) {	// ���� ������ Node�� �����Ѵ�.
		try {
			if (head->next == tail) {
				throw StackEmpty("ERROR");
			}
			tail->prev->selvDelete();	// ������ ������� �Ѵ�.
			return;
		}
		catch (StackEmpty& h) {
			cout << h.what() << endl;	// ���� ������ ��� �ִٸ� ERROR�� ����Ѵ�.
		}

	}
};

void doit() {	// ������� �ް� �׿� �°� �Լ����� �����ϴ� �Լ��̴�.
	Stack<string>* stack = new Stack<string>();		// ������ �������ش�.
	string input;
	while (input != "QUIT") {	// �ؿ� ������� ���� ������ �� �ִ�.
		getline(cin, input);

		if (input.substr(0, 4) == "PUSH") {
			stack->push(input.substr(5));
		}

		else if (input.substr(0, 3) == "POP") {
			stack->pop();
		}

		else if (input.substr(0, 4) == "SIZE") {
			cout << stack->size() << endl;
		}

		else if (input.substr(0, 5) == "EMPTY") {
			if (stack->empty()) {
				cout << "TRUE" << endl;
			}
			else {
				cout << "FALSE" << endl;
			}
		}

		else if (input.substr(0, 3) == "TOP") {
			if (stack->empty()) {
				cout << "ERROR" << endl;
				continue;
			}
			cout << stack->top() << endl;
		}

		else if (input.substr(0, 4) == "QUIT") {
			break;
		}

		else {
			cout << "INPUT ERROR" << endl;	// �� �� �Է��� ������ INPUT ERROR�� ����Ѵ�.
		}
	}
}

int main() {
	doit();
}