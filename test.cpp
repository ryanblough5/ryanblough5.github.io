#include "pch.h"

#include "gtest/gtest.h"

// This is the global test environment for setup and tear down
class Environment : public ::testing::Environment
{
public:
	~Environment() override {}

	// Set up the environment
	void SetUp() override
	{
		// Intializes a random seed
		srand(time(nullptr));
	}

	// Tear down the environment
	void TearDown() override {}
};

// Create a class to store the data in between tests
class CollectionTest : public ::testing::Test
{
protected:
	// Creates a smart pointer to hold the collection
	std::unique_ptr<std::vector<int>> collection;

	// This creates a new collection that is used throughout testing
	void SetUp() override
	{
		collection.reset(new std::vector<int>);
	}

	// This erases the elements in the collection
	void TearDown() override
	{
		collection->clear();
		collection.reset(nullptr);
	}

	// This is used as a helper function to add random values from 0 to 99 count times to the collection
	void add_entries(int count)
	{
		assert(count > 0);
		for (auto i = 0; i < count; ++i)
			collection->push_back(rand() % 100);
	}
};

// Use the ASSERT macro when failure should terminate program
// Use the EXPECT macro when failure should notify user but continue processing

// CollectionTest::SetUp is called
// CollectionTest::TearDown is called

// Create a collection
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
	ASSERT_TRUE(collection);
	ASSERT_NE(collection.get(), nullptr);
}

// Tests that the colelction is empty when created
TEST_F(CollectionTest, TestEmptyWhenCreated)
{
	ASSERT_TRUE(collection->empty());
	ASSERT_EQ(collection->size(), 0);
}

// This test is intended to fail when uncommented
TEST_F(CollectionTest, WillFail)
{
	FAIL();
}

// Adds an entry to the collection
TEST_F(CollectionTest, AddsEntryToCollection)
{
	add_entries(1);
}

// Adds five entries to the collection
TEST_F(CollectionTest, AddFiveEntriesToCollection)
{
	add_entries(5);
}

// The max size is greter than the below entries
TEST_F(CollectionTest, MaxSizeIsGreater)
{
	EXPECT_TRUE(collection->max_size() > 0);
	EXPECT_TRUE(collection->max_size() > 1);
	EXPECT_TRUE(collection->max_size() > 5);
	EXPECT_TRUE(collection->max_size() > 10);
}

// The collection should is greater than or equal to 0, 1, 5, 10
TEST_F(CollectionTest, GreaterThanOrEqualToo)
{
	EXPECT_TRUE(collection->size() >= 0, 1, 5, 10);
}

// The tests the collection to be resized to a number greater than what it was previously
TEST_F(CollectionTest, IncreaseSize)
{
	collection->resize(101);
	ASSERT_TRUE(collection->size() > 100);
}

// This tests the collection to be resized to number smaller than what it was previously
TEST_F(CollectionTest, DecreaseSize)
{
	collection->resize(50);
	ASSERT_TRUE(collection->size() < 51);
}

// This test decreases the collection to zero
TEST_F(CollectionTest, DecreaseToZero)
{
	collection->resize(0);
	ASSERT_EQ(collection->size(), 0);
}

// This test clears the collection and returns it to 0
TEST_F(CollectionTest, ClearCollection)
{
	collection->clear();
	ASSERT_EQ(collection->size(), 0);
}

// This test makes the collection reserve to be pushed over 100
TEST_F(CollectionTest, IncreaseReserveCapacity)
{
	collection->push_back(rand() % 101);
	ASSERT_NE(collection->size(), 101);
}

// This test test the out of range exception
// *** NEGATIVE TEST *** 
TEST_F(CollectionTest, OutOfRangeException)
{
	ASSERT_FALSE(collection->at(101)) << "Collection is out of range";
}

// Assert that the size does not get above 100 entries
TEST_F(CollectionTest, GreaterThanOrEqualTo100)
{
	EXPECT_TRUE(collection->size() >= 100);
	EXPECT_FALSE(collection->max_size() >= 100);
}

// Add too many entries and then resize to a lower number
TEST_F(CollectionTest, AddTooManyEntriesAndResize)
{
	add_entries(1000);
	collection->resize(99);
	ASSERT_EQ(collection->size(), 99);
}

// This test tests the collection out of range resize
TEST_F(CollectionTest, OutOfRangeResize)
{
	add_entries(1000);
	collection->resize(100);
	add_entries(10);
	ASSERT_FALSE(collection->at(111)) << "Collection too large";
}

// This test verifies that the collection is zero
TEST_F(CollectionTest, VerifyCollectionZero)
{
	collection->resize(0);
	ASSERT_FALSE(collection->at(1)) << "Collection is empty";
	EXPECT_FALSE(collection->size() < 0);
	EXPECT_FALSE(collection->size() > 0);
	EXPECT_FALSE(collection->size() == 0);
}

// This test decreases the collection reserve
TEST_F(CollectionTest, DecreaseReserveCapcity)
{
	collection->push_back(rand() % 90);
	ASSERT_FALSE(collection->at(95)) << "Collection too large";
}

// This verifies the size of the collection with a false size
TEST_F(CollectionTest, VerifySizeUsingFalseSize)
{
	collection->resize(101);
	EXPECT_FALSE(collection->size() > 101);
	EXPECT_FALSE(collection->size() >= 102);
	EXPECT_FALSE(collection->size() <= 100);
	ASSERT_NE(collection->size(), 102);
}