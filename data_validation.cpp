#include "data_validation.h"

std::map<symbol_names, const char> Symbol = {
	{symbol_names::At, '@'},
	{symbol_names::Hyphen, '-'},
	{symbol_names::Unerscore, '_'},
	{symbol_names::Dot, '.'},
	{symbol_names::Zero, '0'},
	{symbol_names::Nine, '9'},
	{symbol_names::A, 'A'},
	{symbol_names::Z, 'Z'},
	{symbol_names::a, 'a'},
	{symbol_names::z, 'z'},
	{symbol_names::Slash, '/'},
};

bool is_valid_email(const std::string& email) {
	if (email.length() > max_email_length) {
		return false;
	}
	unsigned at_position = email.find(Symbol[symbol_names::At]);
	if (at_position == std::string::npos) {
		std::cout << "The email domain should contain the symbol @!" << std::endl;
		return false;
	}
	if (at_position == 0 || at_position == email.size() - 1) {
		std::cout << "Wrong placement of @ symbol." << std::endl;
		return false;
	}
	std::string prefix = email.substr(0, at_position);
	if (!check_email_prefix(prefix)) {
		return false;
	}
	std::string domain = email.substr(at_position + 1, email.size() - at_position - 1);
	if (!check_email_domain(domain)) {
		return false;
	}
	std::cout << "The email is valid." << std::endl;
	return true;
}

bool is_valid_number(const std::string& number) {
	if (*number.begin() == Symbol[symbol_names::Zero] && *(number.begin() + 1) != Symbol[symbol_names::Dot]) {
		return false;
	}
	if (*number.begin() == Symbol[symbol_names::Dot]) {
		return false;
	}
	unsigned count_of_dots{};
	for (unsigned i = 0; i < number.size(); ++i) {
		if ((number[i] < Symbol[symbol_names::Zero] || number[i] > Symbol[symbol_names::Nine])
			&& number[i] != Symbol[symbol_names::Dot]) {
			return false;
		}
		if (number[i] == Symbol[symbol_names::Dot]) {
			++count_of_dots;
		}
	}
	if (count_of_dots > 1) {
		return false;
	}
	return true;
} 

bool is_valid_url(const std::string& url) {
	if (url.size() > max_url_length) {
		return false;
	}
	unsigned scheme_position = url.find(url_scheme);
	std::string scheme = url.substr(0, scheme_position);
	if (!is_valid_scheme(scheme)) {
		return false;
	}
	std::string the_rest = url.substr(scheme_position + url_scheme.size(), *(url.end() - 1));
	unsigned slash = the_rest.find(Symbol[symbol_names::Slash]);
	if (slash == std::string::npos) {
		return false;
	}
	std::string path = url.substr(scheme_position + url_scheme.size(), slash);
	if (path.find(www) == std::string::npos || path.find(www) != 0 
		|| path.find(Symbol[symbol_names::Dot]) == std::string::npos) {
		return false;
	}
	return true;
}

bool is_valid_date(const std::string& date) {
	if (date.find(Symbol[symbol_names::Hyphen]) == std::string::npos || date.find(Symbol[symbol_names::Hyphen]) == 0 
		|| date.find(Symbol[symbol_names::Hyphen]) == date.size() - 1) {
		return false;
	}
	std::vector<std::string>* parsed = parse(date);
	for (unsigned i = 0; i < parsed->size(); ++i) {
		if (!is_valid_number_for_date((*parsed)[i])) {
			return false;
		}
	}
	if (parsed->size() != 3) {
		return false;
	}
	if (std::stoi((*parsed)[0]) < 1970 || std::stoi((*parsed)[0]) > 2030) {
		return false;
	}
	if (std::stoi((*parsed)[1]) < 1 || std::stoi((*parsed)[1]) > 12) {
		return false;
	}
	if (std::stoi((*parsed)[2]) < 1 || std::stoi((*parsed)[2]) > count_of_days[std::stoi((*parsed)[1])]) {
		return false;
	}
	return true;
}

bool check_email_prefix(const std::string& prefix) {
	if (!is_letter(*prefix.begin())) {
		std::cout << "The email must begin with a letter!" << std::endl;
		return false;
	}
	if (!is_letter(*(prefix.end() - 1)) && !is_number(*(prefix.end() - 1))) {
		std::cout << "The prefix must end with a letter or a number!" << std::endl;
		return false;
	}
	for (unsigned i = 1; i < prefix.size() - 1; ++i) {
		if (!is_valid_character(prefix[i])) {
			std::cout << "The email can contain only lower or upper case letters, numbers, dots, hyphens and underscores!" << std::endl;
			return false;
		}
		if (is_dot_or_dash(prefix[i]) && is_dot_or_dash(prefix[i + 1])) {
			std::cout << "An email can't contain two consecutive punctuation marks!" << std::endl;
			return false;
		}
	}
	return true;
}

bool check_email_domain(const std::string& domain) {
	if (!is_letter(*domain.begin())) {
		std::cout << "The email domain must begin with a letter!" << std::endl;
		return false;
	}
	unsigned last_dot_position{};
	for (unsigned i = domain.size() - 1; i > 0; --i) {
		if (domain[i] == Symbol[symbol_names::Dot]) {
			last_dot_position = i;
			break;
		}
	}
	if (last_dot_position == 0) {
		std::cout << "The email domain must contain at least one dot!" << std::endl;
		return false;
	}
	if (last_dot_position >= domain.size() - 2) {
		std::cout << "There should be at least two symbols after the dot in the email domain!" << std::endl;
		return false;
	}
	for (unsigned i = 1; i < last_dot_position; ++i) {
		if (!is_valid_character(domain[i])) {
			std::cout << "The email can contain only lower or upper case letters, numbers, dots, hyphens and underscores!" << std::endl;
			return false;
		}
		if (is_dot_or_dash(domain[i]) && is_dot_or_dash(domain[i + 1])) {
			std::cout << "An email can't contain two consecutive punctuation marks!" << std::endl;
			return false;
		}
	}
	return true;
}

bool is_letter(const char ch) {
	return (ch >= Symbol[symbol_names::a] && ch <= Symbol[symbol_names::z]) 
		|| (ch >= Symbol[symbol_names::A] && ch <= Symbol[symbol_names::Z]);
}

bool is_number(const char ch) {
	return (ch >= Symbol[symbol_names::Zero] && ch <= Symbol[symbol_names::Nine]);
}

bool is_dot_or_dash(const char ch) {
	return ch == Symbol[symbol_names::Dot] || ch == Symbol[symbol_names::Hyphen] 
		|| ch == Symbol[symbol_names::Unerscore];
}

bool is_valid_character(const char ch) {
	return is_letter(ch) || is_number(ch) || is_dot_or_dash(ch);
}

bool is_valid_scheme(const std::string& scheme) {
	for (unsigned i = 0; i < scheme.size(); ++i) {
		if (!is_letter(scheme[i]) && !is_number(scheme[i]) && scheme[i] != Symbol[symbol_names::Hyphen]) {
			return false;
		}
	}
	return true;
}

std::vector<std::string>* parse(const std::string& line) {
	std::vector<std::string>* result = new std::vector<std::string>();
	unsigned start = 0;
	for (unsigned end = 0; end < line.size() + 1; ++end) {
		if ((end != line.size() - 1 && line[end] == Symbol[symbol_names::Hyphen]) || line[end] == '\0') {
			std::string current = line.substr(start, end - start);
			result->push_back(current);
			start = end + 1;
		}
		else if (end == line.size() - 1 && line[end] == Symbol[symbol_names::Hyphen]) {
			continue;
		}
	}
	return result;
}

bool is_valid_number_for_date(const std::string& number) {
	for (unsigned i = 0; i < number.size(); ++i) {
		if ((number[i] < Symbol[symbol_names::Zero] || number[i] > Symbol[symbol_names::Nine])) {
			return false;
		}
	}
	return true;
}