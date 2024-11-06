#ifndef MODE_H_
# define MODE_H_

# include <string>

class Mode {
	public:
		static Mode Analyze(const std::string&);

		Mode(const Mode&);
		~Mode();
		char get_mode(void) const;
		bool is_plus(void) const;
		std::string ToString(void) const;

	private:
		static const std::string kSigns;
		static const std::string::size_type kPlusPos;

		const char mode_;
		const bool is_plus_;

		Mode(void);
		Mode(char, bool);
};

#endif