#include <libdonatallo/util/processreader.hh>

#include "testing.h"

using namespace Donatallo;

BEGIN_TEST(int, char*[])
	{
		ProcessReader r;

		EXPECT_TRUE(r.RunShell("true"));
		EXPECT_TRUE(r.GetOutput().empty());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(!r.RunShell("false"));
		EXPECT_TRUE(r.GetOutput().empty());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(!r.RunShell("nonexisting-fake-command-2348758934"));
		EXPECT_TRUE(r.GetOutput().empty());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(r.RunShell("echo test"));

		auto res = r.GetOutput();

		EXPECT_EQUAL(res.size(), 1U);
		EXPECT_TRUE(res.find("test") == res.begin());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(r.RunShell("echo test1 test2"));

		auto res = r.GetOutput();

		EXPECT_EQUAL(res.size(), 2U);
		EXPECT_TRUE(res.find("test1") != res.end());
		EXPECT_TRUE(res.find("test2") != res.end());
	}

	{
		ProcessReader r;

		EXPECT_TRUE(r.RunShell("echo test1; echo test2"));

		auto res = r.GetOutput();

		EXPECT_EQUAL(res.size(), 2U);
		EXPECT_TRUE(res.find("test1") != res.end());
		EXPECT_TRUE(res.find("test2") != res.end());
	}
END_TEST()
