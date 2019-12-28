#include "Header.h"
#include <string>
#include <stack>
#include <queue>
#include <iomanip>

int GetHeight(TNode<string>* root)
{
	if (!root)
	{
		return -1;
	}
	return 1 + max(GetHeight(root->left) , GetHeight(root->right));
}

bool isRootDataNumber(const string& data)
{
	for (int i = 0; i < (signed)data.length(); i++)
	{
		if (data[i] < '0' || data[i]>'9')
		{
			return false;
		}
	}
	return true;
}

string returnNumber(string& text, int index)
{
	string number;
	int len = text.length();
	while (index < len && (text[index] >= '0' && text[index] <= '9'))
	{
		number += text[index];
		++index;
	}
	return number;
}

//                               <TNode<string>>
void PutExprInStack(stack<TNode<string>*>& st, string& prefix)
{
	int len = prefix.length();
	
	for (int i = 0; i < len; i++)
	{
		TNode<string>* ptr;

		if (prefix[i] == ' ')
		{
			continue;
		}
		else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*')
		{
			string eval(1, prefix[i]);
			ptr = new TNode<string>(eval);
			//p.createWithData(eval, empty, empty);
			st.push(ptr);
		}
		else
		{
			string num = returnNumber(prefix, i);
			i += num.length();
			ptr = new TNode<string>(num);
			st.push(ptr);
			
		}
	}
}

TNode<string>* MakeTree(string& expr)
{
	stack<TNode<string>*> st;
	PutExprInStack(st, expr);
	stack<TNode<string>*> numbers;


	while (!st.empty())
	{
		TNode<string>* topOfStack = st.top();
		st.pop();
		if (isRootDataNumber(topOfStack->data))
		{
			numbers.push(topOfStack);
			continue;
		}
		else
		{
			TNode<string>* firstOperand = numbers.top();
			numbers.pop();
			TNode<string>* secondOperand = numbers.top();
			numbers.pop();
			TNode<string>* treeInComplete = new TNode<string>(topOfStack->data);
			treeInComplete->left = firstOperand;
			treeInComplete->right = secondOperand;
			numbers.push(treeInComplete);

		}
	}

	return numbers.top();
}


void putLevelsInVector(TNode<string>* root)
{
	vector<vector<string>> levels;
	levels.resize(GetHeight(root) + 1);
	queue<pair<TNode<string>*,int>> q;
	q.push(make_pair(root,0));
	while (!q.empty())
	{
		TNode<string>* top = q.front().first;
		int level = q.front().second;
		q.pop();
		if (level <= levels.size())
		{
			levels[level].push_back(top->data);
		}
		if (top->left)
		{
			q.push(make_pair(top->left,level+1));
		}
		if (top->right)
		{
			q.push(make_pair(top->right, level + 1));
		}
	}


	for (int i = 0; i < levels.size(); i++)
	{
		cout << "LEVEL " << i << " ELEMENTS ARE ";
		for (int j = 0; j < levels[i].size(); j++)
		{
			cout << levels[i][j] << ' ';
		}
		cout << endl;
	}


}


void printBT(const std::string& prefix, const TNode<string>* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "├─" : "└─");

		// print the value of the node
		std::cout << node->data << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}

void printBT(const TNode<string>* node)
{
	printBT("", node, false);
}


bool isOperand(string n)
{
	return n == "+" || n == "-" || n == "*";
}


//This is infix print..
void print(TNode<string>* root,bool closingBracketPrint=false)
{
	if (!root)
	{
		return;
	}
	print(root->left);
	print(root->right);
	cout << root->data << ' ';

}


// parantasisi print

bool isNodeLeaf(TNode<string>* root)
{
	return root->left == nullptr || root->right == nullptr;
}


void printBrackets(TNode<string>*& root)
{
	if (!root)
	{
		return;
	}
	if (isNodeLeaf(root))
	{
		cout << root->data<<' ';
	}
	else
	{
		cout << "(";
		printBrackets(root->left);
		cout << root->data << "";
		printBrackets(root->right);
		cout << ")";
	}
}


string returnOperand(string op)
{
	if (op == "+")
	{
		return "+";
	}
	else if (op == "-")
	{
		return "-";
	}
	else
	{
		return "*";
	}
}


int Evaluate(TNode<string>* &root)
{
	if (!root)
	{
		return 0;
	}

	else
	{
		if (isOperand(root->data))
		{
			string op = returnOperand(root->data);
			if (op == "+")
			{
				return Evaluate(root->left) + Evaluate(root->right);
			}
			else if (op == "-")
			{
				return Evaluate(root->left) - Evaluate(root->right);
			}
			else
			{
				return Evaluate(root->left) * Evaluate(root->right);
			}
		}
		else
		{
			if (root->data >= "a" && root->data <= "z")
			{
				int number;
				cin >> number;
				return number;
			}
			
			return stoi(root->data);
			
		}
	}
}
int main()
{

	string prefix = " +  1 2";
	//string prefix = "+ 21 23";
	TNode<string>* ptr = MakeTree(prefix);
	//printBrackets(ptr);
	cout << Evaluate(ptr)<<endl;
	return 0;
}
