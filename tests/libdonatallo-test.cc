#include <libdonatallo/database.hh>
#include <libdonatallo/result.hh>
#include <libdonatallo/detectorchain.hh>

#include "testing.h"

using namespace Donatallo;

BEGIN_TEST(int, char*[])
	Database db;

	EXPECT_NO_EXCEPTION(db.Load(TESTDATA_DIR "/testdatabase"));

	{
		DetectorChain emptychain;

		Result res = db.Query(emptychain);

		EXPECT_TRUE(res.empty());
		EXPECT_EQUAL(res.size(), 0);
	}
END_TEST()
