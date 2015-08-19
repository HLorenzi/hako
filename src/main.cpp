#include <hako/engine.h>
#include <hako/util/ds_flattree.h>
#include <stdio.h>


void loop();


int main()
{
	Hako::Engine engine;
	engine.init();

	Hako::DS::FlatTree<int> tree;
	tree.init();
	auto ref33 = tree.add(33);
	auto ref44 = tree.add(44);
	auto ref55 = tree.add(55);
	auto ref66 = tree.add_child(ref44, 66);
	auto ref77 = tree.add_child(ref44, 77);
	auto ref88 = tree.add_child(ref33, 88);

	printf("tree: [%d [%d], %d [%d, %d], %d]\n",
		tree[ref33], tree[ref88],
		tree[ref44], tree[ref66], tree[ref77],
		tree[ref55]);

	//engine.loop(Hako::Callback<void>::make_static<loop>());

	return 0;
}


void loop()
{
	printf("Hello, loopy world!\n");
}
