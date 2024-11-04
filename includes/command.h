#ifndef COMMAND_H_
# define COMMAND_H_

# include <string>
# include <vector>

class Command {
	public:
	static const Command
		kPass,
		kNick,
		kUser,
		kJoin,
		kInvite,
		kKick,
		kTopic,
		kMode,
		kPrivmsg,
		kQuit,
		kNotFound
	;

	static const Command& SearchByName(const std::string&);
	const std::string& get_name(void) const;

	private:
		static const std::vector<const Command*>& kCommandList;
		const std::string name_;

		Command(const std::string&);
		~Command();
};

bool operator== (const Command&, const Command&);
bool operator!= (const Command&, const Command&);

#endif