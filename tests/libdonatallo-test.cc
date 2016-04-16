#include <libdonatallo/database.hh>
#include <libdonatallo/result.hh>
#include <libdonatallo/detectorchain.hh>

#include "testing.h"

using namespace Donatallo;

BEGIN_TEST(int, char*[])
	Database db;

	EXPECT_NO_EXCEPTION(db.Load(TESTDATA_DIR "/testdatabase"));

	{
		Result res = db.GetAll();

		EXPECT_TRUE(!res.empty());
		EXPECT_TRUE(res.size() == 4);

		if (res.size() >= 1) {
			EXPECT_EQUAL(res[0].name, "never");
			EXPECT_EQUAL(res[0].description, "never description");
			EXPECT_EQUAL(res[0].url, "http://never");
		}
	}

	{
		DetectorChain emptychain;

		Result res = db.Query(emptychain);

		EXPECT_TRUE(res.empty());
		EXPECT_EQUAL(res.size(), 0);
	}
END_TEST()
