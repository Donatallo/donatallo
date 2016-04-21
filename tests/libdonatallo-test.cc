#include <libdonatallo/database.hh>
#include <libdonatallo/result.hh>
#include <libdonatallo/project.hh>
#include <libdonatallo/detectorchain.hh>
#include <libdonatallo/detectors/alwaysdetector.hh>
#include <libdonatallo/detectors/opsysdetector.hh>
#if !defined(WIN32)
#	include <libdonatallo/detectors/packagedetector.hh>
#	include <libdonatallo/detectors/fileinetcdetector.hh>
#endif
#include <libdonatallo/detectorfactory.hh>

#include "testing.h"

using namespace Donatallo;

BEGIN_TEST(int, char*[])
	Database db;

	EXPECT_NO_EXCEPTION(db.Load(TESTDATA_DIR "/testdatabase"));

	{
		Result res = db.GetAll();

		EXPECT_TRUE(!res.empty());
		EXPECT_TRUE(res.size() == 6);

		if (res.size() >= 1) {
			EXPECT_EQUAL(res[0].name, "never");
			EXPECT_EQUAL(res[0].comment, "never comment");
			EXPECT_EQUAL(res[0].url, "http://never");
		}
	}

	{
		// empty detector chain should not match anything
		DetectorChain emptychain;

		Result res = db.Query(emptychain);

		EXPECT_TRUE(res.empty());
		EXPECT_EQUAL(res.size(), 0U);
	}

	{
		// AlwaysDetector always matches "always" tag
		DetectorChain detectors;

		detectors.Append<AlwaysDetector>();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
		EXPECT_EQUAL(res.size(), 2U);

		if (res.size() == 2) {
			EXPECT_EQUAL(res[0].name, "always_b");
			EXPECT_EQUAL(res[1].name, "always_a");
		}

		auto sort1 = res.SortByName();

		EXPECT_EQUAL(sort1.size(), 2U);

		if (sort1.size() == 2) {
			EXPECT_EQUAL(sort1[0].name, "always_a");
			EXPECT_EQUAL(sort1[1].name, "always_b");
		}

		auto sort2 = res.SortByName(false);

		EXPECT_EQUAL(sort2.size(), 2U);

		if (sort2.size() == 2) {
			EXPECT_EQUAL(sort2[0].name, "always_b");
			EXPECT_EQUAL(sort2[1].name, "always_a");
		}

		// check iteration
		for (auto& project : res) {
			EXPECT_TRUE(project->name == "always_a" || project->name == "always_b");
		}

		for (const auto& project : res) {
			EXPECT_TRUE(project->name == "always_a" || project->name == "always_b");
		}
	}

	{
		// OpsysDetector should match host environment
		DetectorChain detectors;

		detectors.Append<OpsysDetector>();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
		EXPECT_EQUAL(res.size(), 1U);

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
		EXPECT_EQUAL(res.size(), 1U);

		if (res.size() >= 1) {
			EXPECT_EQUAL(res[0].name, "cmake");
		}
	}

	{
		// FileInEtcDetector
		DetectorChain detectors;

		detectors.Append<FileInEtcDetector>();

		detectors.Prepare();

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
		EXPECT_EQUAL(res.size(), 1U);

		if (res.size() == 1) {
			EXPECT_EQUAL(res[0].name, "etc");
		}
	}
#endif

	{
		// Try all available detectors
		DetectorChain detectors = DetectorFactory::GetInstance()->GetAllDetectors();

		{
			// Check progress reporting:
#if !defined(WIN32)
			const int total_detectors = 5;
#else
			const int total_detectors = 2;
#endif

			int had_progress = 0;
			int had_total = 0;
			detectors.Prepare([&](int done, int total) {
					had_progress |= 1 << done;
					had_total = total;
				});

			EXPECT_EQUAL(had_progress, (1 << (total_detectors + 1)) - 1);
			EXPECT_EQUAL(had_total, total_detectors);
		}

		Result res = db.Query(detectors);

		EXPECT_TRUE(!res.empty());
#if !defined(WIN32)
		EXPECT_TRUE(res.size() >= 4); // always + etc + cmake
#else
		EXPECT_TRUE(res.size() >= 2); // always
#endif
	}

	{
		// doantion types stuff
		Project::ForEachDonationMethod([&](Project::DonationMethod method) {
			EXPECT_TRUE(method == Project::DonationMethodFromKeyword(Project::DonationMethodToKeyword(method)));
			EXPECT_NO_EXCEPTION(Project::DonationMethodToHumanReadable(method));
			EXPECT_TRUE(Project::DonationMethodToHumanReadable(method) != "");
		});
	}
END_TEST()
