#include <hako/engine.h>
#include <hako/util/ds_vector.h>
#include <stdio.h>


void loop();


int main()
{
    Hako::Engine engine;
    engine.init();

	Hako::DS::Vector<int> int_vec;
	int_vec.init();
	int_vec.add(33);
	int_vec.add(44);
	int_vec.add(55);

	printf("int_vec: [%d, %d, %d]\n", int_vec[0], int_vec[1], int_vec[2]);

	engine.loop(Hako::Callback<void>::make_static<loop>());
}


void loop()
{
	printf("Hello, loopy world!\n");
}
