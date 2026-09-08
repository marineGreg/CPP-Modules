#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <cctype>

class RPN {
	private:
    	std::stack<int> _stack;

    	bool _isOperator(char c) const;
    	bool _performOperation(char op);

	public:
    	RPN();
    	RPN(const RPN& src);
    	RPN& operator=(const RPN& other);
    	~RPN();

    	bool resolve(const std::string& expression);
};

#endif
