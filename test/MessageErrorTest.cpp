#include <gtest/gtest.h>
#include "message_parser.h"
#include "command.h"

//test not Found command
TEST(MessageErrorTest, ParsingErrorTest1) {

  std::string raw_message =
    "PASS_ param1 param2 param3 \r\n";
  MessageParser message_parser(raw_message);

  // Expect not found command.
  EXPECT_EQ(kNotFound, message_parser.get_command());
  // Expect ParseError state.
  EXPECT_EQ(kParseError, message_parser.get_state());
}

//test empty command
TEST(MessageErrorTest, ParsingErrorTest2) {

  std::string raw_message =
    "\n";
  MessageParser message_parser(raw_message);

  //Expect not found command.
  EXPECT_EQ(kNotFound, message_parser.get_command());
  //Expect ParseError state.
  EXPECT_EQ(kParseEmpty, message_parser.get_state());
}

//test empty command
TEST(MessageErrorTest, ParsingErrorTest3) {

  std::string raw_message =
    "\r\n";
  MessageParser message_parser(raw_message);

  //Expect not found command.
  EXPECT_EQ(kNotFound, message_parser.get_command());
  //Expect ParseError state.
  EXPECT_EQ(kParseEmpty, message_parser.get_state());
}

//test not ascii code command
TEST(MessageErrorTest, ParsingErrorTest4) {

  std::string raw_message =
    "あいうえお param1 param2\r\n";
  MessageParser message_parser(raw_message);

  //Expect not found command.
  EXPECT_EQ(kNotFound, message_parser.get_command());
  //Expect ParseError state.
  EXPECT_EQ(kParseNotAscii, message_parser.get_state());
}