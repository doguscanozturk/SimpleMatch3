#pragma once

struct NoMatchFoundException : std::exception
{
	virtual const char * what () const throw () override
	{
		return "No match found!";
	}
};
