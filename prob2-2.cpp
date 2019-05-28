#include<iostream>
#include<string>
#include<stdexcept>
#include<sstream>

using namespace std;

template<class E>
class Node {
public:
	E data;
	Node* next;
	Node* prev;
	Node() {
		next = NULL;
		prev = NULL;
		data = '0';
	}
	//ptr �ڿ� �߰�
	Node(E e, Node* ptr) {
		data = e;
		prev = ptr;
		next = ptr->next;
		prev->next = this;
		next->prev = this;
	}
	void selvDelete() {
		prev->next = next;
		next->prev = prev;
		delete this;
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
class Stack {
public:
	Node<E>* head;
	Node<E>* tail;
	Stack() {
		head = new Node<E>();
		tail = new Node<E>();
		head->next = tail;
		tail->prev = head;
	}
	~Stack() {
		while (head->next != tail) {
			head->next->selvDelete();
		}
		delete tail;
		delete head;
	}
	size_t size() const {
		size_t count = 0; // �Լ� �ȿ��� ���� ���� �����Ѱ�? const
		Node<E>* temp = head;
		while (temp->next != tail) {
			count++;
			temp = temp->next;
		}
		return count;
	}
	bool empty() const {
		if (head->next == tail) {
			return true;
		}
		else {
			return false;
		}
	}
	const E& top() const throw(StackEmpty) {
		try {
			if (head->next == tail) {
				throw StackEmpty("ERROR");
			}
			return tail->prev->data;
		}
		catch (StackEmpty& h) {
			cout << h.what() << endl;
		}
	}
	void push(const E& e) {
		new Node<E>(e, tail->prev);
	}
	void pop() throw(StackEmpty) {
		try {
			if (head->next == tail) {
				throw StackEmpty("ERROR");
			}
			tail->prev->selvDelete();
			return;
		}
		catch (StackEmpty& h) {
			cout << h.what() << endl;
		}

	}
};

void doit() {	// prob2-1�� �Է°��� �޴� ����� ���� ����Ǿ� �ִ�.
	Stack<string>* stack = new Stack<string>();
	string num_str;
	getline(cin, num_str);
	int num = stoi(num_str);
	string* ans = new string[num];
	for (int i = 0; i < num; i++) {
		string input_getline;
		getline(cin, input_getline);
		stringstream input_ss(input_getline);
		string input;
		while (input_ss >> input) {
			/*����ǥ���->�����
			�̹����� ���ڵ��� �ٷ� ������� �ʰ� ���ÿ� ��´�.
			�����ڰ� ������ �ٷ� ���ÿ� ���� �� �� ���ҿ� ���� ������ �����Ѵ�.
			�� ������ ���� �ٽ� ���ÿ� ��´�.*/
			if (input == "+") {		
				string temp = to_string((stoi(stack->tail->prev->prev->data) + stoi(stack->tail->prev->data)));
				stack->pop();
				stack->pop();
				stack->push(temp);
			}
			else if (input == "-") {
				string temp = to_string((stoi(stack->tail->prev->prev->data) - stoi(stack->tail->prev->data)));
				stack->pop();
				stack->pop();
				stack->push(temp);
			}
			else if (input == "*") {
				string temp = to_string((stoi(stack->tail->prev->prev->data) * stoi(stack->tail->prev->data)));
				stack->pop();
				stack->pop();
				stack->push(temp);
			}
			/* 5/2 = 2 �� -5/2 = -3 �� �������� �ؾ��Ѵ�.
			�� �ǿ����ڿ� �� �ǿ������� ��ȣ�� �����ϴٸ� / ���길 �����Ͽ���,
			�� �ǿ����ڿ� �� �ǿ������� ��ȣ�� �ٸ��ٸ� / ������ �� ��, - 1�� ���־���.*/
			else if (input == "/") {	
				int first = stoi(stack->tail->prev->prev->data);
				int seconde = stoi(stack->tail->prev->data);
				if (first * seconde >= 0) {
					string temp = to_string(first / seconde);
					stack->pop();
					stack->pop();
					stack->push(temp);
				}
				else if (first * seconde < 0) {
					string temp = to_string(first / seconde - 1);
					stack->pop();
					stack->pop();
					stack->push(temp);
				}
				
			}
			else {	// �����ڰ� �ƴ� ���ڴ� �״�� ���ÿ� �־��ش�.
			stack->push(input);
			}
		}		
		ans[i] = stack->top();
	}
	for (int i = 0; i < num; i++) {
		cout << ans[i] << endl;
	}
}

int main() {
	doit();
}