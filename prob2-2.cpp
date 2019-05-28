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
	//ptr 뒤에 추가
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
		size_t count = 0; // 함수 안에서 변수 선언 가능한가? const
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

void doit() {	// prob2-1에 입력값을 받는 방법에 대해 설명되어 있다.
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
			/*후위표기법->값출력
			이번에는 숫자들을 바로 출력하지 않고 스택에 담는다.
			연산자가 들어오면 바로 스택에 제일 위 두 원소에 대해 연산을 수행한다.
			그 연산한 값은 다시 스택에 담는다.*/
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
			/* 5/2 = 2 가 -5/2 = -3 이 나오도록 해야한다.
			앞 피연산자와 뒷 피연산자의 부호가 동일하다면 / 연산만 수행하였고,
			앞 피연산자와 뒷 피연산자의 부호가 다르다면 / 연산을 한 후, - 1을 해주었다.*/
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
			else {	// 연산자가 아닌 숫자는 그대로 스택에 넣어준다.
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