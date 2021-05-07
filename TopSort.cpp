#include <iostream>
struct Node;
Node* front = nullptr;
auto find(int key) -> Node*;

struct ChildNode
{
	ChildNode* childnext;
	Node* next;

	explicit ChildNode(int key)
	{
		next = find(key);
		childnext = nullptr;
	}
};

struct Node
{
	int key;
	int count;
	Node* next;
	ChildNode* child;

	explicit Node(int key)
	{
		this->key = key;
		next = nullptr;
		child = nullptr;
		count = 0;
	}
};

auto find(int key) -> Node*
{
	if (front != nullptr)
	{
		Node* current = front;
		while (current->key != key && current->next != nullptr)
		{
			current = current->next;
		}
		if (current->key == key)
		{
			return current;
		}
	}
	return nullptr;
}

void insert_elem(int key)
{
	if (front != nullptr)
	{
		if (find(key) == nullptr)
		{
			Node* current = front;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = new Node(key);
		}
	}
}

void addChild(Node* current, int key)
{
	if (current != nullptr)
	{
		Node* temp = current;
		if (temp->child == nullptr)
		{
			temp->child = new ChildNode(key);
		}
		else
		{
			while (temp->child->childnext != nullptr)
			{
				temp->child = temp->child->childnext;
			}
			temp->child->childnext = new ChildNode(key);
		}
		find(key)->count += 1;
	}
}

void delChild(Node* current)
{
	if (current != nullptr && current->child != nullptr)
	{
		ChildNode* temp = current->child;
		if (temp->childnext == nullptr)
		{
			temp->next->count -= 1;
			delete[] temp;
			current->child = nullptr;
		}
		else
		{
			while (temp->childnext->childnext != nullptr)
			{
				temp = temp->childnext;
			}
			temp->childnext->next->count -= 1;
			delete[] temp->childnext;
			temp->childnext = nullptr;
		}
	}
}

auto find_min_elem() -> Node*
{
	int min = 0;
	Node* current = front;
	while (current != nullptr && current->count != 0)
	{
		current = current->next;
	}
	if (current == nullptr)
	{
		return nullptr;
	}
	min = current->key;

	min = current->key;
	current = front;
	while (current != nullptr)
	{
		if (current->count == 0)
		{
			if (current->key < min)
			{
				min = current->key;
			}
		}
		current = current->next;
	}
	return find(min);
}

void topSort()
{
	Node* temp = find_min_elem();
	if (temp == nullptr)
	{
		std::cout << "your graph has cicle";
	}
	else
	{
		while ((temp = find_min_elem()) != nullptr)
		{
			while (temp->child != nullptr)
			{
				delChild(temp);
			}
			temp->count = -1;
			std::cout << temp->key << ' ';
		}
	}
}

auto CountChild(Node* current) -> int
{
	int count = 0;
	Node* temp = current;
	if (temp != nullptr)
	{
		ChildNode* tem = temp->child;
		while (tem != nullptr)
		{
			count++;
			tem = tem->childnext;
		}
	}
	return count;
}

void printGraph()
{
	if (front != nullptr)
	{
		Node* current = front;
		while (current != nullptr)
		{
			std::cout << current->key << ':' << CountChild(current) << ':' << current->count << ' ';
			current = current->next;
		}
		std::cout << std::endl;
	}
}

auto main() -> int
{
	int from;
	int to;
	std::cout << "Enter value (head) from: ";
	std::cin >> from;
	std::cout << "Enter value (head) to: ";
	std::cin >> to;
	front = new Node(from);
	insert_elem(to);
	addChild(front, to);
	std::cout << "For stop enter 00 " << std::endl;
	while (true)
	{
		std::cout << "Enter value from: ";
		std::cin >> from;
		if (from == 00)
		{
			break;
		}
		std::cout << "Enter value to: ";
		std::cin >> to;
		if (to == 00)
		{
			break;
		}
		insert_elem(from);
		insert_elem(to);
		if (from != to)
		{
			addChild(find(from), to);
		}
	}
	printGraph();
	topSort();
}
