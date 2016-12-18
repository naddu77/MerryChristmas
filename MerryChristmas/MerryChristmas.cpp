// MerryChristmas.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

class ChristmasTree final
{
public:
	ChristmasTree(const string& message = "Merry Christmas!!", const int level = 3, const char shape = '*', const int center = 30)
		: message(message), level(level), shape(shape), base_margin(center - 2 * level)
	{
	}

	~ChristmasTree() = default;
	ChristmasTree(const ChristmasTree&) = delete;
	ChristmasTree(ChristmasTree&&) = delete;
	ChristmasTree& operator=(const ChristmasTree&) = delete;
	ChristmasTree& operator=(ChristmasTree&&) = delete;

	void operator()(void) const
	{
		PrintChristmasTreeAndMessage();
	}


private:
	const string message;	// 트리와 함께 출력할 메시지
	const int level;		// 트리 레벨
	const char shape;		// 트리를 만들 때 사용할 모양
	const int base_margin;	// 트리를 출력할 때 여백
	
	void PrintChristmasTreeAndMessage(void) const	// 크리스마스 트리와 메시지를 출력
	{
		PrintChrismasTree();
		PrintNewLine();
		PrintMessage();
	}

	void PrintChrismasTree(const int tree_level = 0) const	// 크리스마스 트리 출력
	{
		if (tree_level >= level)
			return;

		PrintTriangle(2 * tree_level + 3, level - tree_level);
		PrintChrismasTree(tree_level + 1);
	}

	void PrintTriangle(const int triangle_level, const int current_level, const int i = 0) const	// 트리 조각 출력
	{

		if (i == triangle_level)
			return;

		PrintMargin();
		PrintWhiteSpace((current_level - 1) * 2);
		PrintWhiteSpace(triangle_level - i - 1);
		PrintShapeWithSeperator(i + 1);
		PrintNewLine();
		PrintTriangle(triangle_level, current_level, i + 1);
	}

	void PrintWhiteSpace(const int n) const	// 여백 출력
	{
		if (n <= 0)
			return;

		cout << ' ';
		PrintWhiteSpace(n - 1);
	}

	void PrintShapeWithSeperator(const int n, const char seperator = ' ') const	// 모양을 n번 출력(구분자를 두고 출력)
	{
		if (n <= 0)
			return;

		cout << shape << seperator;
		PrintShapeWithSeperator(n - 1);
	}

	void PrintMessage(void) const	// 메시지를 출력
	{
		auto prev_position = 0u;
		auto position = message.find('\n');
		while (position != string::npos)
		{
			PrintSubString(prev_position, position - prev_position);
			prev_position = position + 1;
			position = message.find('\n', prev_position + 1);
		}
		if (position != prev_position)
			PrintSubString(prev_position, position - prev_position);

		PrintNewLine();
	}

	void PrintSubString(unsigned int start_position, unsigned int offset) const	// 메시지 출력 시 중복되는 부분 메소드 추출
	{
		auto sub_string = message.substr(start_position, offset);
		PrintWhiteSpace(base_margin - (static_cast<int>(sub_string.size()) - (4 * level + 1)) / 2);
		cout << sub_string << endl;
	}

	void PrintNewLine(void) const	// New Line
	{
		cout << endl;
	}

	void PrintMargin(void) const	// 마진만큼 공백을 출력
	{
		PrintWhiteSpace(base_margin);
	}
};

void PrintChristmasTree(const string& message, const int tree_level, const int i = 1)	// 1단계부터 tree_level까지 크리스마스 트리 및 메시지 출력
{
	if (i > tree_level)
		return;

	ChristmasTree tree(message, i);
	tree();
	PrintChristmasTree(message, tree_level, i + 1);
}

int main()
{
	//PrintChristmasTree("생활코딩 여러분!!\nMerry Christmas!!!!", 5);
	ChristmasTree tree("준용이랑 지형이도\nMerry Christmas!!!!", 3);
	tree();

    return 0;
}

