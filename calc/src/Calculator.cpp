#include "../include/Calculator.hpp"

Calculator::Calculator()
{};

Calculator::~Calculator()
{};

void Calculator::erase_a_b(Token &a, Token &b, token_type const &t)
{
	a = _st_n.top();
	_st_n.pop();
	if (t == token_type::PLUS || \
		t == token_type::MINUS || \
		t == token_type::MULTIPLICATION ||\
		t == token_type::DIVISION || \
		t == token_type::DIVISION_MOD || \
		t == token_type::POWER)
	{
		b = _st_n.top();
		_st_n.pop();
	}
}

void Calculator::math()
{
	Token a, b;
	erase_a_b(a,b, _st_o.top().getType());
	switch (_st_o.top().getType())
	{
	case token_type::PLUS:
		_st_n.push(a + b);
		break;
	case token_type::MINUS:
		_st_n.push(b - a);
		break;
	case token_type::MULTIPLICATION:
		_st_n.push(a * b);
		break;
	case token_type::DIVISION:
		_st_n.push(b / a);
		break;
	case token_type::DIVISION_MOD:
		_st_n.push(b % a);
		break;
	case token_type::POWER:
		_st_n.push(a.tok_power(b));
		break;
	case token_type::FUNCTION:
		if (_st_o.top().getLexem() == "sin")
			_st_n.push(a.tok_sin());
		else if (_st_o.top().getLexem() == "cos")
			_st_n.push(a.tok_cos());
		else if (_st_o.top().getLexem() == "tg")
			_st_n.push(a.tok_tg());
		else if (_st_o.top().getLexem() == "ctg")
			_st_n.push(a.tok_ctg());
		else if (_st_o.top().getLexem() == "sqrt")
			_st_n.push(a.tok_sqrt());
		else if (_st_o.top().getLexem() == "exp")
			_st_n.push(a.tok_exp());
		break;
	default:
		throw std::runtime_error("unknown operation");
		break;
	}
	_st_o.pop();	
}

void Calculator::calculate(std::vector<Token> const &token)
{
	for (int i = 0, len = token.size(); i < len; )
	{
		if (token[i].getType() == token_type::MINUS && \
				(i == 0 || token[i - 1].getType() == token_type::ROUND_BRACET_OPEN))
			_st_n.push(Token(0));
		if (token[i].getType() == token_type::DIGIT)
		{
			_st_n.push(token[i++]);
		}
		else if (token[i].getType() == token_type::ROUND_BRACET_CLOSE)
		{
			while(_st_o.top().getType() != token_type::ROUND_BRACET_OPEN)
				math();
			_st_o.pop();
			i++;
		}
		else
		{
			if (_st_o.empty() || token[i].getType() == token_type::ROUND_BRACET_OPEN)
				_st_o.push(token[i++]);
			else if (token[i].getRang() > _st_o.top().getRang())
				_st_o.push(token[i++]);
			else
				math();
		}
	}
}

void Calculator::analysis(std::string const &input)
{
	try
	{
		Lexer lex(input);
		lex.print();
		if (lex.getTokens().empty())
			return;
		calculate(lex.getTokens());
		while (_st_o.size() != 0)
			math();
		std::cout << "Answer : " << _st_n.top().getLexem() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
