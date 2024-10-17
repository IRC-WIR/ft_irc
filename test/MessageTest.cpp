#include <gtest/gtest.h>
#include "message.h"

// test the normal parsing
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

// test lower_case parsing
TEST(MessageTest, ParsingTest2) {

   std::string raw_message =
    "pass 1234abcd\r\n";
  message::MessageParser message_parser(raw_message);
  // Expect PASS command.
  EXPECT_EQ(message::kPass, message_parser.get_command());
  // Expect first command params.
  EXPECT_EQ("1234abcd", message_parser.get_params()[0]);
  
}