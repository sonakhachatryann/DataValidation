#ifndef DATAVALIDATION_H
#define DATAVALIDATION_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

enum class symbol_names {
	At,
	Hyphen,
	Unerscore, 
	Dot, 
	Zero, 
	Nine, 
	A, 
	Z, 
	a,
	z,
	Slash,
};

const unsigned max_email_length = 320;
const unsigned max_url_length = 2048;
const std::string url_scheme = "://";
const std::string www = "www.";
const int months = 12;
const int count_of_days[months] = { 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30 };

bool is_valid_email(const std::string&);
bool is_valid_number(const std::string&);
bool is_valid_url(const std::string&);
bool is_valid_date(const std::string&);
bool check_email_prefix(const std::string&);
bool check_email_domain(const std::string&);
bool is_letter(const char);
bool is_number(const char);
bool is_dot_or_dash(const char);
bool is_valid_character(const char);
bool is_valid_scheme(const std::string&);
std::vector<std::string>* parse(const std::string&);
bool is_valid_number_for_date(const std::string&);

#endif // DATAVALIDATION_H