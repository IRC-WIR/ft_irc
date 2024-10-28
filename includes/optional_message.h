#ifndef OPTIONAL_MESSAGE_H_
# define OPTIONAL_MESSAGE_H_

# include <string>
# include <stdexcept>
# include <utility>
# include <fstream>
# include <iostream>

// Javaにある「Optional」クラスを参考にしました。
// c++にも「std::optional」という似た仕組みがあるようです。
class OptionalMessage {
	public:
		static OptionalMessage Empty(void);
		static OptionalMessage Create(int, const std::string&);

		OptionalMessage(const OptionalMessage&);
		~OptionalMessage();

		bool IsEmpty(void) const;
		std::pair<int, std::string> MakePair(void) const;
		OptionalMessage AndThen(bool b);




		//例外処理
		class EmptyMessageException : public std::runtime_error {
			public:
				EmptyMessageException(void);

			private:
				static const std::string kErrorMessage;
		};

	private:
		static const std::string kFilePath;

		const bool is_empty_;
		const int fd_;
		const std::string message_;

		OptionalMessage(void);
		OptionalMessage(int, const std::string&);
};

#endif