// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Precomplied.h"
#include <utility>
#include <algorithm>
#include <memory>



namespace nv {

	template<typename T>
	class unique_handle
	{
		using pointer = typename T::pointer;
		pointer m_value;


	private:

		auto close() noexcept
		{

			if (this)
			{
				T::close(m_value);
			}
		}

		unique_handle(unique_handle const&) = delete;
		auto operator=(unique_handle const&) = delete;


	public:
		explicit unique_handle(pointer value = T::invalid()) noexcept :
			m_value{ value }
		{
		}

		~unique_handle() noexcept
		{
			close();
		}

		unique_handle(unique_handle&& other) noexcept :
			m_value{ other.release() }
		{
		}

		auto operator=(unique_handle&& other)  noexcept
		{
			if (this != &other)
			{
				reset(other.release());
			}
			return this;
		}



		explicit operator bool() const noexcept
		{
			return m_value != T::invalid();
		}

		pointer get() const noexcept
		{
			return m_value;
		}

		pointer release() noexcept
		{
			auto value = m_value;
			m_value = T::invalid();
			return value;
		}

		boolean reset(pointer value = T::invalid()) noexcept
		{
			if (m_value != value)
			{
				close();
				m_value = value;
			}
			return static_cast<bool>(*this);
		}


		auto swap(unique_handle<T>& other) noexcept
		{
			std::swap(m_value, other.m_value);
		}
	};


	 //swap in algorithms uses eq and temp object is ineffiecent 
	 //incomparison with below implementation
	template <typename T>
	auto swap(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.swap(right);
	}

	template <typename T>
	bool operator==(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.get() == right.get();
	}

	template <typename T>
	bool operator!=(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.get() != right.get();
	}

	template <typename T>
	bool operator<(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.get() < right.get();
	}

	template <typename T>
	bool operator<=(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.get() <= right.get();
	}

	template <typename T>
	bool operator>(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.get() > right.get();
	}

	template <typename T>
	bool operator>=(unique_handle<T>& left, unique_handle<T>& right) noexcept
	{
		return left.get() >= right.get();
	}


	struct null_handle_traits
	{
		typedef HANDLE pointer;

		static auto invalid() noexcept
		{
			return nullptr;
		}

		static auto close(pointer value) noexcept
		{

			VERIFY(CloseHandle(value));
		}

	};


	struct invalid_handle_traits
	{
		typedef HANDLE pointer;

		static auto invalid() noexcept
		{
			return INVALID_HANDLE_VALUE;
		}

		static auto close(pointer value) noexcept
		{

			VERIFY(CloseHandle(value));
		}

	};


	using null_handle = unique_handle<null_handle_traits>;
	using invalid_handle = unique_handle<invalid_handle_traits>;

}

using namespace nv;
using namespace std;


struct map_view_deleter
{
	typedef char const* pointer;

	auto operator()(pointer value)const noexcept
	{
		VERIFY(UnmapViewOfFile(value));
	}
};


int main()
{
	auto filename = LR"(C:\Users\Naveen\software\vcpkg\LICENSE.txt)";
	auto file = invalid_handle(
		CreateFile(filename,
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		)
	);
	if (!file)
	{
		printf("CreateFile failed %d \n", GetLastError());
		return 0;
	}

	auto size = LARGE_INTEGER();
	if (!GetFileSizeEx(file.get(), &size))
	{
		printf("GetFileSizeEx failed %d \n", GetLastError());
		return 0;
	}

	if (size.QuadPart == 0)
	{
		printf("file is empty \n");
		return 0;
	}

	auto map = null_handle(
		CreateFileMapping(file.get(),
			nullptr,
			PAGE_READONLY,
			0, 0,
			nullptr)
	);

	if (!map)
	{
		printf("CreateFileMapping failed %d \n ", GetLastError());
		return 0;
	}
	file.reset();


	auto view = unique_ptr<char, map_view_deleter>
	{
		static_cast<char*> (MapViewOfFile(map.get(),
			FILE_MAP_READ,
			0,0,0))
	};

	if (!view)
	{
		printf("MapViewOfFile failed %d \n", GetLastError());
		return 0;
	}
	printf("%.*s \n", static_cast<unsigned>(size.QuadPart),	view.get());




}

int using_swap()
{
	null_handle handles[10];
	reverse(begin(handles), end(handles));

	return 0;
}


int moving_sematics()
{
	auto event = null_handle(CreateEvent(nullptr, true, false, nullptr));
	ASSERT(event);
	auto other = null_handle(move(event));
	ASSERT(!event);
	event = move(other);
	ASSERT(event);
	ASSERT(!other);
	return 0;
}


int using_some_member_function()
{
	auto event = null_handle{ CreateEvent(nullptr, true, false , nullptr) };

	if (event)
	{
		VERIFY(SetEvent(event.get()));
	}

	HANDLE danger = event.release();
	VERIFY(CloseHandle(danger));

	if (event.reset(CreateEvent(nullptr, true, false, nullptr)))
		TRACE(L"RESET\n");

	return 0;
}


