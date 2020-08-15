#pragma once
#include <utility>

namespace RAII{
	template <typename Provider>
	class Booking{
	private:
		Provider* pointer_to_provider;
		using BookingId = int;
		BookingId id;
	public:
		Booking(Provider* ptr, BookingId id_) : pointer_to_provider(ptr), id(id_){};
		Booking(const Booking<Provider>& other) = delete;
		Booking& operator =(const Booking<Provider>& other) = delete;
		Booking& operator =(Booking<Provider>&& other) {
			if(&other != this){
				pointer_to_provider = other.pointer_to_provider;
				id = other.id;
				// перемещщеный объект помечается как не использующий ресурс
				other.pointer_to_provider = nullptr;
				other.id = -1;
			}
			return *this;
		};

		Booking(Booking<Provider>&& other) : pointer_to_provider(other.pointer_to_provider), id(other.id) {
			// перемещщеный объект помечается как не использующий ресурс
			other.pointer_to_provider = nullptr;
			other.id = -1;
		}
		~Booking(){
			// Если id определяет объект как держащий Provider(можно отслеживать через указатель - если указатель на Provider nullptr) - то нужно вызвать метод
			// Уничтожающий этот объект как использующий ресурс
			// Дальше указатель и id уничтожатся сами - они автоматические объекты (автоматические объекты: члены классов,
			// глобальные и локальные переменные)
			if(pointer_to_provider){
				pointer_to_provider->CancelOrComplete(*this);
			}
		}
	};
}
