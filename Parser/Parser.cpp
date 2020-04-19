#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Token {
public:
	enum class Words {
		Number,
		Identifier,
		LeftParen, // (
		RightParen, // )
		LeftSquare, // [
		RightSquare, // ]
		LeftCurly, // {
		RightCurly, // }
		LessThan, // <
		GreaterThan, // >
		Equal, // =
		Plus, // +
		Minus, // -
		Asterisk, // *
		Slash, // /
		Percent, // %
		Colon, // :
		Semicolon, // ;
		SingleQuote, // ''
		DoubleQuote, // ""
		Comma, // ,
		String,
		Letter,
		If,
		Else,
		While,
		Using,
		Class,
		Static,
		Type,
		Point, // .
		Library,
		End,
		Unexpected,
	};


	Token() = default;
	Token(Words Token) : TokenType(Token) {}

	void SetTypeToken(Words Token) { TokenType = Token; }

	void SetString(string Str) { Line = Str; }

	Words GetTypeToken() noexcept { return TokenType; }

	string GetString() { return Line; }

private:
	Words TokenType{};
	string Line;
};

Token::Words ReadPredToken(Token **InputBuffer, int &Step, int Count) {

	if (0 < Step)
	{
		(*InputBuffer)--;
	}
	Step--;

	return (*InputBuffer)->GetTypeToken();
}

Token::Words ReadNextToken(Token **InputBuffer, int &Step, int Count) {

	if (Count > Step)
	{
		(*InputBuffer)++;
	}
	Step++;

	return (*InputBuffer)->GetTypeToken();
}

void Type_id_list(string &Result, Token **InputBuffer, int Size, int &Step, int &Count)
{
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);
	switch (InputBufferTemp->GetTypeToken())
	{
		case Token::Words::Type:
	
			Result += InputBufferTemp->GetString();
			Count++;
			ReadNextToken(&InputBufferTemp, Step, Size); 

			if (InputBufferTemp->GetTypeToken() != Token::Words::Identifier)
				cout << "Error aguments in range: type_id_list" << endl;
			else
			{
				Result += " " + InputBufferTemp->GetString();
				Count++;
			}
			ReadNextToken(&InputBufferTemp, Step, Size);
			
			if (InputBufferTemp->GetTypeToken() == Token::Words::Comma)
			{
				//cout << "hi!" << endl;
				Result += InputBufferTemp->GetString();
				Count++;
				Type_id_list(Result, &InputBufferTemp, Size, Step, Count);
			}
			//else if(InputBufferTemp->GetTypeToken() != Token::Words::LeftParen)

			break;
		case Token::Words::RightParen:
			break;
		default:
			cout << "Error arguments in range: type_id_list" << endl;
			cout << InputBufferTemp->GetString() << endl;
			break;
	}
	*InputBuffer = InputBufferTemp;
}

void Id_list_term(string &Result, Token **InputBuffer, int Size, int &Step, int &Count)
{
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);

	switch (InputBufferTemp->GetTypeToken())
	{
		case Token::Words::Identifier://Term'->Fact->Id Fact1
			Result += InputBufferTemp->GetString();
			Count++;

			Fact1(Result, &InputBufferTemp, Size, Step, Count);
			Term2(Result, &InputBufferTemp, Size, Step, Count);
			break;
		 
			if (InputBufferTemp->GetTypeToken() == Token::Words::Comma)
			{
				//cout << "hi!" << endl;
				Result += InputBufferTemp->GetString();
				Count++;

				Id_list_term(Result, &InputBufferTemp, Size, Step, Count);
			}

		case Token::Words::LeftParen://Term'->Fact->(Term' Term2)
			Result += InputBufferTemp->GetString();
			Count++;

			Fact1(Result, &InputBufferTemp, Size, Step, Count);
			Term2(Result, &InputBufferTemp, Size, Step, Count);

			if (InputBufferTemp->GetTypeToken() == Token::Words::Comma)
			{
				//cout << "hi!" << endl;
				Result += InputBufferTemp->GetString();
				Count++;

				Id_list_term(Result, &InputBufferTemp, Size, Step, Count);
			}

			if (InputBufferTemp->GetTypeToken() != Token::Words::RightParen)
				cout << "Error () in Fact" << endl;
			else
				Count++;

			Result += ")";
			break;

		default:
			cout << "Id_list_term->empty" << endl;
			ReadPredToken(&InputBufferTemp, Step, Size);
			break;
	}
	*InputBuffer = InputBufferTemp;
}

void Fact1(string &Result, Token **InputBuffer, int Size, int &Step, int &Count)
{
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);

	switch (InputBufferTemp->GetTypeToken())
	{
		case Token::Words::LeftCurly://not working
			Result += InputBufferTemp->GetString();
			Count++;

			Id_list_term(Result, &InputBufferTemp, Size, Step, Count);
			break;
		default://Working
			cout << "Fact1 -> empty" << endl;
			ReadPredToken(&InputBufferTemp, Step, Size);
			break;
	}
	*InputBuffer = InputBufferTemp;
}

void Fact(string &Result, Token **InputBuffer, int Size, int &Step, int &Count)
{
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);
	switch (InputBufferTemp->GetTypeToken())
	{
	case Token::Words::Identifier://id Fact1
		Result += InputBufferTemp->GetString();
		Count++;

		Fact1(Result, &InputBufferTemp, Size, Step, Count);
		break;
	case Token::Words::LeftParen:// (Term' Term2)
		Result += InputBufferTemp->GetString();
		Count++;

		Term(Result, &InputBufferTemp, Count, Step, Count);
		Term2(Result, &InputBufferTemp, Count, Step, Count);

		if (InputBufferTemp->GetTypeToken() != Token::Words::RightParen)
			cout << "Error () in Fact" << endl;
		else
			Count++;

		Result += ")";
		break;
	}
	*InputBuffer = InputBufferTemp;
}

void Term2(string &Result, Token **InputBuffer, int Size, int &Step, int &Count) {
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);
	switch (InputBufferTemp->GetTypeToken())
	{
	case Token::Words::Plus:// +Term' Term2
		Result += InputBufferTemp->GetString();
		Count++;

		Term(Result, &InputBufferTemp, Size, Step, Count);
		Term2(Result, &InputBufferTemp, Size, Step, Count);
		break;
	case Token::Words::Minus:// -Term' Term2
		Result += InputBufferTemp->GetString();
		Count++;

		Term(Result, &InputBufferTemp, Size, Step, Count);
		Term2(Result, &InputBufferTemp, Size, Step, Count);
		break;
	default:
		cout << "Term2->empty" << endl;
		ReadPredToken(&InputBufferTemp, Step, Size);
		break;
	}
	*InputBuffer = InputBufferTemp;
}

void Term1(string &Result, Token **InputBuffer, int Size, int &Step, int &Count)
{
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);
	switch (InputBufferTemp->GetTypeToken())
	{
		case Token::Words::Asterisk:// *Fact Term1
			Result += InputBufferTemp->GetString();
			Count++;

			Fact(Result, &InputBufferTemp, Size, Step, Count);
			Term1(Result, &InputBufferTemp, Size, Step, Count);
			break;
		case Token::Words::Slash:// /Fact Term1
			Result += InputBufferTemp->GetString();
			Count++;

			Fact(Result, &InputBufferTemp, Size, Step, Count);
			Term1(Result, &InputBufferTemp, Size, Step, Count);
			break;
		default:
			cout << "Term1->empty" << endl;
			ReadPredToken(&InputBufferTemp, Step, Size);
			break;
	}
	*InputBuffer = InputBufferTemp;
}

void Term(string &Result, Token **InputBuffer, int Size, int &Step, int &Count)//Term'
{
	Token *InputBufferTemp = *InputBuffer;
	ReadNextToken(&InputBufferTemp, Step, Size);

	switch (InputBufferTemp->GetTypeToken())
	{
		case Token::Words::Identifier://Fact Term1
			Result += InputBufferTemp->GetString();
			Count++;

			Fact(Result, &InputBufferTemp, Size, Step, Count);
			Term1(Result, &InputBufferTemp, Size, Step, Count);
			break;
		case Token::Words::LeftParen://Fact Term1
			Result += InputBufferTemp->GetString();
			Count++;

			Term(Result, &InputBufferTemp, Size, Step, Count);
			Term1(Result, &InputBufferTemp, Size, Step, Count);

			if (InputBufferTemp->GetTypeToken() != Token::Words::RightParen)
				cout << "Error () in static id(type_id_list)" << endl;
			else
				Count++;

			Result += ")";
			break;

		case Token::Words::LeftSquare://Fact1
			Result += InputBufferTemp->GetString();
			Count++;

			Fact1(Result, &InputBufferTemp, Size, Step, Count);
			if (InputBufferTemp->GetTypeToken() != Token::Words::RightSquare)
				cout << "Error () in static id(type_id_list)" << endl;
			else
				Count++;

			Result += "]";
			break;
		
	}
	*InputBuffer = InputBufferTemp;
}

class Parser 
{
	Token *InputBuffer;
	
public:
	Parser(Token *Range, int Size)
	{	
		int Step = 1;
		int Count = 0;
		string Result;
		InputBuffer = Range;
		//Stmt
		switch (InputBuffer->GetTypeToken()) 
		{
			case Token::Words::Using:
				Result += InputBuffer->GetString();
				Count = 1;
				
				while (Step < Size && Count != 3)
				{
					ReadNextToken(&InputBuffer, Step, Size);
					switch (InputBuffer->GetTypeToken())
					{
						case Token::Words::Library:
							Result += " " + InputBuffer->GetString();
							Count = 2;
							break;
						case Token::Words::Semicolon:
							Result += InputBuffer->GetString();
							Count = 3;
							break;
						default:
							cout << "Error: using System;" << endl;
							cout << InputBuffer->GetString() << endl;
							break;
					}
				}
				
				if (Count != Size)
					cout << "Error number token in range: using System;" << endl;

				Result += "$";
			
				break;
			case Token::Words::Identifier:
				//Term(Result, &InputBuffer, Size, Step, Count);
				Result += "$";
				break;
			case Token::Words::LeftCurly:
				Result += InputBuffer->GetString();
				Count = 1;

				if (Count != Size)
					cout << "Error number token in range: {" << endl;
				
				Result += "$";
				break;
			case Token::Words::RightCurly:
				Result += InputBuffer->GetString();
				Count = 1;

				if (Count != Size)
					cout << "Error number token in range: }" << endl;

				Result += "$";
				break;
			case Token::Words::Class:
				Result += InputBuffer->GetString();
				Count = 1;

				while (Count != 2 && Step < Size)
				{
					ReadNextToken(&InputBuffer, Step, Size);
					switch (InputBuffer->GetTypeToken())
					{
					case Token::Words::Identifier:
						Result += InputBuffer->GetString();
						Count = 2;
						break;
					default:
						cout << "Error class id" << endl;
						break;
					}
					break;
				}

				if (Count != Size)
					cout << "Error number token in range: class id" << endl;

				Result += "$";
			case Token::Words::Static:
				Result += InputBuffer->GetString();
				Count = 1;

				while (Step < Size)
				{
					ReadNextToken(&InputBuffer, Step, Size);
					cout << "Step = " << Step << endl;
					switch (InputBuffer->GetTypeToken())
					{
					case Token::Words::Type:
						Result += " " + InputBuffer->GetString();
						Count = 2;
						break;
					case Token::Words::Identifier:
						Result += " " + InputBuffer->GetString();

						if (Count != 2)
							cout << "Error Type in range: static type id(type_id_list)" << endl;
						Count = 3;
						break;
					case Token::Words::LeftParen:
						Result += InputBuffer->GetString();

						if (Count != 3)
							cout << "Error Id in range: static type id(type_id_list)" << endl;

						Count = 4;
						Type_id_list(Result, &InputBuffer, Size, Step, Count);
						//ReadNextToken(&InputBuffer, Step, Size);
						if (InputBuffer->GetTypeToken() != Token::Words::RightParen)
							cout << "Error () in static id(type_id_list)" << endl;
						else
							Count++;

						Result += ")";
						
						break;
					default:
						cout << "Error static id(type_id_list)" << endl;
						cout << InputBuffer->GetString() << endl;
						break;
					}
				}
				
				if (Count != Size)
					cout << "Error number token in range: static id(id_list_type)" << endl;

				Result += "$";
				break;
			case Token::Words::Type:
				Result += InputBuffer->GetString();
				Count = 1;

				Term(Result, &InputBuffer, Size, Step, Count);
				// R(Result, &InputBuffer, Size, Step, Count);
				Result += "$";
				break;
			case Token::Words::While:
				Result += InputBuffer->GetString();
				Count = 1;

				while (Step < Size)
				{
					switch (InputBuffer->GetTypeToken())
					{
					case Token::Words::LeftParen:
						Result += InputBuffer->GetString();
						Count = 2;
						// Term(Result, &InputBuffer, Size, &Step, &Count);
						// Expr1(Result, &InputBuffer, Size, &Step, &Count);

						break;
					default:
						cout << "While(...)" << endl;
						break;
					}
					break;
				}

				if (Count != Size)
					cout << "Error number token in ramge: while(term' expr1)" << endl;
				
				Result += "$";
				break;
			case Token::Words::If:
				Result += InputBuffer->GetString();
				Count++;

				while (ReadNextToken(&InputBuffer, Step, Count) != Token::Words::Type && Step < Count)
				{
					switch (InputBuffer->GetTypeToken())
					{
					case Token::Words::LeftParen:
						Result += InputBuffer->GetString();
						Count++;
						break;
					default:
						cout << "While(...)" << endl;
						break;
					}
					break;
				}

				// Term(Result, &InputBuffer, Size, &Step, &Count);
				// Expr1(Result, &InputBuffer, Size, &Step, &Count);
				Result += "$";
				break;
			case Token::Words::Else:
				Result += InputBuffer->GetString();
				Count++;

				if (Count > 1)
					//T(Result, &InputBuffer, Size, &Step, &Count);

				Result += "$";
				break;
			case Token::Words::End:
				Result += "$";
				break;
		}

		cout << "Result: " << Result;
	}

	~Parser() = default;
};


int main() {
	Token *Range = new Token[13];
	/*Range[0].SetTypeToken(Token::Words::Using); // using System;
	Range[0].SetString(string("using"));
	Range[1].SetTypeToken(Token::Words::Library);
	Range[1].SetString(string("System"));
	Range[2].SetTypeToken(Token::Words::Semicolon);
	Range[2].SetString(string(";"));*/

	/*Range[0].SetTypeToken(Token::Words::Static); // static id(type_id_list)
	Range[0].SetString(string("static"));
	Range[1].SetTypeToken(Token::Words::Type);
	Range[1].SetString(string("int"));
	Range[2].SetTypeToken(Token::Words::Identifier);
	Range[2].SetString(string("MIN"));
	Range[3].SetTypeToken(Token::Words::LeftParen);
	Range[3].SetString(string("("));
	Range[4].SetTypeToken(Token::Words::Type);
	Range[4].SetString(string("int"));
	Range[5].SetTypeToken(Token::Words::Identifier);
	Range[5].SetString(string("a"));
	Range[6].SetTypeToken(Token::Words::Comma);
	Range[6].SetString(string(","));
	Range[7].SetTypeToken(Token::Words::Type);
	Range[7].SetString(string("int"));
	Range[8].SetTypeToken(Token::Words::Identifier);
	Range[8].SetString(string("a"));
	Range[9].SetTypeToken(Token::Words::Comma);
	Range[9].SetString(string(","));
	Range[10].SetTypeToken(Token::Words::Type);
	Range[10].SetString(string("float"));
	Range[11].SetTypeToken(Token::Words::Identifier);
	Range[11].SetString(string("m"));
	Range[12].SetTypeToken(Token::Words::RightParen);
	Range[12].SetString(string(")"));*/


	Parser p(Range, 13);

	if (Range != NULL)
		delete[] Range;

	system("pause");
	return 0;
}