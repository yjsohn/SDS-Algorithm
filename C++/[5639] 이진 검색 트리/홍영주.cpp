#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
	int val = NULL;
	Node* left;
	Node* right;

	void add(int num) {
		if (val == NULL) {
			val = num;
			left = nullptr;
			right = nullptr;
		}
		else {
			if (val > num) {
				if (left != nullptr) {
					left->add(num);
				}
				else {
					left = new Node();
					left->add(num);
				}
			}
			else {
				if (right != nullptr) {
					right->add(num);
				}
				else {
					right = new Node();
					right->add(num);
				}
			}
		}
	}

	~Node() {
		delete left;
		delete right;
	}

	void printPostOrder() {
		if (left != nullptr) {
			left->printPostOrder();
		}

		if (right != nullptr) {
			right->printPostOrder();
		}

		if (val != NULL) {
			cout << val << "\n";
		}
	}

};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int val;
	Node n;
	while (cin >>val) {
		if (val == EOF) break;
		
		n.add(val);
	}

	n.printPostOrder();
	return 0;
}