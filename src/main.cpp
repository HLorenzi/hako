#include <hako/engine.h>
#include <tests/basic.h>


int main()
{
	// Init the engine.
	Hako::Engine engine;
	engine.init();
	engine.show();

	// Set up a concrete Test::Framework implementation.
	Test::Basic basic_test;

	// Run the test.
	Test::Framework* test = &basic_test;
	test->init();
	engine.loop(Hako::Callback<void>::make_member<Test::Framework, &Test::Framework::process>(test));

	// Shutdown the engine.
	test->shutdown();
	engine.shutdown();
	return 0;
}
