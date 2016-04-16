#include <libdonatallo/database.hh>
#include <libdonatallo/result.hh>
#include <libdonatallo/detectorchain.hh>
#include <libdonatallo/detectors/alwaysdetector.hh>

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
		// empty detector chain should not match anything
		DetectorChain emptychain;

		Result res = db.Query(emptychain);

		EXPECT_TRUE(res.empty());
		EXPECT_EQUAL(res.size(), 0);
	}

	{
		// AlwaysDetector always matches "always" tag
		DetectorChain detectors;

		detectors.Append<AlwaysDetector>();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
		EXPECT_EQUAL(res.size(), 1);

		if (res.size() >= 1) {
			EXPECT_EQUAL(res[0].name, "always");
		}
	}

END_TEST()
