#include <iostream>

using namespace std;

struct Node
{
	Node* left;
	Node* right;
	Node* father;
	int number;
};

class Tree
{

public:
	Tree()
	{
		root = NULL;
	}
	Node* root;
	bool empty() const { return root == NULL; }
	void Inorden();
	void iorder(Node*);
	void Preorden();
	void preorder(Node*);
	void Padres(Node* Node);
	void Hijos(Node* Node);
	void Hojas(Node* Node);
	int size(Node* Node);
	int altura(Node* Tree);
	void Postorden();
	void postorder(Node*);
	void add(int);
	void deletes(Node*& Tree, int x);
	void deleteNode(Node*& nodeDelete);
	void enlazarNodos(Node* Tree, Node* nuevoNodo);
	void imp_arbol(string prefix, const Node* node, bool isLeft);
	void tree();
	Node* min(Node* Tree);
};

Tree b; // global
void Tree::tree() {
	imp_arbol("", root, false);
}
void Tree::add(int d)
{
	Node* t = new Node;
	Node* father;
	t->number = d;
	t->left = NULL;
	t->right = NULL;
	t->father = NULL;
	father = NULL;

	if (empty()) root = t;
	else
	{
		Node* curr;
		curr = root;
		while (curr)
		{
			father = curr;
			if (t->number > curr->number) curr = curr->right;
			else curr = curr->left;
		}

		if (t->number < father->number) {
			t->father = father;
			father->left = t;
		}
		else {
			father->right = t;
			t->father = father;
		}
	}
}

Node* Tree::min(Node* Tree) {
	if (Tree == NULL) {
		return NULL;
	}
	if (Tree->left != NULL) {
		return min(Tree->left);
	}
	else
		return Tree;
}

void Tree::enlazarNodos(Node* Tree, Node* nuevoNodo) {
	if (Tree->father != NULL) {
		if (Tree->father->left != NULL) {
			if (Tree->number == Tree->father->left->number) {
				Tree->father->left = nuevoNodo;
				return;
			}
		}
		if (Tree->father->right != NULL) {
			if (Tree->number == Tree->father->right->number) {
				Tree->father->right = nuevoNodo;
				return;
			}
		}
		Tree->right = Tree->left = NULL;
	}
	if (nuevoNodo != NULL) {
		nuevoNodo->father = Tree->father;
		return;
	}
}

void Tree::deleteNode(Node*& nodeDelete) {
	if (nodeDelete->left != NULL && nodeDelete->right != NULL) {
		Node* menor = min(nodeDelete->right);
		nodeDelete->number = menor->number;
		deleteNode(menor);
		return;
	}
	else if (nodeDelete->left != NULL) {
		enlazarNodos(nodeDelete, nodeDelete->left);
		nodeDelete->left = nodeDelete->right = NULL;
		delete nodeDelete;
		return;
	}
	else if (nodeDelete->right != NULL) {
		enlazarNodos(nodeDelete, nodeDelete->right);
		nodeDelete->left = nodeDelete->right = NULL;
		delete nodeDelete;
		return;
	}
	else {
		if (nodeDelete->father == NULL) {
			delete nodeDelete;
			b.root = NULL;
			return;
		}
		else {
			enlazarNodos(nodeDelete, NULL);
			delete nodeDelete;
			//nodeDelete->left = nodeDelete->right = NULL;
			return;
		}
	}
}

int Tree::altura(Node* Tree) {
	int a = 0, b = 0;
	if (Tree == NULL) {
		return 0;
	}
	else {
		a = altura(Tree->left) + 1;
		b = altura(Tree->right) + 1;
	}
	if (a >= b)	//Equivalente de max
		return a;
	else
		return b;

}

int Tree::size(Node* Tree) {
	if (Tree == NULL)
		return 0;
	return 1 + size(Tree->right) + size(Tree->left);
}

void Tree::Hojas(Node* Node) {
	if (Node->left == NULL && Node->right == NULL)	//Significa que es una hoja
		cout << Node->number << " ";
	if (Node->left != NULL)
		Hojas(Node->left);
	if (Node->right != NULL)
		Hojas(Node->right);
}

void Tree::Hijos(Node* Node) {
	if (Node->father != NULL)	//Significa que es un hijo
		cout << Node->number << " ";
	if (Node->left != NULL)
		Hijos(Node->left);
	if (Node->right != NULL)
		Hijos(Node->right);
}

void Tree::Padres(Node* Node) {
	if (Node->left != NULL || Node->right != NULL)	//Significa que es una hoja
		cout << Node->number << " ";
	if (Node->left != NULL)
		Padres(Node->left);
	if (Node->right != NULL)
		Padres(Node->right);
}

void Tree::deletes(Node*& Tree, int x) {
	if (Tree == NULL) {
		cout << "Tree empty" << endl;
		return;
	}
	else if (x < Tree->number) {
		deletes(Tree->left, x);
	}
	else if (x > Tree->number) {
		deletes(Tree->right, x);
	}
	else {
		deleteNode(Tree);
	}
}
void Tree::imp_arbol(string prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		cout << prefix;
		cout << (isLeft ? "|--" : "L--");
		cout << node->number << std::endl;
		imp_arbol(prefix + (isLeft ? "|   " : "    "), node->left, true);
		imp_arbol(prefix + (isLeft ? "|   " : "    "), node->right, false);

	}
}
void Tree::Inorden()
{
	inorder(root);
}

void Tree::inorder(Node* p)
{
	if (p != NULL)
	{
		if (p->left != NULL) inorder(p->left);
		cout << " " << p->number << " ";
		if (p->right != NULL) inorder(p->right);
	}
	else return;
}

void Tree::Preorden()
{
	preorder(root);
}

void Tree::preorder(Node* p)
{
	if (p != NULL)
	{
		cout << " " << p->number << " ";
		if (p->left) preorder(p->left);
		if (p->right) preorder(p->right);
	}
	else return;
}

void Tree::Postorden()
{
	postorder(root);
}

void Tree::postorder(Node* p)
{
	if (p != NULL)
	{
		if (p->left) postorder(p->left);
		if (p->right) postorder(p->right);
		cout << " " << p->number << " ";
	}
	else return;
}

void menu();
void menuRecorrido();
int main()
{

	int op, op1, numero;
	while (1)
	{
		menu();
		cin >> op;
		switch (op)
		{
		case 1: cout << " Ingresa un numero : ";
			cin >> numero;
			b.add(numero);
			break;
		case 2: {
			do {
				system("pause");
				system("cls");
				menuRecorrido();
				cin >> op1;
				switch (op1) {
				case 1: cout << endl;
					cout << " In-Orden" << endl;
					cout << " -------------------" << endl;
					b.Inorden();
					break;
				case 2: cout << endl;
					cout << " Pre-Orden" << endl;
					cout << " -------------------" << endl;
					b.Preorden();
					break;
				case 3: cout << endl;
					cout << " Post-Orden " << endl;
					cout << " --------------------" << endl;
					b.Postorden();
					break;
				case 4: cout << endl;
					cout << " Arbol " << endl;
					cout << " --------------------" << endl;
					b.tree();
					break;
				}
			} while (op1 != 5);
			break;
		}
		case 3: cout << " Ingresa un numero : ";
			cin >> numero;
			b.deletes(b.root, numero);
			break;
		case 4:
			cout << "La root es " << b.root->number << endl;
			break;
		case 5:
			cout << "Las hojas son " << endl; b.Hojas(b.root);
			break;
		case 6:
			cout << "Los padres son " << endl; b.Padres(b.root);
			break;
		case 7:
			cout << "Los hijos son " << endl; b.Hijos(b.root);
			break;
		case 8:
			cout << "La altura es " << b.altura(b.root) << endl;
			break;
		case 9:
			cout << "El nivel es " << b.altura(b.root) - 1 << endl;
			break;
		case 10:
			cout << "El orden es 2" << endl;
			break;
		case 11:
			cout << "El tamaño es " << b.size(b.root) << endl;
			break;
		case 12:
			return 0;
		}
		system("pause");
		system("cls");
	}
}
void menuRecorrido() {
	cout << "+-------Menu------+" << endl;
	cout << "| 1.-Inorden      |" << endl;
	cout << "| 2.-Post         |" << endl;
	cout << "| 3.-PreOrden     |" << endl;
	cout << "| 4.-Arbol        |" << endl;
	cout << "| 5.-Salir        |" << endl;
	cout << "+-----------------+" << endl;
}
void menu(){
	cout << "+-------Menu------+" << endl;
	cout << "| 1.-Insertar     |" << endl;
	cout << "| 2.-Mostrar      |" << endl;
	cout << "| 3.-Eliminar     |" << endl;
	cout << "| 4.-Raiz         |" << endl;
	cout << "| 5.-Hojas        |" << endl;
	cout << "| 6.-Padres       |" << endl;
	cout << "| 7.-Hijos        |" << endl;
	cout << "| 8.-Altura       |" << endl;
	cout << "| 9.-Nivel        |" << endl;
	cout << "| 10.-Orden       |" << endl;
	cout << "| 11.-Tamano      |" << endl;
	cout << "| 12.-Salir       |" << endl;
	cout << "+-----------------+" << endl;
}n
