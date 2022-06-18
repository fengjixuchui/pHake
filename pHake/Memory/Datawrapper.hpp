#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <Windows.h>
#include "Process.hpp"

class ReadWriteFactory {
public:
	static Process* process;
};

template <uintptr_t MaxOffset> class DataWrapper : public ReadWriteFactory  // class to download whole objects with one RPM call
{
public:
	DataWrapper()
	{
		this->data_ = std::make_unique<uint8_t[]>(MaxOffset);
	}

	DataWrapper(const DataWrapper& ext) {
		this->data_ = std::make_unique<uint8_t[]>(MaxOffset);
		memcpy(this->data_.get(), ext.data_.get(), MaxOffset);
		this->base_ = ext.base_;
	}

	DataWrapper& operator=(const DataWrapper& ext) {
		if (this == &ext) return *this;
		memcpy(this->data_.get(), ext.data_.get(), MaxOffset);
		this->base_ = ext.base_;
		return *this;
	}

	void Update(uintptr_t baseAddress)
	{
		this->base_ = baseAddress;
		ReadProcessMemory(this->process->handle_, (void*)(baseAddress), this->data_.get(), MaxOffset, NULL);
	}

	template <typename T>
	T read(uintptr_t offset)
	{
		//static_assert(offset > MaxOffset, "Exceeded maximum offset");
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data_[offset]));
	}

	void write(const DataWrapper& ext)
	{
		WriteProcessMemory(this->process->handle_, (void*)(this->base_), ext.data_.get(), sizeof(MaxOffset), 0);
	}

	template<class T>
	void write(uintptr_t offset, T value)
	{
		WriteProcessMemory(this->process->handle_, (void*)(this->base_ + offset), &value, sizeof(T), 0);
	}

public:
	uintptr_t base(){ return this->base_; }
	void      base(uintptr_t base) {  this->base_ = base; }

protected:
	std::unique_ptr<uint8_t[]> data_;
	uintptr_t base_ = 0x0;
};
#endif