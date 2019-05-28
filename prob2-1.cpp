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
	Node(E e, Node* ptr) { //ptr �ڿ� �߰�
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

void doit() {
	Stack<string>* stack = new Stack<string>();		// stack ����
	string num_str;
	getline(cin, num_str);	// �켱 getline���� ����̳� �������� �Է¹޴´�.
	int num = stoi(num_str);	// int������ ��ȯ�Ͽ� �־��ش�.
	string* ans = new string[num];	// �� �ٿ� �´� ������ �־��ֱ� ���� �迭�� �����Ѵ�.
	for (int i = 0; i < num; i++) {
		string input_getline;
		getline(cin, input_getline);	// �켱 getline���� ���� �Է� �޴´�.
		stringstream input_ss(input_getline);	// �� ���� stringstream�� �̿��Ͽ� ������ �������� ���� �޴´�.
		string input;
		while (input_ss >> input) {		// ������ �������� ���� input���� ��� �־��ش�. 
			/*���� ������ �������� ������ �Ǵ� ���ڸ� �Է� �޴´�.
			�����ڸ� ���� ��, ������ ��� �ִٸ� �״�� ���ÿ� �־��ְ�,
			������ ��� ���� �ʴٸ� ���ÿ�, ���� ������ �������� �켱�������� ���� �����ڸ� ����������,	�����ڸ� ���ÿ��� ������ ����Ѵ�.
			���� �����ڰ� ��μ� ���� �� ���ÿ� �ִ´�.*/
			/*ans[i] �� ���� �����ϸ�, �� ���� ans[i]�� ���� �ְ�, ���߿� ans[]�� for���� ���� ����Ѵ�.*/
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
			else if (input == "(") {	// �ϴ� ( �����ڰ� ������ stack�� �״´�.
				stack->push("(");
			}
			else if (input == ")") {	// ��μ� ) �����ڰ� ������ ���ÿ��� ���Ҹ� �����µ�, ( �����ڰ� �ȳ��ö����� ���ش�.
				if (!stack->empty()) {
					while (stack->top() != "(") {
						ans[i] += stack->top() + ' ';
						stack->pop();
					}
					stack->pop(); // ���������� ( �� ���ִ� ��
				}
			}
			else {	
			ans[i] += input + ' ';	// �����ڰ� �ƴϸ� �����̹Ƿ� �״�� ����Ѵ�. (���� ������� ans[i]�� �ִ� ���̴�.)
			}
		}		
		while (!stack->empty()) {	// ������ �������� stack�� �����ִ� �����ڸ� ���� ����Ѵ�.
			ans[i] += stack->top() + ' ';
			stack->pop();
		}
	}
	for (int i = 0; i < num; i++) {		// ���� ans[]�� �׾ƿӴ� ����� ������� ����Ѵ�.
		cout << ans[i] << endl;
	}
	
	
}

int main() {
	doit();
}