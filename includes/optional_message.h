#ifndef OPTIONAL_MESSAGE_H_
# define OPTIONAL_MESSAGE_H_

# include <string>
# include <stdexcept>

// Javaにある「Optional」クラスを参考にしました。
// c++にも「std::optional」という似た仕組みがあるようです。
class OptionalMessage {
	public:
		static OptionalMessage Empty(void);
		static OptionalMessage Create(int, const std::string&);

		OptionalMessage(const OptionalMessage&);
		~OptionalMessage();

		bool is_empty(void) const;
		std::pair<int, std::string> MakePair(void) const;

		//例外処理
		class EmptyMessageException : public std::runtime_error {
			public:
				EmptyMessageException(void);

			private:
				static const std::string kErrorMessage;
		};

	private:
		const bool is_empty_;
		const int fd_;
		const std::string message_;

		OptionalMessage(void);
		OptionalMessage(int, const std::string&);
};

#endif