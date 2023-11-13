#include <memory>
#include "debugUtils.h"


using namespace std;


struct Hen
{
	unsigned id;
	float eggs;

	Hen(unsigned id_, float eggs_) :
		id{ id_ }, 
		eggs{ eggs_ }
	{
	}

};

auto UpdateHen(unique_ptr<Hen> hen) -> unique_ptr<Hen>
{
	hen->eggs += 1.8f;
	return hen;
}


int all_pointer_ops()
{
	auto hen = make_unique<Hen>(123, 3.5f);
	auto hen2 = UpdateHen(move(hen));
	TRACE(L"eggs %f\n", hen2->eggs);


	auto sp = shared_ptr<int>{};

	ASSERT(!sp);
	ASSERT(sp.use_count() == 0);
	ASSERT(!sp.unique());

	sp = make_shared<int>(123);

	ASSERT(sp);
	ASSERT(sp.use_count() == 1);
	ASSERT(sp.unique());

	auto sp2 = sp;

	ASSERT(sp.use_count() == 2);
	ASSERT(sp == sp2);


	auto wp = weak_ptr<int>{ sp2 };


	ASSERT(!wp.expired());

	if (auto locked = wp.lock())
		TRACE(L"locked! %d\n", *locked);

	sp = nullptr;
	ASSERT(wp.expired());


	if (auto locked = wp.lock())
		TRACE(L"locked! %d\n", *locked);
	else
		wp.reset();


	return 1;

}