#include <gtest/gtest.h>
#include "message.h"

// test PASS command
TEST(MessageTest, ParsingTest1) {

  std::string raw_message =
    "PASS 1234abcd : space_include_last_param: \r\n";
  message::MessageParser message_parser(raw_message);

  // Expect PASS command.
  EXPECT_EQ(message::kPass, message_parser.get_command());
  // Expect first command params.
  EXPECT_EQ("1234abcd", message_parser.get_params()[0]);
  // Expect last command params.
  EXPECT_EQ(" space_include_last_param: ", message_parser.get_params()[1]);
}

//test NICK command
TEST(MessageTest, ParsingTest2) {

  std::string raw_upper_message =
    "NICK 1234abcd\r\n";
  std::string raw_lower_message =
    "NicK 1234ABCD\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect NICK command.
  EXPECT_EQ(message::kNick, message_upper_parser.get_command());
  // Expect NICK command.
  EXPECT_EQ(message::kNick, message_lower_parser.get_command());
}
//test USER command
TEST(MessageTest, ParsingTest3) {

  std::string raw_upper_message =
    "USER user * * : user_full_name\r\n";
  std::string raw_lower_message =
    "UsEr user * * : user_full_name\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect USER command.
  EXPECT_EQ(message::kUser, message_upper_parser.get_command());
  // Expect USER command.
  EXPECT_EQ(message::kUser, message_lower_parser.get_command());
  // Expect USER command param[0]
  EXPECT_EQ("user", message_upper_parser.get_params()[0]);
  // Expect USER command param[1]
  EXPECT_EQ("*", message_upper_parser.get_params()[1]);
  // Expect USER command param[2]
  EXPECT_EQ("*", message_upper_parser.get_params()[2]);
  // Expect USER command param[3]
  EXPECT_EQ(" user_full_name", message_upper_parser.get_params()[3]);
}
//test JOIN command
TEST(MessageTest, ParsingTest4) {

  std::string raw_upper_message =
    "JOIN #ch key\r\n";
  std::string raw_lower_message =
    "JoiN #ch\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect JOIN command.
  EXPECT_EQ(message::kJoin, message_upper_parser.get_command());
  // Expect JOIN command.
  EXPECT_EQ(message::kJoin, message_lower_parser.get_command());
  // Expect JOIN command param[0]
  EXPECT_EQ("#ch", message_upper_parser.get_params()[0]);
  // Expect JOIN command param[1]
  EXPECT_EQ("key", message_upper_parser.get_params()[1]);
}

//test INVITE command
TEST(MessageTest, ParsingTest5) {

  std::string raw_upper_message =
    "INVITE user1 #ch1\r\n";
  std::string raw_lower_message =
    "InViTe user1 user2 user3\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect INVITE command.
  EXPECT_EQ(message::kInvite, message_upper_parser.get_command());
  // Expect INVITE command.
  EXPECT_EQ(message::kInvite, message_lower_parser.get_command());
  // Expect INVITE command param[0]
  EXPECT_EQ("user1", message_upper_parser.get_params()[0]);
  // Expect INVITE command param[1]
  EXPECT_EQ("#ch1", message_upper_parser.get_params()[1]);
}

//test KICK command
TEST(MessageTest, ParsingTest6) {

  std::string raw_upper_message =
    "KICK #ch1 user\r\n";
  std::string raw_lower_message =
    "KicK\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect KICK command.
  EXPECT_EQ(message::kKick, message_upper_parser.get_command());
  // Expect KICK command.
  EXPECT_EQ(message::kKick, message_lower_parser.get_command());
  // Expect INVITE command param[0]
  EXPECT_EQ("#ch1", message_upper_parser.get_params()[0]);
  // Expect INVITE command param[1]
  EXPECT_EQ("user", message_upper_parser.get_params()[1]);
}

//test TOPIC command
TEST(MessageTest, ParsingTest7) {

  std::string raw_upper_message =
    "TOPIC #ch1 topic_name\r\n";
  std::string raw_lower_message =
    "TOPIC #ch2 test\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect TOPIC command.
  EXPECT_EQ(message::kTopic, message_upper_parser.get_command());
  // Expect TOPIC command.
  EXPECT_EQ(message::kTopic, message_lower_parser.get_command());
  // Expect INVITE command param[0]
  EXPECT_EQ("#ch1", message_upper_parser.get_params()[0]);
  // Expect INVITE command param[1]
  EXPECT_EQ("topic_name", message_upper_parser.get_params()[1]);
}

//test MODE command
TEST(MessageTest, ParsingTest8) {

  std::string raw_upper_message =
    "MODE #ch1 +o user\r\n";
  std::string raw_lower_message =
    "MODE #ch2 +k key_word\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect MODE command.
  EXPECT_EQ(message::kMode, message_upper_parser.get_command());
  // Expect MODE command.
  EXPECT_EQ(message::kMode, message_lower_parser.get_command());
  // Expect MODE command param[0]
  EXPECT_EQ("#ch1", message_upper_parser.get_params()[0]);
  // Expect MODE command param[1]
  EXPECT_EQ("+o", message_upper_parser.get_params()[1]);
  // Expect MODE command param[2]
  EXPECT_EQ("user", message_upper_parser.get_params()[2]);
}

//test PRIVMSG command
TEST(MessageTest, ParsingTest9) {

  std::string raw_upper_message =
    "PRIVMSG user : test_to_send\r\n";
  std::string raw_lower_message =
    "PRIVmsg #ch1 : test_to_send\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect PRIVMSG command.
  EXPECT_EQ(message::kPrivmsg, message_upper_parser.get_command());
  // Expect PRIVMSG command.
  EXPECT_EQ(message::kPrivmsg, message_lower_parser.get_command());
  // Expect PRIVMSG command param[0]
  EXPECT_EQ("user", message_upper_parser.get_params()[0]);
  // Expect PRIVMSG last command param
  EXPECT_EQ(" test_to_send", message_upper_parser.get_params()[1]);
}

//test QUIT command
TEST(MessageTest, ParsingTest10) {

  std::string raw_upper_message =
    "QUIT\r\n";
  std::string raw_lower_message =
    "QuiT\r\n";
  message::MessageParser message_upper_parser(raw_upper_message);
  message::MessageParser message_lower_parser(raw_lower_message);
  // Expect QUIT command.
  EXPECT_EQ(message::kQuit, message_upper_parser.get_command());
  // Expect QUIT command.
  EXPECT_EQ(message::kQuit, message_lower_parser.get_command());
}

// // test the endof \n parsing
TEST(MessageTest, ParsingTest11) {

  std::string raw_message =
    "PASS 1234abcd : space_include_last_param: \n";
  message::MessageParser message_parser(raw_message);

  // Expect PASS command.
  EXPECT_EQ(message::kPass, message_parser.get_command());
  // Expect first command params.
  EXPECT_EQ("1234abcd", message_parser.get_params()[0]);
  // Expect last command params.
  EXPECT_EQ(" space_include_last_param: ", message_parser.get_params()[1]);

}

// // test lower_case parsing
TEST(MessageTest, ParsingTest12) {

   std::string raw_message =
    "pass 1234abcd\r\n";
  message::MessageParser message_parser(raw_message);
  // Expect PASS command.
  EXPECT_EQ(message::kPass, message_parser.get_command());
  // Expect first command params.
  EXPECT_EQ("1234abcd", message_parser.get_params()[0]);
}

// // test space seperate
TEST(MessageTest, ParsingTest13) {

   std::string raw_message =
    "PASS    abcd1234      efgh5678\r\n";
  message::MessageParser message_parser(raw_message);
  // Expect PASS command.
  EXPECT_EQ(message::kPass, message_parser.get_command());
  // Expect first command params.
  EXPECT_EQ("abcd1234", message_parser.get_params()[0]);
  // Expect first command params.
  EXPECT_EQ("efgh5678", message_parser.get_params()[1]);
}
