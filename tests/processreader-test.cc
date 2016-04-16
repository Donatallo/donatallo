#include <libdonatallo/util/processreader.hh>

#include "testing.h"

using namespace Donatallo;

BEGIN_TEST(int, char*[])
	{
		ProcessReader r;

		EXPECT_TRUE(r.Run("true"));
		EXPECT_TRUE(r.GetOutput().empty());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(!r.Run("false"));
		EXPECT_TRUE(r.GetOutput().empty());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(!r.Run("nonexisting-fake-command-2348758934"));
		EXPECT_TRUE(r.GetOutput().empty());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(r.Run("echo test"));
		EXPECT_EQUAL(r.GetOutput().size(), 1);
	}

	{
		ProcessReader r;

		EXPECT_TRUE(r.Run("echo test1 test2"));
		EXPECT_EQUAL(r.GetOutput().size(), 2);
	}

	{
		ProcessReader r;

		EXPECT_TRUE(r.Run("echo test1; echo test2"));
		EXPECT_EQUAL(r.GetOutput().size(), 2);
	}
END_TEST()
