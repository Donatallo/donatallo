#include <libdonatallo/database.hh>
#include <libdonatallo/result.hh>
#include <libdonatallo/detectorchain.hh>
#include <libdonatallo/detectors/alwaysdetector.hh>
#include <libdonatallo/detectors/opsysdetector.hh>
#include <libdonatallo/detectors/packagedetector.hh>
#include <libdonatallo/detectorfactory.hh>

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

	{
		// OpsysDetector should match host environment
		DetectorChain detectors;

		detectors.Append<OpsysDetector>();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
		EXPECT_EQUAL(res.size(), 1);

		if (res.size() >= 1) {
			EXPECT_EQUAL(res[0].name, "opsys");
		}
	}

#if !defined(WIN32)
	{
		// PackageDetector should at least find cmake
		DetectorChain detectors;

		detectors.Append<PackageDetector>();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
		EXPECT_EQUAL(res.size(), 1);

		if (res.size() >= 1) {
			EXPECT_EQUAL(res[0].name, "cmake");
		}
	}
#endif

	{
		// Try all available detectors
		DetectorChain detectors = DetectorFactory::GetInstance()->GetAllDetectors();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
#if !defined(WIN32)
		EXPECT_TRUE(res.size() >= 2); // always + cmake
#else
		EXPECT_TRUE(res.size() >= 1); // always
#endif
	}
END_TEST()
