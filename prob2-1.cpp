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
	Node(E e, Node* ptr) { //ptr 뒤에 추가
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

void doit() {
	Stack<string>* stack = new Stack<string>();		// stack 생성
	string num_str;
	getline(cin, num_str);	// 우선 getline으로 몇번이나 돌릴건지 입력받는다.
	int num = stoi(num_str);	// int형으로 변환하여 넣어준다.
	string* ans = new string[num];	// 각 줄에 맞는 정답을 넣어주기 위해 배열을 생성한다.
	for (int i = 0; i < num; i++) {
		string input_getline;
		getline(cin, input_getline);	// 우선 getline으로 식을 입력 받는다.
		stringstream input_ss(input_getline);	// 그 다음 stringstream을 이용하여 공백을 기준으로 값을 받는다.
		string input;
		while (input_ss >> input) {		// 공백을 기준으로 값을 input으로 계속 넣어준다. 
			/*이제 공백을 기준으로 연산자 또는 숫자를 입력 받는다.
			연산자를 받을 때, 스택이 비어 있다면 그대로 스택에 넣어주고,
			스택이 비어 있지 않다면 스택에, 지금 들어가려는 연산자의 우선순위보다 낮은 연산자만 남을때까지,	연산자를 스택에서 꺼내고 출력한다.
			낮은 연산자가 비로소 남을 때 스택에 넣는다.*/
			/*ans[i] 에 대해 설명하면, 각 줄을 ans[i]에 집어 넣고, 나중에 ans[]를 for문을 돌려 출력한다.*/
			if (input == "+") {		
				if (stack->empty()) {
					stack->push("+");
				}
				else {
					while (stack->top() == "-" || stack->top() == "*" || stack->top() == "/") {
						ans[i] += stack->top() + ' ';
						stack->pop();
						if (stack->empty()) {
							break;
						}
					}
					stack->push("+");
				}
			}
			else if (input == "-") {
				if (stack->empty()) {
					stack->push("-");
				}
				else {
					while (stack->top() == "+" || stack->top() == "*" || stack->top() == "/") {
						ans[i] += stack->top() + ' ';
						stack->pop();
						if (stack->empty()) {
							break;
						}
					}
					stack->push("-");
				}
			}
			else if (input == "*") {
				if (stack->empty()) {
					stack->push("*");
				}
				else {
					while (stack->top() == "/") {
						ans[i] += stack->top() + ' ';
						stack->pop();
						if (stack->empty()) {
							break;
						}
					}
					stack->push("*");
				}
			}
			else if (input == "/") {
				if (stack->empty()) {
					stack->push("/");
				}
				else {
					while (stack->top() == "*") {
						ans[i] += stack->top() + ' ';
						stack->pop();
						if (stack->empty()) {
							break;
						}
					}
					stack->push("/");
				}
			}
			else if (input == "(") {	// 일단 ( 연산자가 들어오면 stack에 쌓는다.
				stack->push("(");
			}
			else if (input == ")") {	// 비로소 ) 연산자가 들어오면 스택에서 원소를 꺼내는데, ( 연산자가 안나올때까지 빼준다.
				if (!stack->empty()) {
					while (stack->top() != "(") {
						ans[i] += stack->top() + ' ';
						stack->pop();
					}
					stack->pop(); // 마지막으로 ( 을 빼주는 것
				}
			}
			else {	
			ans[i] += input + ' ';	// 연산자가 아니면 숫자이므로 그대로 출력한다. (말이 출력이지 ans[i]에 넣는 것이다.)
			}
		}		
		while (!stack->empty()) {	// 스택이 빌때까지 stack에 남아있던 연산자를 빼내 출력한다.
			ans[i] += stack->top() + ' ';
			stack->pop();
		}
	}
	for (int i = 0; i < num; i++) {		// 이제 ans[]에 쌓아왓던 답들을 순서대로 출력한다.
		cout << ans[i] << endl;
	}
	
	
}

int main() {
	doit();
}