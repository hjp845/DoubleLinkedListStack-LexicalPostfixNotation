#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

template<class E>
class Node {	// stack 구조 안에 들어가는 클래스
public:
	E data;		// 각 Node는 data 값을 가진다.
	Node* next;		// 다음 Node를 가리키는  포인터
	Node* prev;		// 이전 Node를 가리키는 포인터
	Node() {	// 기본 생성자
		next = NULL;	// 기본 생성자의 next 포인터 값은 NULL
		prev = NULL;	// 기본 생성자의 prev 포인터 값은 NULL
		data = '0';		// 기본 생성자의 data 값은 '0'
	}
	Node(E e, Node* ptr) { // 포인터ptr이 가리키는 Node 뒤에 새로운 Node를 추가
		data = e;	// 역시 data 값을 가지며
		prev = ptr;		// 새로운 Node의 앞 Node의 주소는 ptr 이며
		next = ptr->next;	// 새로운 Node의 뒤 Node의 주소는, 본디 앞주소가 가리키던 다음 주소이다. 
		prev->next = this;	// 앞 Node의 next 주소를 새로운 Node의 주소로 변경
		next->prev = this;	// 뒷 Node의 prev 주소를 새로운 Node의 주소로 변경
	}
	void selvDelete() {		// Node 스스로 사라지게 하는 멤버 함수
		prev->next = next;	// 앞 Node의 next 주소를 현재 Node 다음 주소로 변경
		next->prev = prev;	// 뒷 Node의 prev 주소를 현재 Node 이전 주소로 변경
		delete this;	// 스스로를 삭제한다.
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
class Stack {	// 스택 구조 클래스
public:
	Node<E>* head;	
	Node<E>* tail;	// 기본적으로 head와 tail 노드를 생성해준다.
	Stack() {	// 기본 생성자
		head = new Node<E>();
		tail = new Node<E>();	// head와 tail 노드는 빈껍데기와 비슷하다. 스택 구조 구현을 편리하게 하기 위함이다.
		head->next = tail;
		tail->prev = head;	// head와 tail을 서로 연결해준다.
	}
	~Stack() {	// 소멸자
		while (head->next != tail) {	// head 와 tail만 남을 때까지 모든 Node를 삭제한다.
			head->next->selvDelete();
		}
		delete tail;	
		delete head;	// 그 후 모든 Node를 삭제한다.
	}
	size_t size() const {	// 스택에 들어있는 Node수를 return 한다.
		size_t count = 0; 
		Node<E>* temp = tail;
		while (temp->prev != head) {	// head 에서 출발하여 head와 tail 노드를 제외한 노드의 수를 센다.
			count++;
			temp = temp->prev;
		}
		return count;
	}
	bool empty() const {	// 스택이 비어 있으면 true, 스택이 비어 있지않으면 false 값을 반환한다.
		if (tail->prev == head) {
			return true;
		}
		else {
			return false;
		}
	}
	const E& top() const throw(StackEmpty) {	// 스택의 젤 마지막 노드 참조 값을 return 한다.
		try {
			if (head->next == tail) {
				throw StackEmpty("ERROR");
			}
			return tail->prev->data;
		}
		catch (StackEmpty& h) {
			cout << h.what() << endl;	// 만약 스택이 비어 있다면 ERROR를 출력한다.
		}
	}
	void push(const E& e) {		// 파라미터 값을 data로 갖는 Node를 제일 맨뒤에 생성한다.
		new Node<E>(e, tail->prev);		// tail 앞 노드의 뒤에 새로운 Node 생성
	}
	void pop() throw(StackEmpty) {	// 제일 마지막 Node를 제거한다.
		try {
			if (head->next == tail) {
				throw StackEmpty("ERROR");
			}
			tail->prev->selvDelete();	// 스스로 사라지게 한다.
			return;
		}
		catch (StackEmpty& h) {
			cout << h.what() << endl;	// 만약 스택이 비어 있다면 ERROR를 출력한다.
		}

	}
};

void doit() {	// 입출력을 받고 그에 맞게 함수들을 실행하는 함수이다.
	Stack<string>* stack = new Stack<string>();		// 스택을 생성해준다.
	string input;
	while (input != "QUIT") {	// 밑에 제어문들은 쉽게 이해할 수 있다.
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
			cout << "INPUT ERROR" << endl;	// 그 외 입력이 들어오면 INPUT ERROR를 출력한다.
		}
	}
}

int main() {
	doit();
}