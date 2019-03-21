#pragma once

#include <stdexcept>

namespace Formats
{

	class FormatException : public std::runtime_error
	{
	public:

		// `offset` is the location of the error in the stream.
		// `what` should talk about the data or just give it.
		explicit FormatException(std::streampos offset, std::string what) :
			std::runtime_error(what),
			offset(offset)
		{}

		std::streampos where() const {
			return offset;
		}

	private:
		std::streampos offset;
	};

}
