#include <gtest/gtest.h>
#include "message.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {

  std::string raw_message =
    "PASS 1234abcd";
  message::MessageParser message_parser(raw_message);

  // Expect two strings not to be equal.
  EXPECT_EQ("PASS", message_parser.get_command());
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}