add_test([=[HelloTest.BasicAssertions]=]  /Users/weijuan/projects/42Tokyo/IRC/ft_irc/ft_irc/test/build/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /Users/weijuan/projects/42Tokyo/IRC/ft_irc/ft_irc/test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  hello_test_TESTS HelloTest.BasicAssertions)
