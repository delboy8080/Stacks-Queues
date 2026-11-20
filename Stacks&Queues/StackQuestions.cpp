#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "ArrayedStack.h"
#include "LinkedQueue.h"
#include "CircularQueue.h"
using namespace std;


void question2();
void question3();
void question4();
void question5();
void question6();

int queue_main();

int main()
{
	queue_main();
}

bool isPresent(ArrayedStack<int>& s, int item)
{
	bool found = false;
	queue<int> q;
	for (int i = 0; i < 2; i++)
	{
		while (!s.isEmpty())
		{
			if (s.top() == item)
				found = true;
			q.push(s.top());
			s.pop();
		}
		while (!q.empty())
		{
			s.push(q.front());
			q.pop();
		}
	}
	return found;
}

void question2()
{
	ArrayedStack<int> stk;
	for (int i = 1; i <= 10; i++)
	{
		stk.push(i);
	}
	cout << stk;
	bool valIsPresent = isPresent(stk, 15);
	cout << "15 is present: " << (valIsPresent ? "True" : "false")<<endl;
	cout << stk;

}

bool isBalanced(string s)
{
	ArrayedStack<char> stk;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '{' || s[i] == '(' || s[i] == '[')
		{
			stk.push(s[i]);
		}
		else if (s[i] == '}' && stk.top() != '{')
		{
			return false;
		}
		else if (s[i] == ')' && stk.top() != '(')
		{
			return false;
		}
		else if (s[i] == ']' && stk.top() != '[')
		{
			return false;
		}
		else if (s[i] == '}' || s[i] == ']' || s[i] == ')')
		{
			stk.pop();
		}
	}
	return stk.isEmpty();
}


void question3()
{
	string input[4] = {"()[]{}", "{[()()]}", "([)]", "{ [ ( ) ] } ] { ( [ ] ) }"};
	for (int i = 0; i < 4; i++)
	{
		cout << input[i] << ": " << (isBalanced(input[i])?"Valid":"Invalid") << endl;
	}
}


// Helper function to get the next tag, denoted by the opening '<' and closing '>' tags
string getNextTag(string& s, int& startPos)
{

	int nextOpening = s.find('<', startPos);
	if (nextOpening != string::npos)
	{
		int nextClosing = s.find('>', nextOpening);
		startPos = nextClosing + 1;
		return s.substr(nextOpening, (nextClosing - nextOpening) + 1);
		
	}
	return "";
}
//Helper function to retrieve the tag name from an XML tag;
string getTagName(string& s)
{
	int start = 0;

	while (!isalpha(s[start]))
	{
		start++;
	}
	int end = start;
	while (isalpha(s[end]))
	{
		end++;
	}
	return s.substr(start, (end - start));
}
bool isValidXML(string& xmlDoc)
{
	ArrayedStack<string> stk;
	int pos=0;
	string tag;
	while ((tag = getNextTag(xmlDoc, pos)) != "")
	{
		if (tag.find("/") != string::npos)
		{
			string tagName = getTagName(tag);
			if (!stk.isEmpty() && tagName == stk.top())
			{
				stk.pop();

			}
			else
			{
				return false;
			}
		}
		else
		{
			//Opening tag
			string tagName = getTagName(tag);
			stk.push(tagName);
		}

		
	}
	return stk.isEmpty();
}

void question4()
{
	string doc ;
	ifstream in("xmlDoc.xml");
	if (in)
	{
		string line;
		while (!in.eof())
		{
			getline(in, line);
			doc += line;
		}
	}
	cout << (isValidXML(doc)?"Valid":"Invalid");
}

string toBinary(int i)
{
	ArrayedStack<int> stk;
	while (i > 0)
	{
		stk.push(i % 2);
		i /= 2;
	}
	string result="";
	while (!stk.isEmpty())
	{
		result = result + "" + to_string(stk.top());
		stk.pop();
	}
	return result;
}


void question5()
{
	int i = 0;
	cout << "Please enter a number" << endl;
	cin >> i;
	cout << i << " in binary is " << toBinary(i) << endl;

}

void reverseString(string& s)
{
	ArrayedStack<char> stk;
	for (int i = 0; i < s.size(); i++)
	{
		stk.push(s[i]);
	}
	s = "";
	while (!stk.isEmpty())
	{
		s +=stk.top();
		stk.pop();
	}

}

void question6()
{
	string s;
	cout << "Please enter a string." << endl;
	getline(cin, s);
	cout << s << " reversed is ";
	
	reverseString(s);
	cout << s << endl;
}

void processString(string s)
{
	string output = "";
	LinkedQueue<char> q;
	for (char c : s)
	{
		if (c == '*')
		{
			output += q.front();
			q.dequeue();
		}
		else
		{
			q.enqueue(c);
		}
	}
	cout << output;
}
void queueMain()
{
	string q1 = "EAS*Y*QUE***ST***IO*N***";
	processString(q1);


}

struct Block
{
	int qty;
	float price;
};

void sharesMain()
{
	LinkedQueue<Block> q;
	string input;
	do
	{
		if (q.size() != 0)
			cout << q.front().qty << "@" << q.front().price << ">";
		else
			cout << " >";
		cin >> input;
		if (input == "buy")
		{
			Block b;
			cin >> b.qty;
			cin >> b.price;
			q.enqueue(b);
		}
		else if (input == "sell")
		{
			int qty;
			float price;
			cin >> qty;
			cin >> price;
			double totalProfit = 0;
			while (qty > 0)
			{
				if (q.front().qty > qty)
				{
					totalProfit += qty * (price - q.front().price);
					q.front().qty -= qty;
					qty = 0;
				}
				else
				{
					totalProfit += q.front().qty * (price - q.front().price);
					qty -= q.front().qty;
					q.dequeue();
				}
			}
			cout << "Total Profit: " << totalProfit << endl;
		}
	} while (input != "exit");
}


int queue_main()
{
	CircularQueue<int> q(8);
	for (int i = 1; i <= 8; i++)
	{
		q.enqueue(i);
	}
	cout << q;
	q.dequeue();
	q.dequeue();
	q.dequeue();

	cout << q;
	q.enqueue(9);
	q.enqueue(10);
	cout << q;

	q.resize();
	cout << q;
	sharesMain();
	return 0;
}